using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Threading;



namespace Dashboard_DotNet
{
    public partial class Form1 : Form
    {
        Nats nats = new Nats();
        
        //TODO::https://stackoverflow.com/questions/6795075/passing-object-from-backgroundworker-to-main-thread
        // Populate List from data within thread
        public Form1()
        {
            InitializeComponent();
            nats.setCallback(onDataArrival);
        }

        public List<string> toList(string data) {
            List<string> buttons = new List<string>();
            string[] names = data.Split('\n');
            Array.Resize(ref names, names.Length - 1);//lemove last element i.e }
            return names.ToList<string>();
        }

        public void onDataArrival(string data) {
            this.Invoke(new MethodInvoker(delegate ()
            {
                listBox1.Items.Add(data);
                textBox1.Clear();
                textBox1.Text = data;
            string tofind = "gobs";
            int igobs = data.IndexOf(tofind);
            int ls = tofind.Length;
                if (igobs >= 0)
                {
                    listBox1.Items.Clear();
                    updateButtonPanelofObjects(toList(data.Substring(igobs + ls + 2)));
                }
            }));
        }

        private void updateButtonPanelofObjects(List<string> data)
        {
            flowLayoutPanel1.Controls.Clear();
            List<Button> buttons = new List<Button>();
            for (int i = 0; i < data.Capacity; i++)
            {
                Button newButton = new Button();
                newButton.Text = data[i];
                buttons.Add(newButton);
                newButton.MouseClick += NewButton_MouseClick;
                flowLayoutPanel1.Controls.Add(newButton);
            }
        }

        private void NewButton_MouseClick(object sender, MouseEventArgs e)
        {
            char gobId = ((Button)sender).Text[0];
            if (gobId==' ') gobId = ((Button)sender).Text[1];
            PubIt("s"+ gobId);
            PubIt("to?");//print transform
        }

        public void WorkThreadFunction()
        {
            try
            {
                //-url nats://seaof-163-43-82-143.jp-tokyo-01.arukascloud.io:31759/ -subject AlgeApp.Evolution -verbose
                string[] args = {
                    "-url", "nats://localhost:4222",//"nats://seaof-163-43-82-143.jp-tokyo-01.arukascloud.io:31759/",
                    "-subject", "xal.e",
                    "-verbose"
                };
                nats.Run(args);
            }
            catch (Exception ex)
            {
                System.Console.Error.WriteLine("Exception: " + ex.Message);
                System.Console.Error.WriteLine(ex);
            }
        }
        private void Form1_Load(object sender, EventArgs e)
        {
            Thread thread = new Thread(new ThreadStart(WorkThreadFunction));
            thread.Start();
            this.Show();
        }

        void PubIt(string msg) {
            //"Usage:  Publish [-url url] [-subject subject] " +
              //     "-count [count] [-payload payload]");
            string[] args = {
                    "-url", "nats://localhost:4222",//"nats://seaof-163-43-82-143.jp-tokyo-01.arukascloud.io:31759/",
                    "-subject", "xal.e.In",
                     "-count", "1",
                    "-payload", msg
                };
            Publisher publisher = new Publisher();
            publisher.Run(args);
           
        }

        void wireframe(bool tf) {
            if (tf == true) PubIt("wt");
            if (tf == false) PubIt("wf");
        }

        void edit(bool tf)
        {
            if (tf == true) PubIt("et");
            if (tf == false) PubIt("ef");
        }

        private void checkBox1_CheckedChanged(object sender, EventArgs e)
        {
            wireframe(checkBox1.Checked);
        }

        private void Form1_Activated(object sender, EventArgs e)
        {
            PubIt("n");
        }

        private string LastChar(string s) {
            int len = cbTtype.Text.Length;
            string lastChar1 = cbTtype.Text.Substring(cbTtype.Text.Length - 1);
            return lastChar1;
        }

        private void btnTransform_Click(object sender, EventArgs e)
        {
            PubIt("t"+LastChar(cbTtype.Text) + tbTval.Text);
        }

        private void listBox1_SelectedIndexChanged(object sender, EventArgs e)
        {

        }

        private void button1_Click(object sender, EventArgs e)
        {
            listBox1.Items.Clear();
            PubIt("n");
        }

        private void button2_Click(object sender, EventArgs e)
        {
            PubIt("rf");//report fps
        }

        private void button3_Click(object sender, EventArgs e)
        {
            PubIt("tc?");// Transform of Game Camera
        }

        private void checkBox2_CheckedChanged(object sender, EventArgs e)
        {
            edit(checkBox2.Checked);
        }

        private void button4_Click(object sender, EventArgs e)
        {
            PubIt(textBox2.Text);
        }

        private void panel1_Paint(object sender, PaintEventArgs e)
        {
           
        }
    }

}
