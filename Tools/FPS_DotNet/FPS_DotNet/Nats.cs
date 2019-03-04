﻿using System;
using System.Diagnostics;
using System.Text;
using System.Threading;
using System.Collections.Generic;
using NATS.Client;
using System.Windows.Forms;
namespace FPS_DotNet
{
    // Copyright 2015-2018 The NATS Authors

    // Licensed under the Apache License, Version 2.0 (the "License");

    // you may not use this file except in compliance with the License.

    // You may obtain a copy of the License at

    //

    // http://www.apache.org/licenses/LICENSE-2.0

    //

    // Unless required by applicable law or agreed to in writing, software

    // distributed under the License is distributed on an "AS IS" BASIS,

    // WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.

    // See the License for the specific language governing permissions and

    // limitations under the License.



    using System;

    using System.Diagnostics;

    using System.Text;

    using System.Threading;

    using System.Collections.Generic;

    using NATS.Client;





    class Publisher

        {

            Dictionary<string, string> parsedArgs = new Dictionary<string, string>();
            int count = 2000000;
            string url = Defaults.Url;
            string subject = "foo";
            byte[] payload = null;

            public void Run(string[] args)

            {

                Stopwatch sw = null;
                parseArgs(args);
                banner();
                Options opts = ConnectionFactory.GetDefaultOptions();
                opts.Url = url;
            try
            {
                using (IConnection c = new ConnectionFactory().CreateConnection(opts))
                {
                    sw = Stopwatch.StartNew();
                    for (int i = 0; i < count; i++)
                    {
                        c.Publish(subject, payload);
                    }
                    c.Flush();
                    sw.Stop();
                    System.Console.Write("Published {0} msgs in {1} seconds ", count, sw.Elapsed.TotalSeconds);
                    System.Console.WriteLine("({0} msgs/second).",
                        (int)(count / sw.Elapsed.TotalSeconds));
                    printStats(c);
                }
            }
            catch (Exception e) {
                MessageBox.Show("Cannot Connect to AlgeApp Messaging Server");
                Application.Exit();
            }
            }
            private void printStats(IConnection c)
            {
                IStatistics s = c.Stats;
                System.Console.WriteLine("Statistics:  ");
                System.Console.WriteLine("   Outgoing Payload Bytes: {0}", s.OutBytes);
                System.Console.WriteLine("   Outgoing Messages: {0}", s.OutMsgs);
            }



            private void usage()
            {
                System.Console.Error.WriteLine(
                    "Usage:  Publish [-url url] [-subject subject] " +
                    "-count [count] [-payload payload]");
                System.Environment.Exit(-1);
            }
            private void parseArgs(string[] args)
            {
                if (args == null)
                    return;
                for (int i = 0; i < args.Length; i++)
                {
                    if (i + 1 == args.Length)
                        usage();
                    parsedArgs.Add(args[i], args[i + 1]);
                    i++;
                }
                if (parsedArgs.ContainsKey("-count"))
                    count = Convert.ToInt32(parsedArgs["-count"]);

                if (parsedArgs.ContainsKey("-url"))
                    url = parsedArgs["-url"];

                if (parsedArgs.ContainsKey("-subject"))
                    subject = parsedArgs["-subject"];

                if (parsedArgs.ContainsKey("-payload"))
                    payload = Encoding.UTF8.GetBytes(parsedArgs["-payload"]);

            }

            private void banner()
            {
                System.Console.WriteLine("Publishing {0} messages on subject {1}",
                    count, subject);
                System.Console.WriteLine("  Url: {0}", url);
                System.Console.WriteLine("  Payload is {0} bytes.",
                    payload != null ? payload.Length : 0);
            }



            public static void Pub(string[] args)
            {
                try
                {
                    new Publisher().Run(args);
                }
                catch (Exception ex)
                {
                    System.Console.Error.WriteLine("Exception: " + ex.Message);
                    System.Console.Error.WriteLine(ex);
                }
            }
        }
  

    class Nats
    {
        Dictionary<string, string> parsedArgs = new Dictionary<string, string>();
        int count = 1000000;
        string url = Defaults.Url;
        string subject = "foo";
        bool sync = false;
        int received = 0;
        bool verbose = false;

        public void Run(string[] args)
        {
            parseArgs(args);
            banner();

            Options opts = ConnectionFactory.GetDefaultOptions();
            opts.Url = url;

            using (IConnection c = new ConnectionFactory().CreateConnection(opts))
            {
                TimeSpan elapsed;

                if (sync)
                {
                    elapsed = receiveSyncSubscriber(c);
                }
                else
                {
                    elapsed = receiveAsyncSubscriber(c);
                }

                System.Console.Write("Received {0} msgs in {1} seconds ", received, elapsed.TotalSeconds);
                System.Console.WriteLine("({0} msgs/second).",
                    (int)(received / elapsed.TotalSeconds));
                printStats(c);

            }
        }

        Action<string> onRcv;

        internal void setCallback(Action<string> onDataArrival)
        {
            onRcv = onDataArrival;
        }

        private void printStats(IConnection c)
        {
            IStatistics s = c.Stats;
            System.Console.WriteLine("Statistics:  ");
            System.Console.WriteLine("   Incoming Payload Bytes: {0}", s.InBytes);
            System.Console.WriteLine("   Incoming Messages: {0}", s.InMsgs);
        }

        private TimeSpan receiveAsyncSubscriber(IConnection c)
        {
            Stopwatch sw = new Stopwatch();
            Object testLock = new Object();

            EventHandler<MsgHandlerEventArgs> msgHandler = (sender, args) =>
            {
                if (received == 0)
                    sw.Start();

                received++;

                string rcv = System.Text.Encoding.UTF8.GetString(args.Message.Data);

                if (verbose)
                    Console.WriteLine("Received: " + args.Message);

                onRcv(rcv);

                if (received >= count)
                {
                    sw.Stop();
                    lock (testLock)
                    {
                        Monitor.Pulse(testLock);
                    }
                }
            };

            using (IAsyncSubscription s = c.SubscribeAsync(subject, msgHandler))
            {
                // just wait until we are done.
                lock (testLock)
                {
                    Monitor.Wait(testLock);
                }
            }

            return sw.Elapsed;
        }


        private TimeSpan receiveSyncSubscriber(IConnection c)
        {
            using (ISyncSubscription s = c.SubscribeSync(subject))
            {
                Stopwatch sw = new Stopwatch();

                while (received < count)
                {
                    if (received == 0)
                        sw.Start();

                    Msg m = s.NextMessage();
                    received++;

                    if (verbose)
                        Console.WriteLine("Received: " + m);
                }

                sw.Stop();

                return sw.Elapsed;
            }
        }

        private void usage()
        {
            System.Console.Error.WriteLine(
                "Usage:  Publish [-url url] [-subject subject] " +
                "-count [count] [-sync] [-verbose]");

            System.Environment.Exit(-1);
        }

        private void parseArgs(string[] args)
        {
            if (args == null)
                return;

            for (int i = 0; i < args.Length; i++)
            {
                if (args[i].Equals("-sync") ||
                    args[i].Equals("-verbose"))
                {
                    parsedArgs.Add(args[i], "true");
                }
                else
                {
                    if (i + 1 == args.Length)
                        usage();

                    parsedArgs.Add(args[i], args[i + 1]);
                    i++;
                }

            }

            if (parsedArgs.ContainsKey("-count"))
                count = Convert.ToInt32(parsedArgs["-count"]);

            if (parsedArgs.ContainsKey("-url"))
                url = parsedArgs["-url"];

            if (parsedArgs.ContainsKey("-subject"))
                subject = parsedArgs["-subject"];

            if (parsedArgs.ContainsKey("-sync"))
                sync = true;

            if (parsedArgs.ContainsKey("-verbose"))
                verbose = true;
        }

        private void banner()
        {
            System.Console.WriteLine("Receiving {0} messages on subject {1}",
                count, subject);
            System.Console.WriteLine("  Url: {0}", url);
            System.Console.WriteLine("  Receiving: {0}",
                sync ? "Synchronously" : "Asynchronously");
        }

        public static void NatsMain(string[] args)
        {
            try
            {
                new Nats().Run(args);
            }
            catch (Exception ex)
            {
                System.Console.Error.WriteLine("Exception: " + ex.Message);
                System.Console.Error.WriteLine(ex);
            }
        }
    }
}