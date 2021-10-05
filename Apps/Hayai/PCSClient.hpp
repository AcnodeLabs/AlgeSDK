// Copyright (c) 2021 Bilal Ahsan

/* 
   com.perfectcircle.pcsclient
*/

//Virtual Skia Functions
class SKCanvas {};
class SKPaint {};
class SKSurface {};
struct SKColor {};
struct SKRect {};
struct SKPoint {};
class SKImage {};
class SKImageInfo {};
class Socket{
public:
    int Connected;
};
class SKTouchEventArgs {
public:
    i2 Location;
    short ActionType;
};
class SKPaintSurfaceEventArgs {
    
};
class Task {};

class Action {};
struct _PCSFontAttributes {
    short Right;
    short Bottom;
    short Left;
    short Top;
};
enum SKTouchAction {
    Pressed = 1,
};

enum SKPaintStyle {
    
};

class System_Drawing_Rectangle {};

enum SKColors {
    
};
using namespace std;
#define byte unsigned char
namespace PCSClient
{

    //KEYDATA.txt is on Desktop:::<< TODO << START HERE

    struct HELP
    {
    public:
        char Use;
        char Splf;
        int Lne;
        int Pos;
        int Siz;
    };

    class TRANHEADER
    {
        TRANHEADER *Next;    //Offset to next entry in table.  0 = end of window
        short TSize;         //Tran size
        int Seq;            //Transaction sequence
        int Row;            //Row number for display
        int Tag;            //Display tag number
        //enum TranTypes TranType;    //Number to indicate, Text, Line, Circle, Box, etc.
        unsigned char Instance;            //Instance number, usually 0
        short Position;         //Basis position for display
        char LineOffset; //Offset for display, 10 = 10% of a character cell, etc.
        char PosOffset;  //Offset for position.
        short Foreground;           // Foreground color, 100, 200...900 = normal colors,
                                    //    and use low order digits (ie. 101...199) as ways to modify them.
                                    //    maybe middle is normal (150), and for example, 160 means, raise
                                    //    the intensity a percentage.
        short Background;           // Background color
    };

class _WindowData
{
    _WindowData* Next;
public:
    int WindowNumber;
    int StartRow;
    int StartCol;
    int EndRow;
    int EndCol;
    int MaxRow;
    int MaxCol;
    char Outline;
    char ActiveColorDisplay;
    char ActiveColorAccept;
    int ColorScreen;
    int ColorDisplay;
    int ColorField;
    int ColorAccept;
    int ColorFChg;
    int ColorError;
    int ColorHelp1;
    int ColorHelp4;
    int Line;
    int Position;
    int Size;
    int Highlight;
    char DisplayNow;
    char AcceptNow;
    char ConcealPassword;
    string ConvertCase;        //Extra byte is for null-terminator
    char Echo;
    char ReturnSpecialKey;
    string CommandSet;
    char MemoSet;
    char DisplayError;
    char DisplayWarn;
    string Warn;
    char ErrorClear;
    char ErrorWait;
    int ErrorLne;
    int ErrorPos;
    int ErrorSiz;
    HELP Help[6];// = new HELP[6];
    //    char        ScreenData[MAX_LINES][MAX_COLUMNS];
    //    short        ScreenColors[MAX_LINES][MAX_COLUMNS];
    //    BYTE        ScreenAttribs[MAX_LINES][MAX_COLUMNS];
    string ScnNo;
    int TO_row;
    int TO_col;
    int Ins_row;
    int Ins_col;
    int Ins_color;
    string hDCSource;
    int NextSeq;
    bool FixedPitch;
    int FontNum;
};

    struct _WindowTable
    {
    public:
        const int MAX_LINES = 150;
        _WindowData WindowTrans;
        TRANHEADER FirstTran;
        TRANHEADER LastTran;
        bool ClearLine;//[]?
        short Background;//[]?

        void ZeroMemory()
        {

        }
    };

    struct SCROLLINFO
    {
        uint cbSize;
        int fMask;
        int nMin;
        int nMax;
        uint nPage;
        int nPos;
        int nTrackPos;
    };



    enum ClientMode
    {
        CLIENTMODE_NONE,
        NORMALMODE,
        TIMETRACK,
        CALENDAR,
        MESSAGES,
        SCHEDULE,
        WORKENTRY,
        TASKMODE,
        GOALMODE,
        PROJECTMODE,
        USERPRESENCE,
        TODOMODE,
        WIDESCREEN_REPORT,
        CALL_ID_IW,
        CALL_ID_MW
    };

    // Learn more about making custom code visible in the Xamarin.Forms previewer
    // by visiting https://aka.ms/xamarinforms-previewer


    class MainPage
    {

       
        enum KeyTypes
        {
            EOT,            //End of table marker
            STD,            //Standard key, can be retrieved with a WM_CHAR message
            SPL,            //Special keys
            CLN             //Client keys, processed internally, not returned to server
        };

        const char VK_ESCAPE = (char)0x1B;
        const char VK_F1 = (char)0x70;
        const char VK_F2 = (char)0x71;
        const char VK_F3 = (char)0x72;
        const char VK_F4 = (char)0x73;
        const char VK_F5 = (char)0x74;
        const char VK_F6 = (char)0x75;
        const char VK_F7 = (char)0x76;
        const char VK_F8 = (char)0x77;
        const char VK_F9 = (char)0x78;
        const char VK_F10 = (char)0x79;
        const char VK_F11 = (char)0x7A;
        const char VK_F12 = (char)0x7B;
        const char VK_PRIOR = (char)0x21;
        const char VK_NEXT = (char)0x22;
        const char PCS_VK_ALTH = (char)0xAAAA;
        const char VK_LEFT = (char)0x25;
        const char VK_RIGHT = (char)0x27;
        const char VK_UP = (char)0x26;
        const char VK_DOWN = (char)0x28;
        const char VK_HOME = (char)0x24;
        const char VK_TAB = (char)0x09;
        const char VK_END = (char)0x23;
        const char VK_DELETE = (char)0x2E;
        const char VK_INSERT = (char)0x2D;
        const char VK_LBUTTON = (char)0x01;

        class _KeyData
        {
            KeyTypes Type;
            char EndAccept;     //Yes, No, or only at End of field
            int Value;
            string RtnKey;
            string RFRtnCmd;
            string D2RtnCmd;
            string IQRtnCmd;

            _KeyData(KeyTypes Type, char EndAccept, char code, string Key, string RF, string D2, string IQ) {
                Type = Type; EndAccept = EndAccept; Value = code; RtnKey = Key; D2RtnCmd = RF; D2RtnCmd = D2; IQRtnCmd = IQ;
            }
        };

        std::list<_KeyData> KeyData;
        //KeyData= new List<_KeyData>();

        bool offline = false;
        bool MobileHasControl = true;
        
        class Timer {};
        
        Timer dTimer;
        void SpawnTimer()
        {
           // test_PSplit();
 //           dTimer = new Timer(PullData, new AutoResetEvent(false), 0, offline ? 5000000 : 150);
        }

        void SpawnThread()
        {
     //       Task a = new Task(PullDataTh);
     //       a.Start();
        }



        bool fetching = false;

        int lastSeq = 0;

        void InitKeyData() {
            return;
            //    Type    EndAccept    Code            Key        RF        2D        IQ
//            KeyData.Add(new _KeyData(KeyTypes.STD, 'Y', ' ', "ESC", "QU", "QU", "QU"));
//            KeyData.Add(new _KeyData(KeyTypes.SPL, 'Y', VK_ESCAPE, "ESC", "QU", "QU", "QU"));
//            KeyData.Add(new _KeyData(KeyTypes.STD, 'N', '?', "?  ", "HL", "HL", "HL"));
//            KeyData.Add(new _KeyData(KeyTypes.STD, 'N', '9', "99 ", "QU", "QU", "QU"));
//            KeyData.Add(new _KeyData(KeyTypes.STD, 'N', '.', ".  ", "DE", "RF", "DE"));
//            KeyData.Add(new _KeyData(KeyTypes.STD, 'N', 'Q', "Q  ", "QU", "QU", "QU"));
//            KeyData.Add(new _KeyData(KeyTypes.STD, 'N', 'q', "Q  ", "QU", "QU", "QU"));
//            KeyData.Add(new _KeyData(KeyTypes.STD, 'N', ',', ",  ", "DE", "LF", "PU"));
//            KeyData.Add(new _KeyData(KeyTypes.STD, 'N', '>', ">  ", "DE", "PR", "PD"));
//            KeyData.Add(new _KeyData(KeyTypes.STD, 'N', '<', "<  ", "DE", "PL", "PU"));
//            KeyData.Add(new _KeyData(KeyTypes.STD, 'N', 'Y', "Y  ", "DE", "DE", "DE"));
//            KeyData.Add(new _KeyData(KeyTypes.STD, 'N', 'y', "Y  ", "DE", "DE", "DE"));
//            KeyData.Add(new _KeyData(KeyTypes.STD, 'N', 'N', "N  ", "DE", "FF", "FF"));
//            KeyData.Add(new _KeyData(KeyTypes.STD, 'N', 'n', "N  ", "DE", "FF", "FF"));
//            KeyData.Add(new _KeyData(KeyTypes.STD, 'N', 'C', "C  ", "DE", "DE", "QU"));
//            KeyData.Add(new _KeyData(KeyTypes.STD, 'N', 'c', "C  ", "DE", "DE", "QU"));
//            KeyData.Add(new _KeyData(KeyTypes.STD, 'N', 'D', "D  ", "DE", "DE", "DE"));
//            KeyData.Add(new _KeyData(KeyTypes.STD, 'N', 'd', "D  ", "DE", "DE", "DE"));
//            KeyData.Add(new _KeyData(KeyTypes.STD, 'N', 'S', "S  ", "DE", "PU", "ST"));
//            KeyData.Add(new _KeyData(KeyTypes.STD, 'N', 's', "S  ", "DE", "PU", "ST"));
//            KeyData.Add(new _KeyData(KeyTypes.STD, 'N', 'P', "P  ", "DE", "PD", "PD"));
//            KeyData.Add(new _KeyData(KeyTypes.STD, 'N', 'p', "P  ", "DE", "PD", "PD"));
//            KeyData.Add(new _KeyData(KeyTypes.STD, 'N', 'B', "B  ", "DE", "BF", "BF"));
//            KeyData.Add(new _KeyData(KeyTypes.STD, 'N', 'b', "B  ", "DE", "BF", "BF"));
//            KeyData.Add(new _KeyData(KeyTypes.STD, 'N', 'L', "L  ", "DE", "PU", "PU"));
//            KeyData.Add(new _KeyData(KeyTypes.STD, 'N', 'l', "L  ", "DE", "PU", "PU"));
//            KeyData.Add(new _KeyData(KeyTypes.SPL, 'Y', VK_F1, "F1 ", "HL", "HL", "HL"));
//            KeyData.Add(new _KeyData(KeyTypes.SPL, 'Y', VK_F2, "F2 ", "HL", "HL", "HL"));
//            KeyData.Add(new _KeyData(KeyTypes.SPL, 'Y', VK_F3, "F3 ", "DF", "DF", "DF"));
//            KeyData.Add(new _KeyData(KeyTypes.SPL, 'Y', VK_F4, "F4 ", "DF", "DF", "DF"));
//            KeyData.Add(new _KeyData(KeyTypes.SPL, 'Y', VK_F5, "F5 ", "DF", "DF", "DF"));
//            KeyData.Add(new _KeyData(KeyTypes.SPL, 'Y', VK_F6, "F6 ", "DF", "DF", "DF"));
//            KeyData.Add(new _KeyData(KeyTypes.SPL, 'Y', VK_F7, "F7 ", "DF", "DF", "DF"));
//            KeyData.Add(new _KeyData(KeyTypes.SPL, 'Y', VK_F8, "F8 ", "DF", "DF", "DF"));
//            KeyData.Add(new _KeyData(KeyTypes.SPL, 'Y', VK_F9, "F9 ", "DE", "DE", "DE"));
//            KeyData.Add(new _KeyData(KeyTypes.SPL, 'Y', VK_F10, "FA ", "QU", "QU", "QU"));
//            KeyData.Add(new _KeyData(KeyTypes.SPL, 'Y', VK_F11, "FB ", "HL", "HL", "HL"));
//            KeyData.Add(new _KeyData(KeyTypes.SPL, 'Y', VK_F12, "FC ", "HL", "HL", "HL"));
//            KeyData.Add(new _KeyData(KeyTypes.SPL, 'Y', VK_PRIOR, "PU ", "BF", "PU", "PU"));
//            KeyData.Add(new _KeyData(KeyTypes.SPL, 'Y', VK_NEXT, "PD ", "DF", "PD", "PD"));
//            KeyData.Add(new _KeyData(KeyTypes.SPL, 'Y', PCS_VK_ALTH, "ALH", "HL", "HL", "HL"));
//            KeyData.Add(new _KeyData(KeyTypes.SPL, 'E', VK_LEFT, "LA ", "BF", "LF", "BF"));
//            KeyData.Add(new _KeyData(KeyTypes.SPL, 'E', VK_RIGHT, "RA ", "DF", "RF", "FF"));
//            KeyData.Add(new _KeyData(KeyTypes.SPL, 'Y', VK_UP, "UA ", "BF", "BF", "BF"));
//            KeyData.Add(new _KeyData(KeyTypes.SPL, 'Y', VK_DOWN, "DA ", "DF", "FF", "FF"));
//            KeyData.Add(new _KeyData(KeyTypes.SPL, 'Y', VK_HOME, "HM ", "BF", "BF", "DF"));
//            KeyData.Add(new _KeyData(KeyTypes.SPL, 'Y', VK_TAB, "TB ", "DF", "FF", "FF"));
//            KeyData.Add(new _KeyData(KeyTypes.SPL, 'Y', Convert.ToChar(-1), "BT ", "BF", "BF", "BF"));
//            KeyData.Add(new _KeyData(KeyTypes.CLN, 'Y', VK_END, "EN ", "  ", "  ", "  "));
//            KeyData.Add(new _KeyData(KeyTypes.CLN, 'N', VK_DELETE, "DL ", "  ", "  ", "  "));
//            KeyData.Add(new _KeyData(KeyTypes.CLN, 'N', VK_INSERT, "IN ", "  ", "  ", "  "));
//            KeyData.Add(new _KeyData(KeyTypes.SPL, 'Y', VK_LBUTTON, "LB ", "DF", "DF", "DF"));
//            KeyData.Add(new _KeyData(KeyTypes.CLN, 'N', Convert.ToChar(-2), "WDL", "  ", "  ", "  "));
//            KeyData.Add(new _KeyData(KeyTypes.CLN, 'N', Convert.ToChar(-3), "WDR", "  ", "  ", "  "));
//            KeyData.Add(new _KeyData(KeyTypes.EOT, ' ', ' ', "   ", "  ", "  ", "  "));
            
        }


//        std::list<std::string> phase1(std::list<std::string> td)
//        {
//
//            td.Add("CTL,SZ,19,W0080");
//            td.Add("CTL,WC,10,001");
//            td.Add("CTL,WP,161,001001001025080NSS701701701880701741721721001001001001 E RF 000000YY NN020041030100 YN022041040YN023041040NN023041040YK022001040YK023001040NN02300104");
//            td.Add("CTL,WL,17,001001Y731");
//            td.Add("CTL,WT,179,001001   ☺☻");
//            td.Add("CTL,WT,179,001001   ☺☻");
//            td.Add("CTL,WT,179,0010014  ☺☻");
//            td.Add("CTL,WT,179,001001   ☺☻");
//            td.Add("CTL,WT,179,001001Ç  ☺☻");
//            td.Add("CTL,WT,42,001001   ☺");
//            td.Add("CTL,WT,42,001001");
//            td.Add("CTL,WL,17,001002Y701");
//            td.Add("CTL,WT,44,001002");
//            td.Add("CTL,WL,17,001003Y701");
//            td.Add("CTL,WL,17,001004Y701");
//            td.Add("CTL,WL,17,001005Y701");
//            td.Add("CTL,WL,17,001006Y701");
//            td.Add("CTL,WL,17,001007Y701");
//            td.Add("CTL,WL,17,001008Y701");
//            td.Add("CTL,WL,17,001009Y701");
//            td.Add("CTL,WL,17,001010Y701");
//            td.Add("CTL,WL,17,001011Y701");
//            td.Add("CTL,WT,44,001011");
//            td.Add("CTL,WL,17,001012Y701");
//            td.Add("CTL,WT,179,001012");
//            td.Add("CTL,WL,17,001013Y701");
//            td.Add("CTL,WL,17,001014Y701");
//            td.Add("CTL,WT,179,001014  ");
//            td.Add("CTL,WT,179,001014");
//            td.Add("CTL,WL,17,001015Y701");
//            td.Add("CTL,WT,179,001015");
//            td.Add("CTL,WL,17,001016Y701");
//            td.Add("CTL,WL,17,001017Y701");
//            td.Add("CTL,WL,17,001018Y701");
//            td.Add("CTL,WL,17,001019Y701");
//            td.Add("CTL,WL,17,001020Y701");
//            td.Add("CTL,WL,17,001021Y701");
//            td.Add("CTL,WL,17,001022Y701");
//            td.Add("CTL,WL,17,001023Y701");
//            td.Add("CTL,WL,17,001024Y731");
//            td.Add("CTL,WT,179,001024   ");
//            td.Add("CTL,WT,42,001024   ");
//            td.Add("CTL,WT,42,001024");
//            td.Add("CTL,WL,17,001025Y731");
//            td.Add("CTL,WT,179,001025  ");
//            td.Add("CTL,WT,179,001025");
//            td.Add("CTL,WE,8,");
//            td.Add("SIO,US,19,TEST");
//            td.Add("SIO,AD,320,V2 23142480014041012005001S880SSNNSSNSNSSSSRFY AUN000001100400NNNY  Enter user-name to login");
//            return td;
//        }


        string Desc(string ret)
        {
            return "";
        }

//        string GetDesc(string ret[])
//        {
//            list<string> l = new List<string>();
//            foreach (string a in ret)
//            {
//                l.Add(Desc(a));
//            }
//            return l.ToArray();
//        }

//        string GetTestData(int seg)
//        {
//            List<string> td = new List<string>();
//            phase1(ref td);
//            //return test.ToArray();
//            string[] ret = test_data_arr0;//.ToList().Take(1879-1839).ToArray();
//            string[] descs = GetDesc(ret);
//            return ret;
//        }

        char c;
        
        class Thread {
        public:
            static void Sleep(int ms) {};
        };
        
        void PullDataTh()
        {
            while (true) {
                object nullobject;
                PullData(nullobject);
                Thread::Sleep(500);
            //    PrintMessage(canvas, paint, " Sent Reconnect Key", 10, 10, 1, 711, fa, 1, false);
              //  c++;
            //    mVib.Vibrate(20);
                //ßif (canvasPaintRefSet)
                  //  canvas.DrawCircle(new SKPoint(0, 0), 200, paint);
            }
        }

        class object {};
        void PullData(object stateInfo)
        {
            
            if (!offline)
            {
                if (!sock.Connected)
                {
               //     DisplayAlert("Error", "Remote Server Not Connected.", "OK");
               //     dTimer.Dispose();
                } else
                    test_data = SocketSendReceive(*this);
            }
            else {
                //test_data = test_data_arr0;
            }
        }
/*
        byte Take(byte arr[], int from, int to) {
            int skip = from;
            int take = to;
            byte seg[] = arr.Skip(skip).Take(take).ToArray();
            return &seg;
        }

        byte SplitByteArrayBinMode(byte oneDbyteArray[])
        {
            byte[] cmd_name = oneDbyteArray.Take(3).ToArray();
            byte[] cmd_len = oneDbyteArray.Skip(3).Take(2).ToArray();
            byte[] cmd_type = oneDbyteArray.Skip(5).Take(2).ToArray();
            byte[] cmd_spec = oneDbyteArray.Skip(7).ToArray();
            byte[][] ret = new byte[3][];
            ret[0] = cmd_name;
            ret[1] = cmd_type;
            ret[2] = cmd_spec;
            return ret;
        }

        list<byte[]> SplitPCSMessages(byte oneDbyteArray[])
        {
            list<byte[]> ret = new list<byte[]>();
            int MsgSizePtr = 3;
            int idx = 0;
            {
                while (MsgSizePtr < oneDbyteArray.Length)
                {
                    int MsgSize = oneDbyteArray[MsgSizePtr] + oneDbyteArray[MsgSizePtr + 1] * 255;
                    byte[] msg = oneDbyteArray.Skip(idx).Take(MsgSize).ToArray();
                    ret.Add(msg);
                    idx += MsgSize;
                    MsgSizePtr += MsgSize;
                }
            }
            return ret;
        }

        byte SplitByteArray(byte oneDbyteArray[], char separator = '\n')
        {

            List<int> from = new List<int>();
            List<int> to = new List<int>();
            int i = 0; int ii = 0;
            from.Add(i);
            foreach (byte b in oneDbyteArray) {
                if (b == separator)
                {
                    from.Add(i + 1);
                }
                i++;
            }
            from.Add(i + 1);
            int segments = from.Count - 2 + 1;
            byte[][] res = new byte[segments][];
            for (int ns = 0; ns < segments; ns++)
            {
                int fr = from[ns];
                int tk = from[ns + 1] - fr;
                byte[] bs = Take(oneDbyteArray, fr, tk);
                res[ns] = bs;
            }

            return res;
        }
 */
        bool IsNumeric(string x) {
            bool ret = false;
            foreach (char c in x) {
                if (c >= '0' && c <= '9') ret = true;
            }
            return ret;
        }

        bool bpressed = false;
        //https://codetips.nl/skiasharpformstouch.html
        void OnTouch(object sender, SKTouchEventArgs args)
        {

            {

            auto point = args.Location; //Point location
            auto type = args.ActionType; //Entered, Pressed, Moved ... etc.
                                        //... do something
                                        // Handle event to indicate we are interested in other events

            if (type == SKTouchAction::Pressed)
                ProcessVBtn(Convert.ToInt16(point.x), Convert.ToInt16(point.y));
            }
            args.Handled = true;
        }

        string ip_server = GetIP();//

        static string GetIP()
        {
            string ip_vbox = "192.168.100.177";
            string ip_mac = "192.168.100.16";
            string ip_pc = "192.168.100.153";
            string ip_actual = "pcs.pcsfarm.com";
            return ip_pc;
        }

        bool negotiating = true;
        bool use_proxy = false;

        int GetPort() {
            if (use_proxy) return 6994;
            return 6954;
        }

        class PCSMessage {};
        PCSMessage dateDDmsg;


        string result;
        void Fc()
        {
            result = await DisplayPromptAsync("Server IP", "Connect to "+result, "Yes", "Other");
        }

        class IVibrationService {};
        MainPage(IVibrationService vib)

        {
            mVib = vib;

            byte[] arr = { 0, 1, Convert.ToByte('\n'), 3, 4, 5, 6, Convert.ToByte('\n'), 8, 9, Convert.ToByte('\n') };
            byte[][] test = SplitByteArray(arr);

            
            InitializeComponent();

            string pip;
            
            try
            {
                pip = Application.Current.Properties["Proxy_IP"].ToString();
                if (pip.Count(f => f == '.') != 3) pip = ip_server;
            }
            catch (KeyNotFoundException ke) {
                pip = ip_server;
            }

            if (!offline)
            {
             
                try {
                    sock = SocketConnect(pip, GetPort());
                    Alert("Welcome " + (sock.Connected?"Connected ":"Could not reach ") + "Proceed");
                    }
                catch (System.Net.Sockets.SocketException sx)
                {
                    Alert(sx.Message + "!!");
                }
        }
            //SpawnTimer();
            SpawnThread();

            if (PCSMode == ClientMode.TIMETRACK) MainFont = 2;
            else
            {
                if (WindowWidth <= 80 && WindowHeight <= 25)
                {
                    MainFont = 0;
                }
                else
                {
                    MainFont = 1;
                    FONT_OFFSET = 0;
                }
            }
            var tapGestureRecognizer = new TapGestureRecognizer();
            tapGestureRecognizer.Tapped += (s, e) => {

                //  var endPos = e.Event.GetX();

                //   _thePage.TriggerTouchDown(endPos.X, endPos.Y);

                // ProcessVBtn(0,0);
            };
            canvasView.GestureRecognizers.Add(tapGestureRecognizer);
            //     s_Send(ComposeAcceptDataMessage("BILAL"));
            //     Task.Delay(1000).Wait();
            //    s_Send(ComposeAcceptDataMessage("BILAL"));
            //    Task.Delay(1000).Wait();
            //    s_Send(ComposeAcceptDataMessage("51"));
            //
           
        }


        bool once1 = true;

    protected:
        Task WaitAndExecute(int milisec, Action actionToExecute)
        {
            await Task.Delay(milisec); actionToExecute();
        }

        void OnAppearing()
        {
            base.OnAppearing();

            WaitAndExecute(1000, () => {
                if (once1)
                {
                    if (!use_proxy) Initial_Seq();
                }
                once1 = false;
            });
                
        }

    private:
        string b2s(byte* ba) {
            return string(ba);
        }

        void SendReconnectKey() {
            byte[] srv_rk = { 0x53, 0x52, 0x56, 0x43, 0x00, 0x52, 0x4b, 0x6c, 0x69, 0x76, 0x65, 0x62, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x57, 0x49, 0x4e, 0x31, 0x30, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
            s_Send(srv_rk);
        //    PrintMessage(canvas, paint, " Sent Reconnect Key", 10, 10, 1, 711, fa, 1, false);
            PullData(null);
        }
        void SendVersionInfo()
        {
            byte[] clt_vi = { 0x43, 0x4c, 0x54, 0x16, 0x00, 0x56, 0x49, 0x34, 0x2e, 0x32, 0x2e, 0x30, 0x2e, 0x37, 0x37, 0x00, 0x38, 0x30, 0x00, 0x32, 0x35, 0x00 };
            s_Send(clt_vi);
         //   PrintMessage(canvas, paint, " Sent Version Info", 10, 10, 1, 711, fa, 1, false);
        }

        void SendLogin()
        {
            byte[] srv_li = { 0x53, 0x52, 0x56, 0x07, 0x00, 0x4c, 0x49 };
            PCSMessage SrvRK = new PCSMessage("");
            Alert("Sending Login ..");
            s_Send(srv_li);
            //    byte[] ctl_cq = { 0x43, 0x54, 0x4c, 0xff, 0x00, 0x43, 0x51, 0x04, 0x00, 0xd4, 0x2c, 0x00, 0x00, 0x06, 0x00, 0x6c, 0x69, 0x76, 0x65, 0x62, 0x00, 0x06, 0x00, 0x57, 0x49, 0x4e, 0x31, 0x30, 0x00, 0x94, 0x00, 0x94, 0x00, 0x00, 0x00, 0x06, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0xf0, 0x23, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x6c, 0x69, 0x76, 0x65, 0x62, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x57, 0x49, 0x4e, 0x31, 0x30, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x54, 0x45, 0x53, 0x54, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
            //    s_Send(ctl_cq);
            //    byte[] ctl_cw = { 0x43, 0x54, 0x4c, 0x15, 0x00, 0x43, 0x57, 0x57, 0x04, 0x00, 0x50, 0x00, 0x00, 0x00, 0x48, 0x04, 0x00, 0x19, 0x00, 0x0 };
            //    s_Send(ctl_cw);
            {
                int  n2, n3, n4;
                Alert("Pulling RK Now");
                SrvRK.Pull(sock);//,out n2,out n3,out n4);
                Alert("GOT:"+ SrvRK.SubType[0]+""+ SrvRK.SubType[1] + "Expected RK - CHECK");
                mVib.Vibrate(30);
                if (SrvRK.SubType[0] == 'R' && SrvRK.SubType[1] == 'K') Alert("RK OK");
                else Alert("RK Not Ok but continuing anyway");
                {
                    SendReconnectKey();
                }
            }
        }

        void Initial_Seq() {
         //   byte[] ctl_up = { 0x43, 0x54, 0x4c, 0x0e, 0x00, 0x55, 0x50, 0x05, 0x00, 0x34, 0x2e, 0x32, 0x2e, 0x30 };
         //   s_Send(ctl_up);
            byte[] ctl_ca = { 0x43, 0x54, 0x4c, 0x22, 0x00, 0x43, 0x41, 0x4e, 0x08, 0x00, 0x34, 0x2e, 0x32, 0x2e, 0x30, 0x2e, 0x37, 0x37, 0x04, 0x00, 0x54, 0x45, 0x53, 0x54, 0x08, 0x00, 0x73, 0x38, 0x37, 0x73, 0x70, 0x61, 0x70, 0x68 };
            s_Send(ctl_ca);
            Alert("Initiating Connect Sequence .." );

            //
            //SendVersionInfo();
            //SendLogin();
           
        }

        void ProcessVBtn(int clickX, int clickY)
        {
            int hit = -1;
            for (int i = 0; i < numVBtns; i++) {
                if (vBtnActuals[i].Contains(clickX, clickY))
                {
                    hit = i;
                    mVib.Vibrate(50);
                }
            }

            string clickedText = "";
            if (hit == 0) clickedText = "ESC";
            if (hit == 1) clickedText = "F1";
            if (hit == 2) clickedText = "***";

            if (hit == 3) clickedText = "PgUp";
            if (hit == 4) clickedText = "seq";
            if (hit == 5) clickedText = "F7";

            if (hit == 6) clickedText = "PgDn";
            if (hit == 7) clickedText = "INS";
            if (hit == 8) clickedText = "DEL";

            if (hit == 9) clickedText = "abc";
            if (hit == 10) clickedText = "123";
            if (hit == 11) clickedText = "F2";

            if (hit == 12) clickedText = "Y";
            if (hit == 13) clickedText = "C";
            if (hit == 14) clickedText = "N";

            if (hit == 15) clickedText = "A";
            if (hit == 16) clickedText = "UP";
            if (hit == 17) clickedText = "R";

            if (hit == 18) clickedText = "LT";
            if (hit == 19) clickedText = "DN";
            if (hit == 20) clickedText = "RT";

            if (hit == 21) clickedText = "ENT";

            if (hit > -1) onVBtnClickAsync(clickedText);
        }

        byte b(char c) { return Convert.ToByte(c); }
        byte br(char cr[]) { return cr.Select(c => (byte)c).ToArray(); }
        byte byr(string cr) { return cr.Select(c => (byte)c).ToArray(); }

        string lastCurAcceptSeq = "";
        byte byteComposeAcceptDataMessage(string InpBuff, bool fnkey = false, bool enterKey = false)
        {
            byte SendBuf[158];// = new byte[158];
            //        Message header
            SendBuf[0] = b('S');
            SendBuf[1] = b('I');
            SendBuf[2] = b('O');
            SendBuf[3] = 158; SendBuf[4] = 0;
            SendBuf[5] = b(CurAccept.Type[0]);
            SendBuf[6] = b(CurAccept.Type[1]);
            // if (lastCurAcceptSeq == CurAccept.Seq) return null;//Bounce Control
            lastCurAcceptSeq = CurAccept.Seq;
            for (int i = 0; i < 8; i++) SendBuf[7 + i] = b(CurAccept.Seq[i]);
            string mx = ConvertNumToAlph(3, CurAccept.MouseX);
            string my = ConvertNumToAlph(3, CurAccept.MouseY);
            byte[] mbx = byr(mx);
            byte[] mby = byr(my);
            mbx.CopyTo(SendBuf, 15);
            mby.CopyTo(SendBuf, 18);

            SendBuf[21] = b(CurAccept.RtnCmd[0]);
            SendBuf[22] = b(CurAccept.RtnCmd[1]);
            SendBuf[23] = b(CurAccept.RtnKey[0]);
            SendBuf[24] = b(CurAccept.RtnKey[1]);
            SendBuf[25] = b(CurAccept.RtnKey[2]);

            int BufSize = InpBuff.Length;



            if (fnkey) {
                SendBuf[21] = b(InpBuff[0]);
                SendBuf[22] = b(InpBuff[1]);
                SendBuf[23] = b(InpBuff[2]);
                SendBuf[24] = b(InpBuff[3]);
                SendBuf[25] = b(' ');
                BufSize = 0; //No data
                BufSize = CurAccept.Default.Length;
                byr(CurAccept.Default.TrimEnd()).CopyTo(SendBuf, 26);
            }

            InpBuff = InpBuff.ToUpper();

            if (enterKey)
            {
                BufSize = CurAccept.Default.Length;
                bool escapeKey = InpBuff.StartsWith("QUESC");
                if (escapeKey)
                    byr(InpBuff).CopyTo(SendBuf, 21);
                else
                    byr("DFDF " + CurAccept.Default.TrimEnd()).CopyTo(SendBuf, 21);
            }
            else
            {
                if (CurAccept.RtnCmd.StartsWith("QU") || CurAccept.RtnKey.StartsWith("? "))
                {
                    BufSize = CurAccept.Default.Length;
                    byr(CurAccept.Default).CopyTo(SendBuf, 26);
                }
                else byr(InpBuff).CopyTo(SendBuf, 26);
            }
            //SpaceFill
            for (int idNil = 26 + BufSize; idNil < 132; idNil++)
                SendBuf[idNil] = b(' ');

            return SendBuf;
        }

        void s_Send(byte data[]) {

            //if (data != null && s!= null)
            {
                try
                {
                    int nbytes = sock.Send(data);
                    if (nbytes > 0)
                    {
                        if (mVib != null)
                        {
                            mVib.Vibrate(30);
                        }
                    }
                }
                catch (IOException ex)
                {
                    DisplayAlert("Error during Send", ex.Message, "OK");
                    mVib.Vibrate(200);
                    PaintWindow();
                }
                catch (System.NullReferenceException nex) {
                    DisplayAlert("Remote Server is not Connected.", "@ MainPage.xaml.cs:808 - "+nex.Message, "Close");
                    PaintWindow();
                }
            }
        }

        Task onVBtnClickAsync(string txt)
        {
            //   DisplayAlert("You Hit", null, Encoding.UTF8.GetString(FinishAccept(txt).ToArray(),"OK");

            int keyCode = 0;
            /*
            KeyData.Add(new _KeyData(KeyTypes.SPL, 'Y', VK_F1, "F1 ", "HL", "HL", "HL"));
            KeyData.Add(new _KeyData(KeyTypes.SPL, 'Y', VK_F2, "F2 ", "HL", "HL", "HL"));
            KeyData.Add(new _KeyData(KeyTypes.SPL, 'Y', VK_F3, "F3 ", "DF", "DF", "DF"));
            KeyData.Add(new _KeyData(KeyTypes.SPL, 'Y', VK_F4, "F4 ", "DF", "DF", "DF"));
            KeyData.Add(new _KeyData(KeyTypes.SPL, 'Y', VK_F5, "F5 ", "DF", "DF", "DF"));
            KeyData.Add(new _KeyData(KeyTypes.SPL, 'Y', VK_F6, "F6 ", "DF", "DF", "DF"));
            KeyData.Add(new _KeyData(KeyTypes.SPL, 'Y', VK_F7, "F7 ", "DF", "DF", "DF"));
            KeyData.Add(new _KeyData(KeyTypes.SPL, 'Y', VK_F8, "F8 ", "DF", "DF", "DF"));
            KeyData.Add(new _KeyData(KeyTypes.SPL, 'Y', VK_F9, "F9 ", "DE", "DE", "DE"));
            KeyData.Add(new _KeyData(KeyTypes.SPL, 'Y', VK_F10, "FA ", "QU", "QU", "QU"));
            KeyData.Add(new _KeyData(KeyTypes.SPL, 'Y', VK_F11, "FB ", "HL", "HL", "HL"));
            KeyData.Add(new _KeyData(KeyTypes.SPL, 'Y', VK_F12, "FC ", "HL", "HL", "HL"));
            KeyData.Add(new _KeyData(KeyTypes.SPL, 'Y', VK_UP, "UA ", "BF", "BF", "BF"));
            KeyData.Add(new _KeyData(KeyTypes.SPL, 'Y', VK_DOWN, "DA ", "DF", "FF", "FF"));
            KeyData.Add(new _KeyData(KeyTypes.SPL, 'E', VK_LEFT, "LA ", "BF", "LF", "BF"));
            KeyData.Add(new _KeyData(KeyTypes.SPL, 'E', VK_RIGHT, "RA ", "DF", "RF", "FF"));
            KeyData.Add(new _KeyData(KeyTypes.SPL, 'Y', VK_PRIOR, "PU ", "BF", "PU", "PU"));
            KeyData.Add(new _KeyData(KeyTypes.SPL, 'Y', VK_NEXT, "PD ", "DF", "PD", "PD"));
                /* vBtn("ESC", r, 0); vBtn("F1", r, 1); vBtn("F2", r, 2); r++;
               vBtn("F3", r, 0); vBtn("seq", r, 1); vBtn("F7", r, 2); r++;
               vBtn("?", r, 0); vBtn("INS", r, 1); vBtn("DEL", r, 2); r++;
               vBtn("abc", r, 0); vBtn("123", r, 1); vBtn("***", r, 2); r++;
               vBtn("Y", r, 0, 711); vBtn("UP", r, 1, 711); vBtn("N", r, 2, 711); r++;
               vBtn("LT", r, 0, 711); vBtn("DN", r, 1, 711);vBtn("RT", r, 2, 711); r++;
               vBtn("ENTER", r, 1, 711, true); */

            if (txt.Length == 1) { s_Send(ComposeAcceptDataMessage(txt)); } //Y N C A R
            if (txt.StartsWith("PgUp")) { s_Send(ComposeAcceptDataMessage("PUPU ", true)); }
            if (txt.StartsWith("PgDn")) { s_Send(ComposeAcceptDataMessage("PDPD ", true)); }
            if (txt.StartsWith("seq")) { Task a = new Task(dbg_userPass51); a.Start(); }
            if (txt.StartsWith("DEL")) { s_Send(ComposeAcceptDataMessage("  DL ", true)); };
            if (txt.StartsWith("F1")) { s_Send(ComposeAcceptDataMessage("HLF1 ", true)); }
            if (txt.StartsWith("F2")) { s_Send(ComposeAcceptDataMessage("HLF2 ", true)); }
            if (txt.StartsWith("F7")) { s_Send(ComposeAcceptDataMessage("DFF7 ", true)); }
            if (txt.StartsWith("UP")) { s_Send(ComposeAcceptDataMessage("BFUA ", true)); }
            if (txt.StartsWith("DN")) { s_Send(ComposeAcceptDataMessage("FFDA ", true)); } //Whyn not DFDA think
            if (txt.StartsWith("LT")) { s_Send(ComposeAcceptDataMessage("BFLA ", true)); }
            if (txt.StartsWith("RT")) { s_Send(ComposeAcceptDataMessage("FFRA ", true)); }
            if (txt.StartsWith("ENT")) { s_Send(ComposeAcceptDataMessage("DFDF ", false, true)); }
            if (txt.StartsWith("ESC")) {
                s_Send(ComposeAcceptDataMessage("QUESC", false, true));
            }
            if (txt.StartsWith("abc") || txt.StartsWith("123") || txt.StartsWith("***"))
            {
                if (AcceptPending)
                {
                    string sh = CurAccept.Default.TrimEnd();
                    var typ = Xamarin.Forms.Keyboard.Text;
                    string title = "Pl Enter ";

                    if (txt.StartsWith("abc")) { typ = Xamarin.Forms.Keyboard.Text; title += "Text"; }
                    if (txt.StartsWith("123")) { typ = Xamarin.Forms.Keyboard.Numeric; title += "Numeric"; }
                    if (txt.StartsWith("***")) typ = Xamarin.Forms.Keyboard.Default;
                    //mVib.Vibrate(80);
                    string result = await DisplayPromptAsync("", title, "Send", "Cancel", CurAccept.Default.TrimEnd(), -1, typ);
                    //await DisplayAlert("Will Send", result, "OK");
                    if (result != null) s_Send(ComposeAcceptDataMessage(result));
                }
                else
                {
                    await DisplayAlert("No Pending Input", null, "OK");
                }
            }
            processKeyCode(keyCode);
        }

        string getProxyIp()
        {
            Application.Current.Properties["Proxy_IP"] = DisplayPromptAsync("Configure IP", "Please Enter Proxy IP Address", "Set", "Cancel", "xxx.xxx.xxx.xxx".TrimEnd(), -1, Xamarin.Forms.Keyboard.Text);
            return Application.Current.Properties["Proxy_IP"].ToString();
        }

        void dbg_userPass51()
        {
            s_Send(ComposeAcceptDataMessage("BILAL"));
            Thread.Sleep(1000);
            s_Send(ComposeAcceptDataMessage("BILAL"));
            Thread.Sleep(1000);
            s_Send(ComposeAcceptDataMessage("51"));
            Thread.Sleep(2000);
            dbg_autoINDV0254();
        }

        void dbg_autoINDV0254()
        {
            s_Send(ComposeAcceptDataMessage("DFF7 ", true));
            Thread.Sleep(1000);
            { s_Send(ComposeAcceptDataMessage("FFDA ", true)); }
            Thread.Sleep(1000);
            { s_Send(ComposeAcceptDataMessage("FFDA ", true)); }
            Thread.Sleep(1000);
            { s_Send(ComposeAcceptDataMessage("DFDF ", false, true)); }
            Thread.Sleep(1000);
            s_Send(ComposeAcceptDataMessage("RUN"));
            Thread.Sleep(1000);
       //     s_Send(ComposeAcceptDataMessage("INDV0254"));
       //     Thread.Sleep(1000);
        //    s_Send(ComposeAcceptDataMessage("BILAL"));
        //    Thread.Sleep(100);
        //    s_Send(ComposeAcceptDataMessage("BILAL"));
        //    Thread.Sleep(100);
        //    s_Send(ComposeAcceptDataMessage("51"));
        //    Thread.Sleep(100);
        }

        void processKeyCode(int keyCode)
        {
            
        }

        class XY {
            int x, y;
        };
        
        XY getBtnId(int mX, int mY)
        {
            
            XY xy = new XY();
            return xy;
        }

        bool firsttime = true;

       
        void canvasView_PaintSurface(object sender, SKPaintSurfaceEventArgs e)
        {
            SKCanvas canvas = e.Surface.Canvas;
            //canvas.Clear(SKColors.CornflowerBlue);

            using (var paint = new SKPaint())
            {
                paint.TextSize = TextSize;
                paint.IsAntialias = true;
                byte R = 0x00;
                if (sock == null) R = 0xFF;
                try
                {
                    if (sock != null && sock.Available == 0) { R = 0xAA; }
                }
                catch (System.ObjectDisposedException odx) { }
                paint.Color = new SKColor(R, 0x00, 0x00);
                paint.IsStroke = false;
                paint.IsLinearText = true;
                SetCanvasPaintRef(e.Surface, paint);

                {
                    MDrawBatch();
                    canvasView.InvalidateSurface();
                }

                PaintWindow();
            }
        }

        const int MAX_WINDOWS = 20;
        int MaxRow = 25;
        int MaxCol = 80;


        void PaintWindow()
        {

            if (CurWindow < 0) return;//dont paint until vars are set

            int mf;
            if (CurWindow >= MAX_WINDOWS)
            {
                CurWindow = MAX_WINDOWS - 1;
            }
            int RectTop, RectLeft, RectBot, RectRight;
            RectTop = 0;
            RectLeft = 250;

            RectBot = (MaxRow - 1);
            RectRight = (MaxCol - 1);

            DisplayWindow(CurWindow, RectTop, RectLeft, RectBot, RectRight);
        }

        void DisplayWindow(int curWindow, int rectTop, int rectLeft, int rectBot, int rectRight)
        {
           // canvas.Restore(SavedBM[curWindow].hbitmap);
        }

        SKPoint GetSIOPoint(int row, int col)
        {
            int xw = 22, yw = 42;
            int px = col * xw;
            int py = yw + row * yw;
            return new SKPoint(px, py);
        }

        SKPoint GetSIOPoint0(string v2)
        {

            string rowsz = v2.Substring(3 + 0, 3);
            string colsz = v2.Substring(3 + 3, 3);
            int row = Convert.ToInt32(rowsz) - 1;
            int col = Convert.ToInt32(colsz) - 1;
            int xw = 15, yw = CellHeight;
            return new SKPoint(col * xw, CellHeight + row * yw);
        }

        SKPoint GetSIOPoint(string v2)
        {
            string rowsz = v2.Substring(3 + 0, 3);
            string colsz = v2.Substring(3 + 3, 3);

            int row = Convert.ToInt32(rowsz) - 1;
            int col = Convert.ToInt32(colsz) - 1;
            int xw = CellWidth, yw = CellHeight;
            return new SKPoint(col * xw, yw + row * yw);
        }

        SKPoint GetSIOPoint3(string v2)
        {
            string rowsz = v2.Substring(3 + 0, 3);
            string colsz = v2.Substring(3 + 3, 3);

            rowsz = v2.Substring(8 + 3, 3);
            colsz = v2.Substring(11 + 3, 3);
            int row = Convert.ToInt32(rowsz) - 1;
            int col = Convert.ToInt32(colsz) - 1;
            int xw = 22, yw = 42;
            return new SKPoint(col * xw, yw + row * yw - 10);//-10 is just visual correction
        }

        string GetSIOText(string spec, string stxt)
        {
            return stxt;//.Replace(' ','_');
        }

        int ConvertBufNum(string b, int start, int len)
        {
            
            int ret = 0;
            try
            {
                string s = b.Substring(start, len);
                ret = Convert.ToInt32(s);
            }
            catch (System.Exception ex) { }
            return ret;
        }

        int min(int a, int b)
        {
            if (a <= b) return a; else return b;
        }

        int max(int a, int b)
        {
            if (a >= b) return a; else return b;
        }
        void DisplayHLine(SKCanvas canvas, SKPaint paint, int strrow, int endrow, int strcol, int endcol, int color, int type, int thick, int tag)
        {
            RenderHLineTran(canvas, paint, strrow, endrow, strcol, endcol, thick, color, type);
        }

        int CellWidth = 22, CellHeight = 42;
        int TextSize = 36;

        int StdColorMap[100] =
 {
    //    SIO1    SIO2    FRed    FGreen    FBlue    BRed    BGreen    BBlue
        0,      701,    0,      0,      0,      255,    255,    255, //white
        1,      711,    0,      0,      0,      225,    225,    255, //LightBlueish
        2,      721,    0,      0,      0,      225,    255,    225,
        3,      731,    0,      0,      0,      225,    255,    255,
        4,      741,    0,      0,      0,      255,    168,    168,
        5,      751,    0,      0,      0,      255,    225,    255,
        6,      761,    0,      0,      0,      255,    255,    225,
        7,      771,    0,      0,      0,      255,    255,    255,
        -1,     -1,     192,    192,    128,    192,    192,    192
};
        SKColor ResolveSIOColor(int c)
        {

            byte r = 0, g = 0, b = 0;
            int sio2 = 0;
            for (int ro = 0; ro < 8 * 8; ro += 8)
            {
                sio2 = StdColorMap[ro + 1];
                r = (byte)StdColorMap[ro + 5];
                g = (byte)StdColorMap[ro + 6];
                b = (byte)StdColorMap[ro + 7];
                if (sio2 == c)
                    break;
            }
            if (c == -1) { r = 192; g = 192; b = 192; } //Workaround for last row, correct Later 8*8 needs correction
            if (c == -2) { r = 0; g = 0; b = 0; } //Added For Black = N/A
            if (c == 70 ) { r = 0; g = 0; b = 0; } //Added For Black
            if (c == 711) { r = 225; g = 225; b = 255; }
            SKColor clr = new SKColor(r, g, b);
            return clr;
        }

        SKRect RenderBoxTran(int Row, int Left, int EndRow, int Right, int Foreground, int Thick, bool Outline, bool Fill, int ClearLine, int Background)
        {
            SKRect actual = new SKRect();
            SKColor linecolor = new SKColor(0, 0, 255);

            if (Left == 20 && Right == 79)
            {
                int a = 0;
            }

            int THICKCORRECTION = 1;

            SKColor skc = paint.Color;
            SKPaintStyle skp = paint.Style;
            float sw = paint.StrokeWidth;

            int xl = (Left - 1) * CellWidth;
            int yt = (Row) * CellHeight;
            int xr = (Right + 1) * CellWidth;
            int yb = (EndRow + 1) * CellHeight;
            actual.Left = xl;
            actual.Right = xr;
            actual.Top = yt;
            actual.Bottom = yb;
            if (Outline)
            {
                
                paint.StrokeWidth = Thick * THICKCORRECTION;
                paint.Color = linecolor;
                paint.Style = SKPaintStyle.Stroke;
               // SKRect rect = new SKRect(xl + 1, yt + 1, xr, yb);
                canvas.DrawLine(pt(new SKPoint(xl, yt)), pt(new SKPoint(xl, yb)), paint);
                canvas.DrawLine(pt(new SKPoint(xl, yb)), pt(new SKPoint(xr, yb)), paint);
                canvas.DrawLine(pt(new SKPoint(xr, yb)), pt(new SKPoint(xr, yt)), paint);
                canvas.DrawLine(pt(new SKPoint(xr, yt)), pt(new SKPoint(xl, yt)), paint);
            }

            if (Fill)
            {
                paint.StrokeWidth = Thick * THICKCORRECTION;
                paint.Color = ResolveSIOColor(Foreground);
                //if (Foreground == 761) paint.Color = linecolor;
                SKRect rect = RectFromRowCol(Left, Row, Right, EndRow);
                paint.Style = SKPaintStyle.StrokeAndFill;
                canvas.DrawRect(rect, paint);
            }

            paint.StrokeWidth = sw;
            paint.Style = skp;
            return actual;
        }

        SKRect RectFromRowCol(int Left, int Row, int Right, int EndRow)
        {
            int xl = (Left - 1) * CellWidth;
            int yt = (Row) * CellHeight;
            int xr = (Right + 1) * CellWidth;
            int yb = (EndRow + 1) * CellHeight;
            SKPoint ptx = pt(new SKPoint(0, 0));
            SKRect rect = new SKRect(ptx.X + xl + 1, ptx.Y + yt + 1, ptx.X + xr, ptx.Y + yb);
            return rect;
        }
        void RenderHLineTran(SKCanvas canvas, SKPaint paint, int Row, int EndRow, int Left, int Right, int Thick, int Foreground, int Type)
        {
            
            if (Left == Right && Left != 0)
            {
                Left = Right;
            }
            SKColor linecolor;
            //    Thick lines used for outlines
            if (Type == 1)
            {

                {
                    int xl = (Left) * CellWidth;
                    int yt = (Row) * CellHeight;
                    int xr = (Right) * CellWidth;
                    int yb = (EndRow) * CellHeight;

                    linecolor = SKColors.Blue;
                    paint.StrokeWidth = Thick;
                    paint.Color = linecolor;
                    canvas.DrawLine(pt(new SKPoint(xl, yt)), pt(new SKPoint(xr, yb)), paint);
                }

            }

            //    Thin horizontal seperators, bottom of character box
            if (Type == 2)
            {

                int t = max(Thick / 2, 1);
                int xl = (Left) * CellWidth;
                int yt = (Row + 1) * CellHeight - 1 - 2 * t; //(FONT_OFFSET-t*2); //- t*2
                int xr = (Right + 1) * CellWidth;
                int yb = (EndRow + 1) * CellHeight - 1 - 2 * t; //(FONT_OFFSET-t*2);// - t*2;

                linecolor = SKColors.DarkGray;
                paint.StrokeWidth = Thick;
                paint.Color = linecolor;
                canvas.DrawLine(pt(new SKPoint(xl, yt)), pt(new SKPoint(xr, yb)), paint);
                canvas.DrawLine(pt(new SKPoint(xl, yt + t)), pt(new SKPoint(xr, yb + t)), paint);
            }

            //    Thin vertical seperators
            if (Type == 3)
            {
                //        SelectObject(hdc, (HGDIOBJ) FontHandles[MainFont]);
                //        SetFontData(hdc, &CharWidth, &CharHeight, &NumberWidth);

                int t = max(Thick / 2, 1);
                int xl = (Left) * CellWidth - CellWidth / 2 - 2 * t;
                int yt = (Row) * CellHeight - 1; //(FONT_OFFSET-t*2); //- t*2
                int xr = (Right) * CellWidth - CellWidth / 2 - 2 * t;
                int yb = (EndRow + 1) * CellHeight; //(FONT_OFFSET-t*2);// - t*2;

                linecolor = SKColors.DarkGray;
                paint.StrokeWidth = Thick;
                paint.Color = linecolor;
                canvas.DrawLine(pt(new SKPoint(xl, yt)), pt(new SKPoint(xr, yb)), paint);
                canvas.DrawLine(pt(new SKPoint(xl + t, yt)), pt(new SKPoint(xr + t, yb)), paint);

            }

            //    Thin horizontal seperators, top of character box
            if (Type == 4)
            {
                //        SelectObject(hdc, (HGDIOBJ) FontHandles[MainFont]);
                //        SetFontData(hdc, &CharWidth, &CharHeight, &NumberWidth);

                //        int t = max(Thick/2,1);
                int t = 1;
                int xl = (Left) * CellWidth;
                int yt = (Row) * CellHeight - 1;
                int xr = (Right) * CellWidth;
                int yb = (EndRow) * CellHeight - 1;

                linecolor = SKColors.DarkGray;
                paint.StrokeWidth = Thick;
                paint.Color = linecolor;
                canvas.DrawLine(pt(new SKPoint(xl, yt)), pt(new SKPoint(xr, yb)), paint);
                canvas.DrawLine(pt(new SKPoint(xl, yt + t)), pt(new SKPoint(xr, yb + t)), paint);

            }

            //    Thin horizontal seperators, top of character box
            if (Type == 5)
            {

                int xl = (Left) * CellWidth;
                int yt = (Row) * CellHeight + 1;
                int xr = (Right+1) * CellWidth;
                int yb = (EndRow + 1) * CellHeight - 1;
                int t = yb - yt;

                linecolor = SKColors.YellowGreen;  /*VISUAL VERIFICATION , IF NOT ok USE fOREGROUND PARAM*/
                paint.StrokeWidth = Thick;
                paint.Color = linecolor;
                canvas.DrawLine(pt(new SKPoint(xl, yt + 2)), pt(new SKPoint(xr, yt + 2)), paint);
            }

        }

        void MDrawBox(string b, SKCanvas canvas, SKPaint paint, int MsgSize)
        {
            int row;
            int col;
            int siz;
            int DispColr;
            int mtype;
            int mthick;
            int high;
            bool outline;
            bool fill;
            int mtag;
            int MSG_HDR = 0;
            //    COBOL/SIO starts numbering row/column at 1, C starts at 0.
            row = ConvertBufNum(b, MSG_HDR, 3) - 1;
            col = ConvertBufNum(b, MSG_HDR + 3, 3) - 1;
            siz = ConvertBufNum(b, MSG_HDR + 6, 3);
            high = ConvertBufNum(b, MSG_HDR + 9, 3);
            mtype = ConvertBufNum(b, MSG_HDR + 12, 3);
            mthick = ConvertBufNum(b, MSG_HDR + 15, 3);
            outline = (b[MSG_HDR + 18] == 'Y');
            fill = (b[MSG_HDR + 19] == 'Y');
            DispColr = ConvertBufNum(b, MSG_HDR + 20, 3);
            mtag = ConvertBufNum(b, MSG_HDR + 23, 3);
            RenderBoxTran(row, col + 1, row + high, col + siz, DispColr, mthick, outline, fill, mtype, mtag);
            //canvas.DrawLine()
        }

        void MDrawLine(string b, SKCanvas canvas, SKPaint paint, int MsgSize)
        {
            int row;
            int col;
            int siz;
            int DispColr;
            int type;
            int thick;
            int tag;
            int high;
            int MSG_HDR = 0;
            //    COBOL/SIO starts numbering row/column at 1, C starts at 0.
            row = ConvertBufNum(b, MSG_HDR, 3) - 1;
            col = ConvertBufNum(b, MSG_HDR + 3, 3) - 1;
            siz = ConvertBufNum(b, MSG_HDR + 6, 3);
            type = ConvertBufNum(b, MSG_HDR + 9, 3);
            thick = ConvertBufNum(b, MSG_HDR + 12, 3);
            DispColr = ConvertBufNum(b, MSG_HDR + 15, 3);
            tag = ConvertBufNum(b, MSG_HDR + 18, 3);
            high = MsgSize > (MSG_HDR + 22) ? ConvertBufNum(b, MSG_HDR + 21, 3) : row;
            DisplayHLine(canvas, paint, row, row + high, col, (col + siz < 80 ? col + siz : 80), DispColr, type, thick, tag);
            //canvas.DrawLine()
        }

        std::list<PCSMessage> test_data;

        string correctDDtext(string spec, string ddtext)
        {
            int siz = ConvertBufNum(spec, 3 + 6, 3);

            int alen = ddtext.TrimEnd().Length;

            int numspaceddeficient = siz - alen;

            string ddR = ddtext.TrimEnd();

            for (int i = 1; i <= numspaceddeficient; i++)
            {
                ddR += " ";
            }

            int lnow = ddR.Length;

            // Remove Extra Space?
            if (ddR.Length > 2 && ddR[0] == ' ' && ddR[1] != ' ') ddR = ddR.TrimStart();

            return ddR;
        }

        void DisplayData(int row, int col, int siz, char ActColrDisp, int DispColr, string c, _PCSFontAttributes fa, int tag, bool fe)
        {

            int Color;
            string Data;

            if (CurWindow < 0) return;


            //        After an accept, TBSAD will trigger a redisplay.  If the accept used an Offset amount (For
            //        word-wrapping), apply it to the next display.
            if (CurAccept.SizOff > 0)
            {
                siz = siz - CurAccept.SizOff;
                CurAccept.SizOff = 0;
            }

            _WindowData wd = FindWD(CurWindow);
            if (wd == null) return;

            Color = wd.ColorScreen;
            if (ActColrDisp == 'D') Color = DispColr;
            if (ActColrDisp == 'H') Color = wd.ColorHelp1;

            if (row == wd.Ins_row - 1)
                if (wd.Ins_col - 1 >= col)
                    if (wd.Ins_col - 1 <= (col + siz))
                        wd.Ins_color = Color;


            Data = c;

            string d = Data;
            int SpcCnt = d.Length - d.Replace(" ", "").Length;

            bool CheckA = (Data.Length == 1 && Data[0] == ' ' );
            bool CheckB = (SpcCnt == Data.Length);
            bool CheckC = (col == (wd.StartCol - 1));
            bool CheckD = (siz >= (wd.EndCol - wd.StartCol - 1));

            PrintMessage(canvas, paint, Data, row, col, siz, Color, fa, tag, fe);
        }
        void MDrawText(SKCanvas canvas, SKPaint paint, string spec, string astxt, int bgColor = 731, int fgColor = -1/*Grey*/)
        {
            if (CurWindow < 0) return;
            paint.Color = new SKColor(0, 0, 255);
            paint.Typeface = SKTypeface.FromFamilyName("Courier");
            string stxt = GetSIOText(spec, astxt);

            if (stxt.Length > 0)
            {
                SKPaintStyle ps = paint.Style;
                paint.Style = SKPaintStyle.StrokeAndFill;
                SKPoint p = pt(GetSIOPoint(spec));

                //_DrawText(canvas, stxt.Replace(' ','.'), p, paint);

                int nCHARs = 0;
                string ddR = correctDDtext(spec, stxt);

                short TEXTYCORR = 0;
                SKPoint ptx = pt(new SKPoint(0, 0));
                SKRect r = new SKRect();
                r.Left = ptx.X + p.X;
                r.Top = ptx.Y + p.Y - TextSize + TEXTYCORR;
                r.Bottom = ptx.Y + p.Y + TEXTYCORR + 5;
                r.Right = ptx.X + p.X + CellWidth * ddR.Length;

                foreach (char c in ddR.TrimStart())
                {
                    if (c != ' ') nCHARs++;
                }
                if (nCHARs == 0)
                {
                    paint.Style = SKPaintStyle.StrokeAndFill;
                    if (CurWindow > -1)
                    {
                        SKColor paint_Color = ResolveSIOColor(bgColor);
                        paint.Color = paint_Color;
                    }

                    canvas.DrawRect(r, paint);
                }
                else
                {
                    SKPaintStyle ps0 = paint.Style;
                    SKColor cl0 = paint.Color;
                    paint.Style = SKPaintStyle.StrokeAndFill;
                    if (CurWindow > -1)
                        paint.Color = ResolveSIOColor(bgColor);
                    //    if (bgColor == 70) paint.Color =  new SKColor(0, 0, 0);
                    canvas.DrawRect(r, paint);
                    paint.Style = ps0;
                    paint.Color = cl0;
                    paint.Color = ResolveSIOColor(fgColor);
                    _DrawText(canvas, ddR, p, paint);


                }
                paint.Style = ps;
            }
        }

        SKPoint pt(SKPoint p)
        {
            p.X = p.X + 50;//Left Border
            return p;
        }

        class ACCEPTDATA
        {
            string str(int n) { return new string(' ', n); }

            ACCEPTDATA()
            {
                Seq = str(8);
                Default = str(133);
                SavedScreen = str(160);
                Type = str(3);
                RtnCmd = str(3);
                RtnKey = str(4);
                ConvertCase = str(3);
                CmdSet = str(3);
            }

            string Seq;
            int StrPos;
            int SizOff;
            string SavedScreen;
            int Row;
            int Col;
            int CurPosition;
            string Type;
            int Siz;
            int Color;
            int ActColrAcpt;
            string RtnCmd;
            string RtnKey;
            string ConvertCase;
            string CmdSet;
            int Highlight;
            int CPos;
            char ActF1, ActF2, ActF3, ActF4, ActF9, ActFA, ActQUE, Act99, ActBF, ActF5, ActF6, ActF7, ActF8, PreDispDef, ConcealPass, Timeout;
            int TimeoutSec, Counter;
            bool InsertMode;
            short MouseX, MouseY;
            bool EraseBuffer;
            bool FirstChar;
            _PCSFontAttributes FontAttributes;
            bool ExpandField;
            bool AllowDrag;
            string Default;
        };

        bool AcceptPending = false;
        int CaretOn = 0;
        bool ButtonsEnabled = false;
        bool DragForNextAccept = false;
        bool CalForNextAccept = false;
        double FONT_PERCENT = 0.75;
        int FONT_OFFSET = 3;
        double EXPAND_DISPLAY = 0.25;
        ClientMode PCSMode = ClientMode::NORMALMODE;
        int InpIdx = 0;
        char InpBuffr[128];
        int CurWindow = -1;
        _WindowTable Window[15];
        ACCEPTDATA CurAccept;// = new ACCEPTDATA();

        int MainFont = 0;
        struct _PCSFontAttributes
        {
            int FontNumber;   // Font number, mapped to fonts in the client, 1...999
            int FontSize;   // Font size, 100 = normal size, 200 = double size
            int FontWeight;   // Weight, 400 = normal, 700=bold
            bool FontItalics;
            bool FontUnderline;
            bool FontStrikeout;
            uint HorizAlign;
            uint VertAlign;
            int ForegroundColor;
            int BackgroundColor;
            bool Outline;
        };


        int LastWinLoaded = 0;

        void LoadWindowParms(string w)
        {

            int MSG_HDR = 0;
            int i, j;

            int win = ConvertBufNum(w, MSG_HDR, 3);
            win--;

            //  Reconnect = TRUE;

            CurWindow = win;

            _WindowData wd;

            LastWinLoaded = win;

            wd = Window[win].WindowTrans;

            if (wd == null)
            {
                //        int cw = CurWin;
                //        CurWin = win;
                wd = FindPoolEnd();
                //        CurWin = cw;
                // Is this zero memory causing the exe exception 8/19/19??
                // After removing this zero memory, it did not get the data exception
                // but when it reconnected it displayed the screen but keyboard did not work.
                // How does this reconnect logic work?
                //        ZeroMemory(wd, sizeof(*wd));
            }
            //    Out of memory
            if (wd == null) return;

            Window[win].WindowTrans = wd;

            wd.WindowNumber = win;
            int offset = MSG_HDR + 3;
            wd.StartRow = ConvertBufNum(w, offset + 0, 3);
            wd.StartCol = ConvertBufNum(w, offset + 3, 3);
            wd.EndRow = ConvertBufNum(w, offset + 6, 3);
            wd.EndCol = ConvertBufNum(w, offset + 9, 3);
            wd.Outline = w[offset + 12];
            wd.ActiveColorDisplay = w[offset + 13];
            wd.ActiveColorAccept = w[offset + 14];
            wd.ColorScreen = ConvertBufNum(w, offset + 15, 3);
            wd.ColorDisplay = ConvertBufNum(w, offset + 18, 3);
            wd.ColorField = ConvertBufNum(w, offset + 21, 3);
            wd.ColorAccept = ConvertBufNum(w, offset + 24, 3);
            wd.ColorFChg = ConvertBufNum(w, offset + 27, 3);
            wd.ColorError = ConvertBufNum(w, offset + 30, 3);
            wd.ColorHelp1 = ConvertBufNum(w, offset + 33, 3);
            wd.ColorHelp4 = ConvertBufNum(w, offset + 36, 3);
            wd.Line = ConvertBufNum(w, offset + 39, 3);
            wd.Position = ConvertBufNum(w, offset + 42, 3);
            wd.Size = ConvertBufNum(w, offset + 45, 3);
            wd.Highlight = ConvertBufNum(w, offset + 48, 3);
            wd.DisplayNow = w[offset + 51];
            wd.AcceptNow = w[offset + 52];
            wd.ConcealPassword = w[offset + 53];
            wd.ConvertCase = w.Substring(offset + 54, 3);//strncpy_s(wd.ConvertCase, 3, &w[offset + 54], _TRUNCATE);
            wd.Echo = w[offset + 56];
            wd.ReturnSpecialKey = w[offset + 57];
            wd.CommandSet = w.Substring(offset + 58, 3);// strncpy_s(wd.CommandSet, 3, &w[offset + 58], _TRUNCATE);
            wd.MemoSet = w[offset + 60];
            //Filler X(6)
            wd.DisplayError = w[offset + 67];
            wd.DisplayWarn = w[offset + 68];
            wd.Warn = w.Substring(offset + 69, 3);// strncpy_s(wd.Warn, 3, &w[offset + 69], _TRUNCATE);
            wd.ErrorClear = w[offset + 70];
            wd.ErrorWait = w[offset + 71];
            wd.ErrorLne = ConvertBufNum(w, offset + 73, 3);
            wd.ErrorPos = ConvertBufNum(w, offset + 76, 3);
            wd.ErrorSiz = ConvertBufNum(w, offset + 79, 3);
            wd.ScnNo = w.Substring(offset + 82, 3);// .. strncpy_s(wd.ScnNo, 4, &w[offset + 82], _TRUNCATE);
            wd.FixedPitch = (w[offset + 85] == 'Y');

            j = 86;
            for (i = 0; i < 6; i++)
            {
                wd.Help[i].Use = w[offset + j];
                j++;
                wd.Help[i].Splf = w[offset + j];
                j++;
                wd.Help[i].Lne = ConvertBufNum(w, offset + j, 3);
                j += 3;
                wd.Help[i].Pos = ConvertBufNum(w, offset + j, 3);
                j += 3;
                wd.Help[i].Siz = min(ConvertBufNum(w, offset + j, 3), 40);
                j += 3;
            }
            wd.MaxRow = max(WindowHeight, wd.EndRow);
            wd.MaxCol = max(WindowWidth, wd.EndCol);
            wd.TO_row = wd.MaxRow;
            wd.TO_col = 1;
            wd.Ins_row = wd.MaxRow;
            wd.Ins_col = wd.MaxCol;
            wd.Ins_color = wd.ColorScreen;

            MakeBitmap(wd);
            //                char m[256];
            //                sprintf_s(m,sizeof(m),"Erasing window %d via LoadWindowParms (%d)", win, FindWD(win)?FindWD(win)->FontNum:999);
            //                DisplayMessage(strlen(m),m);
            SIOEraseWindow(win);
        }




        _WindowData FindWD(int cw)
        {
            _WindowData wd;
            if (cw < 0) wd = null;
            else
            {
                wd = Window[cw].WindowTrans;
            }
            return wd;
        }

        int WindowWidth = 80;
        int WindowHeight = 25;

        void RenderTextTran(int win, string Text, _PCSFontAttributes fa, System_Drawing_Rectangle Loc, int Fore, bool ClearLine, short Background, bool fld_expand, bool Multiline)
        {
            long fc, bc;
            int col;
            int x, y;
            short Color;
            byte Attribs;
            _WindowData wd = FindWD(win);
            int offset = 0;
            bool ExpandField = false;
            bool NewWindow = false;

            int size = (Loc.Right - Loc.Left) + 1;
            int height = (Loc.Bottom - Loc.Top) + 1;
            if (size == 0) return;

            if (wd.FontNum == -1)
            {
                wd.FontNum = fa.FontNumber;
                NewWindow = true;
            }

        }

        //Wrapper for canvas.DrawText
        int corrY = 6;
        void _DrawText(SKCanvas canvas, string txt, SKPoint p, SKPaint paint)
        {
            canvas.DrawText(txt, pt(new SKPoint(p.X, p.Y - corrY)), paint);
        }

        void PrintMessageAcpt(SKCanvas canvas, SKPaint paint, string message, int row, int col, int siz, int color, _PCSFontAttributes fa, int tag, bool fe)
        {
            if (row < 0) row = 0;
            if (col < 0) col = 0;
            if ((col + siz) > 80) siz = 80 - col;//correction for extra going offscreen
            EraseFill(SKColors.DarkSlateGray, col + 1, row + 1/*1=H&T*/, col + siz, row + 1);
            SKPoint p = (GetSIOPoint(row, col));
            paint.Typeface = SKTypeface.FromFamilyName("Courier");
            paint.Color = ResolveSIOColor(color);
            _DrawText(canvas, message, p, paint);
            paint.Color = SKColors.White;//print Caret
            _DrawText(canvas, "_", p, paint);
            //    MDrawText(canvas,paint,"",message,color);
            //RECT r;
            //SetRect(&r, (col) * CharWidth, (row) * CharHeight,
            //        (col + siz) * CharWidth, (row + 1) * CharHeight);
            //InvalidateRect(PCSDialogWindow, NULL, FALSE);
        }

        void PrintMessage(SKCanvas canvas, SKPaint paint, string message, int row, int col, int siz, int color, _PCSFontAttributes fa, int tag, bool fe)
        {
            if (paint == null) return;
            if (canvas == null) return;
            if (row < 0) row = 0;
            if (col < 0) col = 0;
            if ((col + siz) > 80) siz = 80 - col;//correction for extra going offscreen
            EraseFill(ResolveSIOColor(color), col + 1, row + 1/*1=H&T*/, col + siz, row + 1);
            SKPoint p = (GetSIOPoint(row, col));
            paint.Typeface = SKTypeface.FromFamilyName("Courier");
            paint.Color = SKColors.Black;
            if (color == 70) paint.Color = SKColors.White;//Bg Black Text White
            _DrawText(canvas, message, p, paint);
            //    MDrawText(canvas,paint,"",message,color);
            //RECT r;
            //SetRect(&r, (col) * CharWidth, (row) * CharHeight,
            //        (col + siz) * CharWidth, (row + 1) * CharHeight);
            //InvalidateRect(PCSDialogWindow, NULL, FALSE);
        }

        void DisplayHelp(SKCanvas canvas, SKPaint paint, int cw, int i, int help_text, string b)
        {
            _WindowData wd = FindWD(cw);
            if (wd == null) return;
            if (wd.Help[i].Use != 'Y') return;

            byte[] HelpText = new byte[256];
            
            int helpsiz = min(HelpText.Length, wd.Help[i].Siz);
      //      string chk = b.Substring(help_text, helpsiz);
            
            {
                for (int ij = 0; ij < 133; ij++) { HelpText[ij] = 0; }
                //HelpText[132] = 0;
                _PCSFontAttributes fa = new _PCSFontAttributes();
                if (wd.FontNum == -1) fa.FontNumber = MainFont;
                fa.FontNumber = 0;
                fa.FontSize = 100;
                fa.FontWeight = 400;
                HELP hl = wd.Help[i];

                b = b + "                                                                                                                                                       ";

                for (int k = 0; k < helpsiz; k++)
                {
                    try
                    {
                        HelpText[k] = (byte)b[help_text + k];
                    }
                    catch (IndexOutOfRangeException e) {
                        HelpText[k] = 0;
                    }
                }


                string strHelpText = b.Substring(help_text, helpsiz);
                PrintMessage(canvas, paint, strHelpText, hl.Lne - 1, hl.Pos - 1, hl.Siz,
                    (i < 4 ? wd.ColorHelp1 : wd.ColorHelp4), fa, 0, false);

                bool TopHelp = true;
                for (int j = 0; j < 6; j++) if ((j != i) && (wd.Help[j].Lne < hl.Lne)) TopHelp = false;
                if (TopHelp) RenderHLineTran(canvas, paint, hl.Lne - 1, hl.Lne - 1, hl.Pos - 1, hl.Pos - 1 + hl.Siz,
                                1, (i < 4 ? wd.ColorHelp1 : wd.ColorHelp4), 4);//, false, (i < 4 ? wd.ColorHelp1 : wd.ColorHelp4));

                //    This only works well for full-screen browses.
                if (wd.Outline != 'Y')
                {
                    bool LeftHelp = true;
                    for (int j = 0; j < 6; j++) //This is NOT a left help line if...
                        if ((j != i)            //Skip this line
                            && (wd.Help[j].Use == 'Y')     // It's in use
                            && (wd.Help[j].Lne == hl.Lne) // There's another help on this line
                            && (hl.Pos > wd.Help[j].Pos)) // Theres something to our left
                            LeftHelp = false;
                    if (LeftHelp) RenderHLineTran(canvas, paint, hl.Lne - 1, hl.Lne - 1, hl.Pos + hl.Siz - 1, hl.Pos + hl.Siz - 1,
                                    1, (i < 4 ? wd.ColorHelp1 : wd.ColorHelp4), 3);//, FALSE, (i < 4 ? wd.ColorHelp1 : wd->ColorHelp4));
                }
            }
            //catch (System.Exception ex) {
            //    Console_WriteLine("String Err");
            //}
        }


        void MAcceptData(SKCanvas canvas, SKPaint paint, string txt, string t3, char A_type)
        {
            int i;
            _WindowData wd;
            AcceptPending = true;
            CurAccept.FirstChar = true;
            CurAccept.ExpandField = true;
            CurAccept.AllowDrag = false;
            if (DragForNextAccept)
            {
                DragForNextAccept = false;
                CurAccept.AllowDrag = true;
            }


            int offset = 3, default_offset = 3;
            string b = t3;
            int ADVersion = 1;


            string ADV;
            ADV = b.Substring(0, 2);

            if (ADV.StartsWith("V2"))
            {
                offset = 3;
                ADVersion = 2;
                default_offset = 3;
            }

            wd = FindWD(CurWindow);
            if (wd == null) return;

         //   CopyBitmap(wd);

            CurAccept.Type = "A" + Convert.ToString(A_type);

            if (A_type == 'E')
            {
                CurAccept.Row = wd.ErrorLne - 1;
                CurAccept.Col = wd.ErrorPos - 1 - 1;
                CurAccept.Siz = 1;
                CurAccept.Color = wd.ColorError;
                CurAccept.ActColrAcpt = 'A';
                CurAccept.Default = "";
            }
            else //AD
            {
                CurAccept.Row = ConvertBufNum(b, offset + 8, 3) - 1;
                CurAccept.Col = ConvertBufNum(b, offset + 11, 3) - 1;
                CurAccept.Siz = ConvertBufNum(b, offset + 14, 3);
                CurAccept.Color = ConvertBufNum(b, offset + 24, 3);
                CurAccept.ActColrAcpt = b[offset + 23];
                try
                {
                    CurAccept.Default = b.Substring(offset + 302 + default_offset);
                }
                catch (System.ArgumentOutOfRangeException e) {
                    CurAccept.Default = "";
                }
            }

            string Seq = b.Substring(offset, 8);
            if (Seq == CurAccept.Seq)
            {
                CurAccept.StrPos = 2;
                CurAccept.SizOff = 0;
            }
            CurAccept.Seq = Seq;
            CurAccept.Highlight = ConvertBufNum(b, offset + 17, 3);
            CurAccept.CPos = ConvertBufNum(b, offset + 20, 3);
            CurAccept.ActF1 = b[offset + 27];
            CurAccept.ActF2 = b[offset + 28];
            CurAccept.ActF3 = b[offset + 29];
            CurAccept.ActF4 = b[offset + 30];
            CurAccept.ActF9 = b[offset + 31];
            CurAccept.ActFA = b[offset + 32];
            CurAccept.ActQUE = b[offset + 33];
            CurAccept.Act99 = b[offset + 34];
            CurAccept.ActBF = b[offset + 35];
            CurAccept.ActF5 = b[offset + 36];
            CurAccept.ActF6 = b[offset + 37];
            CurAccept.ActF7 = b[offset + 38];
            CurAccept.ActF8 = b[offset + 39];
            CurAccept.CmdSet = b.Substring(offset + 40, 3 - 1);
            CurAccept.PreDispDef = b[offset + 42];
            CurAccept.ConcealPass = b[offset + 43];
            CurAccept.ConvertCase = b.Substring(offset + 44, 3 - 1);
            CurAccept.Timeout = b[offset + 46];
            CurAccept.TimeoutSec = ConvertBufNum(b, offset + 47, 3);
            CurAccept.MouseX = 0;
            CurAccept.MouseY = 0;

            if (CurAccept.ActColrAcpt != 'A') CurAccept.Color = wd.ColorScreen;

            int Default_location = 302 + offset + default_offset;
            int ReadBufSize = txt.Length;//////////////////////<<<<TUKKA
            if ((ReadBufSize > Default_location) && (ReadBufSize < (Default_location + 132)))
            {
                int st = ReadBufSize - (Default_location);
                int se = 132 - (ReadBufSize - (Default_location));
                //    ZeroMemory(&CurAccept.Default[ReadBufSize - (Default_location)], 132 - (ReadBufSize - (Default_location)));
            }
            if (ReadBufSize <= Default_location) //ZeroMemory(&CurAccept.Default, 132);
                CurAccept.Default = "";//?

            if ((CurAccept.Color == 110) || (CurAccept.Color == 220) || (CurAccept.Color == 330)
                || (CurAccept.Color == 440) || (CurAccept.Color == 550) || (CurAccept.Color == 660)
                || (CurAccept.Color == 770) || (CurAccept.Color == 880))
            {
                CurAccept.ConcealPass = 'Y';
                CurAccept.PreDispDef = 'N';
            }

            CurAccept.FontAttributes.FontNumber = ConvertBufNum(b, offset + 50, 3) - 1;
            CurAccept.FontAttributes.FontSize = ConvertBufNum(b, offset + 53, 3);
            CurAccept.FontAttributes.FontWeight = ConvertBufNum(b, offset + 56, 3);
            CurAccept.FontAttributes.FontItalics = (b[59 + offset] == 'Y');
            CurAccept.FontAttributes.FontUnderline = (b[60 + offset] == 'Y');
            CurAccept.FontAttributes.FontStrikeout = (b[61 + offset] == 'Y');
            CurAccept.FontAttributes.HorizAlign = 0;
            CurAccept.FontAttributes.VertAlign = 0;
            CurAccept.FontAttributes.BackgroundColor = 0;
            CurAccept.FontAttributes.ForegroundColor = 0;
            CurAccept.FontAttributes.Outline = false;

            if (ADVersion >= 2)
            {
                if (b.Length < 70) b = b + spaces.Substring(1,10);//add some padding
                CurAccept.ExpandField = (b[62 + offset] != 'N');
                CurAccept.FontAttributes.HorizAlign = b[63 + offset];
                CurAccept.FontAttributes.VertAlign = b[64 + offset];
            }

            //Print AD Message
            if (CurAccept.PreDispDef == 'Y')
                PrintMessageAcpt(canvas, paint, CurAccept.Default, CurAccept.Row, CurAccept.Col, CurAccept.Siz - CurAccept.SizOff, CurAccept.Color,
                CurAccept.FontAttributes, 0, CurAccept.ExpandField);

        //    InpBuff = CurAccept.Default;
            InpIdx = max(CurAccept.StrPos - 1, 0);

            CurAccept.CurPosition = ComputePosition();

            for (i = 0; i < 6; i++)
            {
                int idx = offset + 62 + (i * 40) + default_offset;
                DisplayHelp(canvas, paint, CurWindow, i, idx, txt);
            }

            //paint.Color = new SKColor(255, 0, 0);
            //paint.Typeface = SKTypeface.FromFamilyName("Courier");

            if (AcceptPending) ProcessKeyBuff();

            if (AcceptPending && (CurAccept.Timeout == 'Y') && (CurAccept.TimeoutSec == 0))
            {
                CurAccept.RtnCmd = "TO";
                CurAccept.RtnKey = "   ";
                FinishAccept();
            }

            if (AcceptPending && (CurAccept.Timeout == 'Y') && (CurAccept.TimeoutSec != 0))
                SetTimer(CurAccept.TimeoutSec * 1000);

            if (ButtonsEnabled && ButtonTable[0].Name.Length > 0) {

                int ClientWidth = WindowWidth * CellWidth;
                int ib=0;
                int w = 50;
                int h = CharHeight;
                int x = (CurAccept.Col + 3) * CharWidth;
                int y = 0;

                for (i = 0; i < NUM_BUTTONS; i++)
                {
                    SIZE s;
                    bool GetSize = true;
                    if ((ButtonTable[i].Name.Length) > 0 && (ButtonTable[i].AcceptSeq.Take(8)==CurAccept.Seq.Take(8) ))
                    {
                    //    ButtonTable[i].hWnd = CreateWindow("PCS_BUTTON", ButtonTable[i].Name,
                    //                WS_CHILD | BS_CENTER | BS_PUSHBUTTON | BS_NOTIFY,
                     //               x, y,
                      //              w, h,
                      //              PCSDialogWindow, NULL, PCSInstance, NULL);
                      //  SendMessage(ButtonTable[i].hWnd, WM_SETFONT, (WPARAM)hMFont, (LPARAM)NULL);
                        if (GetSize)
                        {
                //            HDC hdc = GetDC(ButtonTable[i].hWnd);
                //            DebugCreateGDI("AcceptData", "GetDC", hdc);
                //            //        Probably the biggest word we'll have
                //            GetTextExtentPoint32(hdc, "CANCEL", 6, &s);
                //            DebugReleaseDCGDI("AcceptData", "ReleaseDC", hdc, ButtonTable[i].hWnd);
                            GetSize = false;
                        }
                        //h = (int(s.cy) + 4); //  Couple of pixels for the borders
                        //y = CellHeight * CurAccept.Row;// + (s.cy-CharHeight)/2;
                        //w = s.cx + 4;
                        //MoveWindow(ButtonTable[i].hWnd, x, y, w, h, FALSE);
                        //ShowWindow(ButtonTable[i].hWnd, SW_SHOW);

                        bool ButtonFits = true;
                        if ((x + w) > (ClientWidth / 2)) ButtonFits = false;
                        if (ButtonFits)
                        {
                            int j = 0;
                            int help_left = -1;
                            int help_right = -1;
                            for (j = 0; j < 6; j++)
                            {
                                if (wd.Help[j].Use == 'Y' && (wd.Help[j].Lne == (CurAccept.Row + 1)))
                                {
                                    if (help_left == -1 || (wd.Help[j].Pos < help_left)) help_left = wd.Help[j].Pos;
                                    if (help_right == -1 || (wd.Help[j].Pos + wd.Help[j].Siz > help_right)) help_right = wd.Help[j].Pos + wd.Help[j].Siz;
                                }
                            }
                            if (help_left != -1 && ((help_left - 1) * CharWidth) < (x + w + 2)) ButtonFits = false;
                            //                        if (help_right~=-1&&(help_right*CharWidth)
                        }

                        if (!ButtonFits)
                        {
                            DestroyOneButton(i);
                            break;
                        }
                        else x += w + 5;
                    }
                }//end of for
                //SetFocus()?;
            }
            //    InvalidateRect(PCSDialogWindow, NULL, FALSE);

            if (AcceptPending)
            {
                while (CaretOn <= 0)
                {
                //    CreateCaret(PCSDialogWindow, (HBITMAP)NULL, (int)(CharWidth * .7), CARET_HEIGHT);
                //    ShowCaret(PCSDialogWindow);
                    CaretOn++;
                }
                CurAccept.CurPosition = ComputePosition();
                //        if (!CaretOn) ShowCaret(PCSDialogWindow);
                //        CaretOn=TRUE;
            }

            if (CalForNextAccept)
            {
                SIODisplayCalendar();
                CalForNextAccept = false;
            }
            
        }

        

        void SIODisplayCalendar()
        {
            throw new NotImplementedException();
        }

        void DestroyOneButton(int i)
        {
            throw new NotImplementedException();
        }

        void SetTimer(int v)
        {
            //throw new NotImplementedException();
        }

        string ConvertNumToAlph(int size, int value)
        {
            string Dest = "" + value;
            if (Dest.Length == 1) return "00" + Dest;
            if (Dest.Length == 2) return "0" + Dest;
            return Dest;
        }
        char SendBuf[158];
        char* FinishAccept(string vBtnTxt="")
        {

            short BufSize;

            _WindowData wd = FindWD(CurWindow);
            
            if (wd != null && (CurAccept.Type.Take(2)=="AE")) PrintMessage(canvas, paint," ", CurAccept.Row, CurAccept.Col, CurAccept.Siz, wd.ColorScreen,
                     CurAccept.FontAttributes, 0, CurAccept.ExpandField);

            //KillTimer(MainWindow, PCS_ACCEPT_TIMER);

            //    if (CaretOn)
            while (CaretOn > 0)
            {
              //  DestroyCaret();
              //  HideCaret(PCSDialogWindow);
                //        CaretOn=FALSE;
                CaretOn--;
            }

            //        Message header
            SendBuf[0] = 'S';
            SendBuf[1] = 'I';
            SendBuf[2] = 'O';
            SendBuf[3] = Convert.ToChar(158);
            SendBuf[4] = Convert.ToChar(0);
            SendBuf[5] = CurAccept.Type[0];
            SendBuf[6] = CurAccept.Type[1];

            //    Data copy 8 bytes w.e.f [7]

            for (int i = 7; i < 7 + 8; i++) {
                SendBuf[i] = CurAccept.Seq[i-7];
            }

            string mx = ConvertNumToAlph(3,CurAccept.MouseX);
            string my = ConvertNumToAlph(3, CurAccept.MouseX);
            SendBuf[15] = mx[0]; SendBuf[16] = mx[1]; SendBuf[17] = mx[2];
            SendBuf[18] = my[0]; SendBuf[19] = my[1]; SendBuf[20] = my[2];

            SendBuf[21] = CurAccept.RtnCmd[0];//H   .e.g
            SendBuf[22] = CurAccept.RtnCmd[1];//L
            SendBuf[23] = CurAccept.RtnKey[0];//F
            SendBuf[24] = CurAccept.RtnKey[1];//2
            SendBuf[25] = CurAccept.RtnKey[2];//' '

            int j = InpBuff.Length - 1;
            while (InpBuff[j] == ' ')
            {
                InpBuff[j] = Convert.ToChar(0);
                j--;
            }

            //    if (!(strncmp(CurAccept.RtnKey, "TB", 2))
            //        ||!(strncmp(CurAccept.RtnKey, "BT", 2))
            if ((CurAccept.RtnCmd.Take(2) == "QU")
                || (CurAccept.RtnKey.Take(2) == "? "))
                {
                CurAccept.Default.CopyTo(0, SendBuf, 26, 132);
                
            }
            else {
                InpBuff.CopyTo(SendBuf,26);
            }
            //        strncpy_s(&SendBuf[26],132,CurAccept.Default);
            //    else strncpy_s(&SendBuf[26],132,InpBuff);


            //Space-fill the buffer
            for (int i = 26; i < 26 + 132; i++) {
                if (SendBuf[i] == 0) SendBuf[i] = ' ';
            }

            //Note:    Consider, while testing, adding a timer somewhere around here, to determine
            //how long before we receive the next ACCEPT packet. That may be a good idea for our
            //speed issues.  It may also HELP - but not be a complete testing solution, to run
            //Ethereal and see the times between packets.  Both may be informative.  Any other
            //testing/debugging ideas?  Installing a profiler, for example?


            //    PrintMessage(SendBuf, 28, 1, 80, 711);
            byte[] SendBufEx = System.Text.Encoding.UTF8.GetBytes(SendBuf).Take(132).ToArray();
   //         if (s!=null)
   //            Spawn.Send(SendBufEx);

            // let AcceptPending=True if called with vBtn param
            if (vBtnTxt.Length==0) AcceptPending = false;

            if (CurAccept.SizOff > 0)
            {
                int i;
                for (i = 0; i < CurAccept.SizOff; i++)
                {
                    int r = CurAccept.Row;
                    int c = CurAccept.Col + CurAccept.Siz + i - CurAccept.SizOff;
                    //            int r = CurAccept.Row - 1;
                    //            int c = CurAccept.Col + CurAccept.Siz + i - 1 - CurAccept.SizOff;
                    //    Find a new way to do this.  Maybe SavedScreen needs to be the transaction that created
                    //    this bit of text, and then we reprint it?
                    //            if (wd!=NULL) PrintMessage(&CurAccept.SavedScreen[i],r+1,c+1,1,WindowData->ScreenColors[r][c]);
                }
               // InvalidateRect(MainWindow, NULL, FALSE);
               // InvalidateRect(PCSDialogWindow, NULL, FALSE);
            }

            DestroyButtons();

            //    We're done with this accept.  In case the next accept doesn't send the "AP" packet with these
            //    parms, reset them here.
            CurAccept.StrPos = 0;
            CurAccept.SizOff = 0;
            CurAccept.EraseBuffer = true;
            string utfString = Encoding.UTF8.GetString(SendBufEx, 5, 128);// bytes.Length);
            return SendBuf;
        }

        void ProcessKeyBuff()
        {

        }

        int CountLeadingSpaces(string t)
        {
            int i = 0;
            foreach (char a in t)
            {
                if (a == ' ') i++; else break;
            }
            return i;
        }


        int ComputePosition()
        {

            int i;
            _WindowData wd;

            // DebugStartProcess("ComputePosition");

            wd = FindWD(CurWindow);
            //    hDC = GetDC(PCSDialogWindow);
            //hDC = GetDC(MainWindow);
            //DebugCreateGDI("ComputePosition", "GetDC", hDC);

            //HFONT cf;
            //if (wd && wd.FixedPitch)
            //{
            //    cf = SelectPCSFont(hDC, CurAccept.FontAttributes, wd->FixedPitch);
            //}
            //else
            //{
            //    cf = FontInfo[CurAccept.FontAttributes.FontNumber].FontHandle;
            //}
            //if (cf) SelectObject(hDC, (HGDIOBJ)cf);
            //#ifdef PCSDEBUG
            //                char m[512];
            //                sprintf_s(m,sizeof(m),"Resetting font data: ComputePosition");
            //                DisplayMessage((short)strlen(m),m);
            //#endif
            SetFontData(ref CharWidth, ref CharHeight, ref NumberWidth);

            int TextLen = 0;
            int SpcLen = 0;
            int spc = 0;

            //    When we display the string, we're going to parse out the leading spaces and
            //    replace them with CellNumberWidth blank pixels.
      //      spc = min(CountLeadingSpaces(InpBuff), InpIdx);

            if (spc < InpIdx)
            {
                RECT r;
                r.right = 0;
                r.left = 0;
                //MDrawText(canvas,paint)
                //XDrawText(hDC, &InpBuff[spc], InpIdx - spc, &r, DT_CALCRECT | DT_NOPREFIX);
                TextLen = r.right - r.left;
            }

            SpcLen = spc * CellNumberWidth;

            SCROLLINFO si = new SCROLLINFO();
            int iVertPos = 0, iHorzPos = 0;
            //si.cbSize = sizeof(si);
            //si.fMask = SIF_POS;
            //if (GetScrollInfo(MainWindow, SB_HORZ, &si)) iHorzPos = si.nPos;
            //if (GetScrollInfo(MainWindow, SB_VERT, &si)) iVertPos = si.nPos;

            i = (CurAccept.Col) * CharWidth + TextLen + SpcLen - iHorzPos * CellWidth;

            //    -5, since that's where the bottom line of the edit box is drawn at.
            //SetCaretPos(i, ((CurAccept.Row + 1) * CharHeight) - CARET_HEIGHT - 2 - FONT_OFFSET - (iVertPos * CellHeight));

            //DebugReleaseDCGDI("ComputePosition", "ReleaseDC", hDC, PCSDialogWindow);
            //if (wd && wd.FixedPitch)
            //{
            //    DebugDeleteGDI("ComputePosition", "DeleteObject - Font", cf);
            //}

            //DebugEndProcess("ComputePosition");

            return i;
        }

        int batchno = 0;
        void SIOOpenWindow(string b)
        {
            int j;
            int i;

            CurWindow++;
            _WindowData wd = FindWD(CurWindow);
            if (wd == null)

            {
                wd = FindPoolEnd();
                if (wd == null) return;
                wd.WindowNumber = CurWindow + 1;
            }

            int MSG_HDR = 0;
            wd.StartRow = ConvertBufNum(b, MSG_HDR, 3);
            wd.StartCol = ConvertBufNum(b, MSG_HDR + 3, 3);
            wd.EndRow = ConvertBufNum(b, MSG_HDR + 6, 3);
            wd.EndCol = ConvertBufNum(b, MSG_HDR + 9, 3);
            wd.Outline = b[MSG_HDR + 12];
            wd.ActiveColorDisplay = b[MSG_HDR + 13];
            wd.ActiveColorAccept = b[MSG_HDR + 14];
            wd.ColorScreen = ConvertBufNum(b, MSG_HDR + 15, 3);
            wd.ColorDisplay = ConvertBufNum(b, MSG_HDR + 18, 3);
            wd.ColorField = ConvertBufNum(b, MSG_HDR + 21, 3);
            wd.ColorAccept = ConvertBufNum(b, MSG_HDR + 24, 3);
            wd.ColorFChg = ConvertBufNum(b, MSG_HDR + 27, 3);
            wd.ColorError = ConvertBufNum(b, MSG_HDR + 30, 3);
            wd.ColorHelp1 = ConvertBufNum(b, MSG_HDR + 33, 3);
            wd.ColorHelp4 = ConvertBufNum(b, MSG_HDR + 36, 3);
            wd.Line = ConvertBufNum(b, MSG_HDR + 39, 3);
            wd.Position = ConvertBufNum(b, MSG_HDR + 42, 3);
            wd.Size = ConvertBufNum(b, MSG_HDR + 45, 3);
            wd.Highlight = ConvertBufNum(b, MSG_HDR + 48, 3);
            wd.DisplayNow = b[MSG_HDR + 51];
            wd.AcceptNow = b[MSG_HDR + 52];
            wd.ConcealPassword = b[MSG_HDR + 53];
            wd.ConvertCase = b.Substring(MSG_HDR + 54, 3 - 1);// 1 byte diff
            wd.Echo = b[MSG_HDR + 56];
            wd.ReturnSpecialKey = b[MSG_HDR + 57];
            wd.CommandSet = b.Substring(MSG_HDR + 58, 3 - 1);// 1 byte diff
            wd.MemoSet = b[MSG_HDR + 60];
            wd.DisplayError = b[MSG_HDR + 61];
            wd.DisplayWarn = b[MSG_HDR + 62];
            wd.Warn = b.Substring(MSG_HDR + 63, 3 - 1);// 1 byte diff
            wd.ErrorClear = b[MSG_HDR + 65];
            wd.ErrorWait = b[MSG_HDR + 66];
            wd.ErrorLne = ConvertBufNum(b, MSG_HDR + 67, 3);
            wd.ErrorPos = ConvertBufNum(b, MSG_HDR + 70, 3);
            wd.ErrorSiz = ConvertBufNum(b, MSG_HDR + 73, 3);
            wd.ScnNo = b.Substring(MSG_HDR + 76, 4 - 1);// 1 byte diff
            wd.FixedPitch = (b[MSG_HDR + 79] == 'Y');
            j = 80;

            for (i = 0; i < 6; i++)
            {
                wd.Help[i].Use = b[j + MSG_HDR];
                j++;
                wd.Help[i].Splf = b[j + MSG_HDR];
                j++;
                wd.Help[i].Lne = ConvertBufNum(b, MSG_HDR + j, 3);
                j += 3;
                wd.Help[i].Pos = ConvertBufNum(b, MSG_HDR + j, 3);
                j += 3;
                wd.Help[i].Siz = min(ConvertBufNum(b, MSG_HDR + j, 3), 40);
                j += 3;
            }

            wd.MaxRow = max(WindowHeight, wd.EndRow);
            wd.MaxCol = max(WindowWidth, wd.EndCol);
            wd.Ins_row = wd.MaxRow;
            wd.Ins_col = wd.MaxCol;
            wd.Ins_color = wd.ColorScreen;
            wd.TO_row = wd.MaxRow;
            wd.TO_col = 1;

            if (wd.FontNum == 0)
            {
                wd.FontNum = -1;
                //                char m[256];
                //                sprintf_s(m,sizeof(m),"Reset font for window %d to -1", CurWindow);
                //                DisplayMessage(strlen(m),m);

                //    Look for a full-screen window to load the font number from.
                if (CurWindow > 0)
                {
                    int win = CurWindow - 1;
                    _WindowData lw;
                    while (true)
                    {
                        lw = FindWD(win);
                        if (lw == null) break;
                        if ((lw.EndCol - lw.StartCol + 1 == WindowWidth) && (lw.EndRow - lw.StartRow + 1 == WindowHeight) && lw.FontNum != -1)
                        {
                            wd.FontNum = lw.FontNum;
                            //                        char m[256];
                            //                        sprintf_s(m,sizeof(m),"Set font for window %d to %d", CurWindow, wd->FontNum);
                            //                        DisplayMessage(strlen(m),m);
                            break;
                        }
                        if (win < 1) break;
                        win--;
                    }
                }
                //                        sprintf_s(m,sizeof(m),"After reset, font for window %d is %d", CurWindow, wd->FontNum);
                //                        DisplayMessage(strlen(m),m);
            }

            _PCSFontAttributes fa = new _PCSFontAttributes();
            if (wd.FontNum != -1) fa.FontNumber = wd.FontNum;
            else fa.FontNumber = MainFont;
            fa.FontSize = 100;
            fa.FontWeight = 400;
            //SelectPCSFont(..)
            if ((wd.EndRow - wd.StartRow + 1 == WindowHeight) && (wd.EndCol - wd.StartCol + 1 == WindowWidth))
            {
                ResizePCS(false, 0, 0);
            }

        }

        void ResizePCS(bool move, int def_x, int def_y)
        {
            //DisplayTime(null, 0, 1, 0);



        }

        string getTextParamBinMode(string txt)
        {
            string ret = "";
            int countSpc = 0;
            foreach (char b in txt) {
                if (b == ' ') countSpc++;
                if (countSpc > 2) {
                    ret = ret + b;
                }
            }
            return ret.TrimStart(); //ignore leading spac
        }

        //Deprecated
        string getTextParam(string txt)
        {
            string[] t = txt.Split(',');
            string ret = t[3];
            for (int i = 4; i < t.Length; i++)
            {
                ret += "," + t[i];
            }
            return ret;
        }

        SKSurface surface;
        SKCanvas canvas;// = null;
        SKPaint paint;// = null;

        bool canvasPaintRefSet = false;

        void SetCanvasPaintRef(SKSurface s, SKPaint p)
        {
            surface = s;
            canvas = surface.Canvas;
            paint = p;
            canvasPaintRefSet = true;
        }

        struct RECT
        {
            int top;
            int bottom;
            int left;
            int right;
        };

        struct _FIELDENH
        {
            int StartCol;
            int EndCol;
            int Size;
            int Row;
            int Window;

            void ZeroMemory()
            {
                StartCol = 0; EndCol = 0; Size = 0; Row = 0; Window = 0;
            }

        };

        const int NUM_BUTTONS = 93;
        struct _ButtonTable
        {
            string Name;
            string Code;
            string AcceptSeq;
            void ZeroMemory()
            {
                Name = ""; Code = ""; AcceptSeq = "";
            }
        };
        _ButtonTable ButtonTable[93];


        const int NUM_FH = 500;
        _FIELDENH FieldEnh[500];
        int FieldEnh_Ptr = 0;

        int CharWidth = 0, CharHeight = 0, NumberWidth = 0;
        int CellNumberWidth = 0;

        RECT SetRect(int Left, int Top, int Right, int Bottom)
        {
            RECT r;
            r.bottom = Bottom;
            r.left = Left;
            r.top = Top;
            r.right = Right;
            return r;
        }

        void SetupButtons(string c)
        {
            int num;
            num = ConvertBufNum(c, 0, 3) - 1;

            if (num < 0 || num > 92) return;
            ButtonTable[num].AcceptSeq = c.Substring(3, 8);// CopyString(ButtonTable[num].AcceptSeq, &c[3], 8);
            ButtonTable[num].Code = c.Substring(11, 3);
            ButtonTable[num].Name = c.Substring(14, 6);
        }

        void DestroyButtons()
        {
            //EnumChildWindows(PCSDialogWindow, DestroyButtonWindows, 0);
            for (int i = 0; i < NUM_BUTTONS; i++) ButtonTable[i].ZeroMemory();
            return;
        }


        void EraseFill(SKColor c, int sc, int sr, int ec, int er)
        {
            SKRect rec = new SKRect();
            SKPoint ptx = pt(new SKPoint(0, 0));//pt gises the shifted point so we apply here to be reflected in rect
            rec.Left = (sc - 1) * CellWidth + ptx.X;
            rec.Top = (sr - 1) * CellHeight + ptx.Y;
            rec.Right = (ec) * CellWidth + ptx.X;
            rec.Bottom = (er) * CellHeight + ptx.Y;
            if (paint != null)
            {
                paint.Style = SKPaintStyle.Fill;
                paint.Color = c;
                canvas.DrawRect(rec, paint);
            }
        }

        //    meant redoing the bitmap in the background color.
        void SIOEraseWindow(int cw = 0)
        {

            if (cw >= 0)
            {
                _WindowData wd = FindWD(cw);
                if (wd != null)
                {

                    EraseFill(ResolveSIOColor(wd.ColorScreen), wd.StartCol, wd.StartRow, wd.EndCol, wd.EndRow);

                    if (wd.Outline == 'Y')
                    {
                        MDisplayBox(wd.StartRow - 1, wd.StartCol,
                                    wd.EndRow - 1, wd.EndCol - 1,
                                    wd.ColorScreen, 1, 1,
                                    true, true, 0);
                    }

                    RECT r;
                    r = SetRect(wd.StartCol * CharWidth, wd.StartRow * CharHeight, wd.EndCol * CharWidth, wd.EndRow * CharHeight);
                    //InvalidateRect(PCSDialogWindow, &r, FALSE);
                    //UpdateWindow(PCSDialogWindow);

                    int f;
                    for (f = NUM_FH - 1; f >= 0; f--)
                    {
                        if (FieldEnh[f].Size != 0 && FieldEnh[f].Window == cw)
                        {
                            FieldEnh[f].ZeroMemory();
                            FieldEnh_Ptr--;
                        }
                    }

                    //    And, although I don't like it here, cleaning out any leftover buttons.
                    DestroyButtons();
                }
            }
        }

        void MDisplayBox(int strrow, int strcol, int endrow, int endcol, int color, int type, int thick, bool outL, bool f, int tag)
        {
            _WindowData wd = FindWD(CurWindow);
            if (wd != null)
            {
                RenderBoxTran(strrow, strcol, endrow, endcol, color, thick, outL, f, 0, 0);
            }
        }


        void DisplayError(string b)
        {
            string Data = b + "";
            _WindowData wd = FindWD(CurWindow);
            if (wd != null)
            {
                _PCSFontAttributes fa = new _PCSFontAttributes();
                if (wd.FontNum != -1) fa.FontNumber = wd.FontNum;
                else fa.FontNumber = MainFont;
                fa.FontSize = 100;
                fa.FontWeight = 400;
                if (wd != null) PrintMessage(canvas, paint, Data, wd.ErrorLne - 1, wd.ErrorPos - 1,
                                          wd.ErrorSiz, wd.ColorError, fa, 999, false);
            }
        }


        SKImage savedN;
        int NextDisplay_FG = 0;
        int NextDisplay_BG = 0;

        struct TEXTMETRIC
        {
            long tmHeight;
            long tmAscent;
            long tmDescent;
            long tmInternalLeading;
            long tmExternalLeading;
            long tmAveCharWidth;
            long tmMaxCharWidth;
            long tmWeight;
            long tmOverhang;
            long tmDigitizedAspectX;
            long tmDigitizedAspectY;
            byte tmFirstChar;
            byte tmLastChar;
            byte tmDefaultChar;
            byte tmBreakChar;
            byte tmItalic;
            byte tmUnderlined;
            byte tmStruckOut;
            byte tmPitchAndFamily;
            byte tmCharSet;
        };

        TEXTMETRIC TextMetrics;
        byte TMPF_FIXED_PITCH = 0x01;


        void GetTextMetrics() { }


        struct SIZE
        {
            long cx;
            long cy;
        };

        void SetFontData(int& cw, int& ch, int& nw)
        {

            int width, height, numwidth;
            //GetTextMetrics(hdc, &TextMetrics);
            height = Convert.ToInt32(TextMetrics.tmHeight) + FONT_OFFSET;

            // For a fixed pitch font, seems like Max != Average, and causes my calcs to be off elsewhere.
            int l = TextMetrics.tmPitchAndFamily & TMPF_FIXED_PITCH;
            if (l > 0)
            {
                width = Convert.ToInt32(TextMetrics.tmAveCharWidth);
                numwidth = width;
            }
            else
            {
                width = (int)TextMetrics.tmAveCharWidth * 2;
                if (width > TextMetrics.tmMaxCharWidth) width = Convert.ToInt32(TextMetrics.tmAveCharWidth + TextMetrics.tmMaxCharWidth) / 2;
                //    Fixed pitch, chardwidth is correct.  Proportional font, adjust the width.
                //    Which method do we like better, average character size in a "normal" PCS string,
                //    Or a hardcoded 70%?
                SIZE s;

                //    We were passed a DC;  Use it.
                //        HDC hdcDialog;
                //.75 too narrow
                //    Width of an 'N' might be reasonable. - too narrow.
                width = (int)(((double)width) * FONT_PERCENT);
                //    Close to reasonable? '1' is narrow, 0's are common, '9' is probably wide.
                //        hdcDialog = GetDC(PCSDialogWindow);
                //        DebugCreateGDI("SetFontData", "GetDC", hdcDialog);
                s.cx = 0; s.cy = 0;
                GetTextExtentPoint32("1009", 4, ref s);
                //        DebugReleaseDCGDI("SetFontData", "ReleaseDC", hdcDialog, PCSDialogWindow);
                numwidth = Convert.ToInt32(s.cx) / 4;
            }

            //    0 is never valid
            if (width < 1) width = 1;
            if (height < 1) height = 1;
            if (numwidth < 1) numwidth = 1;

            //#ifdef PCSDEBUG
            //    if (width==8) width = 9;
            //#endif

            if (cw != null) cw = width;
            if (ch != null) ch = height;
            if (nw != null) nw = numwidth;

            cw = 22;//Override Defaults
            ch = 42;

            //# ifdef PCSDEBUG
            //            static int old_cw = 0;
            //            if (old_cw != width)
            //            {
            //                DWORD dummy;
            //                DMFormatBuffer();
            //                sprintf_s(DbgText, sizeof(DbgText), "Old CharWidth: %d, New: %d\n", old_cw, width);
            //                WriteFile(XmitLog, DbgText, (DWORD)strlen(DbgText), &dummy, NULL);
            //                //        DisplayMessage((short) strlen(DbgText), DbgText);
            //                old_cw = width;
            //            }
            //#endif

        }

        //void ProcessResize(string b, short size)
        //{
        //    //PCSPGMLOC(" - Function Start")

        //    int i = 0;
        //    int w = 0, h = 0;
        //    do
        //    {
        //        switch (b[i])
        //        {
        //            case 'H':
        //                {
        //                    h = atoi(&b[i + 1]);
        //                    i += (int)strlen(&b[i + 1]) + 2;
        //                    break;
        //                }
        //            case 'W':
        //                {
        //                    w = atoi(&b[i + 1]);
        //                    i += (int)strlen(&b[i + 1]) + 2;
        //                    break;
        //                }
        //            case 'F':
        //                {
        //                    MainFont = atoi(&b[i + 1]) - 1;
        //                    i += (int)strlen(&b[i + 1]) + 2;
        //                    break;
        //                }
        //            //        Not doing anything with these yet, but they're sent.
        //            case 'Y':
        //                {
        //                    int DefSize = atoi(&b[i + 1]);
        //                    i += (int)strlen(&b[i + 1]) + 2;
        //                    break;
        //                }
        //            case 'Z':
        //                {
        //                    int DefWeight = atoi(&b[i + 1]);
        //                    i += (int)strlen(&b[i + 1]) + 2;
        //                    break;
        //                }
        //            case 'I':
        //                {
        //                    BOOL DefItalics = (b[i + 1] == 'Y');
        //                    i += 2;
        //                    break;
        //                }
        //            case 'U':
        //                {
        //                    BOOL DefUnderline = (b[i + 1] == 'Y');
        //                    i += 2;
        //                    break;
        //                }
        //            case 'S':
        //                {
        //                    BOOL DefStrikeout = (b[i + 1] == 'Y');
        //                    i += 2;
        //                    break;
        //                }
        //            default:
        //                {
        //                    i = size;
        //                    break;
        //                }
        //        }
        //    } while (i < size);

        //    WINDOWDATA* wd = FindWD(CurWindow);
        //    if (wd) wd->FontNum = MainFont;
        //    if (WindowWidth != w || WindowHeight != h)
        //    {
        //        HDC hdc = GetDC(MainWindow);
        //        DebugCreateGDI("ProcessResize", "GetDC", hdc);
        //        SelectObject(hdc, (HGDIOBJ)FontInfo[MainFont].FontHandle);
        //        //#ifdef PCSDEBUG
        //        //                char m[512];
        //        //                sprintf_s(m,sizeof(m),"Resetting font data: ProcessResize");
        //        //                DisplayMessage((short)strlen(m),m);
        //        //#endif
        //        SetFontData(hdc, &CellWidth, &CellHeight, &CellNumberWidth);
        //        SetFontData(hdc, &CharWidth, &CharHeight, &NumberWidth);
        //        DebugReleaseDCGDI("ProcessResize", "ReleaseDC", hdc, PCSDialogWindow);

        //        //#ifdef PCSDEBUG
        //        //        sprintf_s(m,sizeof(m),"ProcessResize: CharWidth = %d, MainFont = %d", CharWidth, MainFont);
        //        //        DisplayMessage((short) strlen(m), m);
        //        //#endif

        //        ResizeWindow(w, h);
        //        if (wd)
        //        {
        //            DebugCopyBitmap(wd->hDC, "After Resize");
        //            //    Q: 8/20, KB removed the condition & made this an 'always do' the makebitmap.
        //            //    Why the condition?  Check Widescreen in browses, widescreen reports,
        //            //  and time tracker (help, set status, drill downs).  All seemed fine without
        //            //    it, and the widescreen browses didnt resize right with it.
        //            //    12/23/09, KB Says: This doesn't work in the time tracker.  It totally breaks TBSTC's
        //            //    resize - but only the second and subsequent times.  WHY?
        //            //            if (CurWindow==0) MakeBitmap(wd);
        //            MakeBitmap(wd);
        //            //            DebugCopyBitmap(wd->hDC, "After MakeBitmap");
        //        }
        //    }
        //    //    RECT    rcDlg;
        //    //    HDC hdc = GetDC(MainWindow);
        //    //    DebugCreateGDI("ParsePCSMessage", "GetDC", hdc);
        //    //    GetWindowRect(MainWindow, &rcDlg);
        //    //    HBITMAP hbmWin = CreateCompatibleBitmap(hdc,
        //    //        rcDlg.right-rcDlg.left, rcDlg.bottom-rcDlg.top);
        //    //    DebugCreateGDI("ParsePCSMessage", "CreateCompatibleBitmap" hbmWin);
        //    //    BITMAP b;
        //    //    if (GetObject(hbmWin, sizeof(b), &b))
        //    //    {
        //    //        char m[256];
        //    //        sprintf_s(m, sizeof(m), "Width: %d, Height: %d\n", b.bmWidth, b.bmHeight);
        //    //        MessageBox(NULL, m, m, MB_OK);
        //    //    }
        //}


        void test_PSplit()
        {
            return;
            /*
            string[] t1 = PSplit("SIO,DD,115,V2 024001080D731001075400NNN000Y            (C) Copyrights,  Perfect Circle Solutions, Inc.  1979 thru 2014 ");
            string[] t2 = PSplit("SIO,DD,52,V2 001070010D731001075400NNN000Y  MNSL6354 H ");
            string[] t3 = PSplit("SIO,DD,40,V2 025001080D731001100400NNN000Y ");
            string[] t4 = PSplit("SIO,DD,52,V2 001030030D731001100400NNN000YC PCS Log On");

            bool pass1 = t1[4].Contains("(C) Copyrights,  Perfect Circle Solutions, Inc.  1979 thru 2014");
            bool pass2 = t2[4].Contains("MNSL6354 H");
            bool pass3 = t3[4].Contains("        ");
            bool pass4 = t4[4].Contains("PCS Log On");
            */

            byte[][] t1 = PSplit(Encoding.ASCII.GetBytes("SIO,DD,115,V2 024001080D731001075400NNN000Y            (C) Copyrights,  Perfect Circle Solutions, Inc.  1979 thru 2014 "));
            byte[][] t2 = PSplit(Encoding.ASCII.GetBytes("SIO,DD,52,V2 001070010D731001075400NNN000Y  MNSL6354 H "));
            byte[][] t3 = PSplit(Encoding.ASCII.GetBytes("SIO,DD,40,V2 025001080D731001100400NNN000Y "));
            byte[][] t4 = PSplit(Encoding.ASCII.GetBytes("SIO,DD,52,V2 001030030D731001100400NNN000YC PCS Log On"));

        }

        byte&& PSplit(byte t[], char separator=',')
        {
            int commas = 0;
            int idx = 0 ;
            byte[][] ret = new byte[3][];
            int first =-1, second=-1;
            bool discont = false;
            foreach (char a in t)
            {
                if (commas == 1) first = idx;
                if (commas == 2) { second = idx; discont = true; }
                if (a == separator) { commas++; }
                idx++;
                if (discont) break;
            }

           ret[0] = Take(t, 0, first);
           ret[1] = Take(t, first, second);
           ret[2] = Take(t, second, t.Length);
           return ret;
        }

    std::list<string> PSplit(string t)
        {
            int commas = 0;
            string msgtag = "";
            string msgcmd = "";
            string msglen = "";
            string cmdx = "";
            foreach (char a in t)
            {
                if (a == ',') { commas++; if (commas <= 3) continue; }
                if (commas == 0) { msgtag = msgtag + a; }
                if (commas == 1) { msgcmd = msgcmd + a; }
              //  if (commas == 2) { msglen = msglen + a; }
                if (commas >= 2) { cmdx = cmdx + a; }
            }
            int spaces = 0;
            string spec = "";
            string val = "";
            foreach (char a in cmdx)
            {
                if (a == ' ') { spaces++; }
                if (spaces <= 1) { spec = spec + a; }
                if (spaces > 1) { val = val + a; }
            }


            if (msglen.Length > 1)
            {

                int l = Convert.ToInt32(msglen) - spec.Length;

                while (l > 0)
                {
                    val = val + ' ';
                    l--;
                }
            }


            string[] rets = (msgtag + "|" + msgcmd + "|" + msglen + "|" + spec + "|" + val).Split('|');
            return rets;

            string full = "";
            string tag = "";
            string cmd = "";
            string llen = "";

            int i = 0;
            commas = 0;
            spaces = 0;
            foreach (char a in t)
            {
                char ch = a;
                if (commas < 3 && ch == ',') { ch = '|'; commas++; }
                else
                {
                    if (ch == ' ') spaces++;
                    if (spaces == 2 && ch != ' ') ch = '|';
                }
                full = full + ch;
                i++;
            }
            string[] ret = full.Split('|');

            if (ret.Length > 2)
            {

                int l = Convert.ToInt32(ret[2]) - ret[3].Length;

                if (ret.Length > 4)
                    while (l > 0)
                    {
                        ret[4] = ret[4] + ' ';
                        l--;
                    }
            }

            return ret;
        }

        char spaces[256];
        int t1 = 0;

        void MDrawBatch()
        {

            batchno++;
            //lock (test_data)

            {
                DrawKbdGrid();
                // while (fetching) { };
                if (test_data == null) return;
                if (test_data.Count < 1) return;

                List<PCSMessage> test_dataX = test_data.GetRange(0, test_data.Count);//Clone list to avoid Object was Modified during Operation Errors

                int Bytes=0;
                foreach (PCSMessage txtb in test_dataX)
                {
                    Bytes+=txtb.iMsgSize;
                }
                

                foreach (PCSMessage msg in test_dataX)
                {
                    bool processed = false;
                    if (msg.iMsgSize == 0) continue;
                    var txt = System.Text.Encoding.Default.GetString(msg.Content);
                    string b = System.Text.Encoding.UTF8.GetString(msg.Content);

                    if (msg.Type[0] == 'S' && msg.Type[1] == 'R' && msg.Type[2] == 'V')
                    {
                        if (MobileHasControl) {
                         //   if (msg.SubType[0] == 'R' && msg.SubType[1] == 'K') SendReconnectKey();

                            if (msg.SubType[0] == 'P' && msg.SubType[1] == 'N')
                            {
                               // int spawn_port = msg.Content[3] * 256 ^3 + msg.Content[2] * 256^2+ msg.Content[1] * 256 + msg.Content[0];
                                int spawn_port = msg.Content[0] + msg.Content[1] * 256;
                                Alert("Reconnecting to port " + spawn_port);
                                sock.Close();
                                try
                                {
                                    Thread.Sleep(3000);
                                    sock = SocketConnect(ip_server, spawn_port);
                                }
                                catch (System.Net.Sockets.SocketException sx) {
                                    Alert(sx.Message+"..");
                                }
                                if (sock.Connected)
                                {
                                    onSpawnConnected();
                                    //Alert("Just a Moment..");
                                }
                            }


                            processed = true;
                        }

                    }
                    if (msg.Type[0] == 'C' && msg.Type[1] == 'T' && msg.Type[2] == 'L')
                    {
                        {
                            if (msg.SubType[0] == 'E' && msg.SubType[1] == 'X')
                                 {OnExpiryÏnfo((char)msg.Content[0]);  }
                            if (msg.SubType[0] == 'W' && msg.SubType[1] == 'T') LoadWindowTrans(b);
                            if (msg.SubType[0] == 'W' && msg.SubType[1] == 'L') LoadWindowLines(b);
                            //   if (msg.SubType[0] == 'C' && msg.SubType[1] == 'Q' && MobileHasControl) {SendLogin();SendVersionInfo() ; }
                            if (msg.SubType[0] == 'A' && msg.SubType[1] == 'U')
                                 { OnClientAuth((char)msg.Content[0]);  }
                            if (msg.SubType[0] == 'V' && msg.SubType[1] == 'I') SendVersionInfo();
                            processed = true;
                        }
                        
                    }

                    if (msg.Type[0] == 'C' && msg.Type[1] == 'T' && msg.Type[2] == 'L')
                    {
                        if (msg.SubType.Count() > 0 && msg.SubType[0] == 'S' && msg.SubType[0] == 'Z')
                        {
                            string sizespec = b;
                            int w = 0, h = 0;
                            if (sizespec[0] == 'W')
                            {
                                w = Convert.ToInt32(sizespec.Substring(1));
                            }
                            else
                            {
                                h = h;//?
                            }
                            processed = true;
                        }
                    }

                    if (msg.Type[0] == 'S' && msg.Type[1] == 'I' && msg.Type[2] == 'O')
                    {
                        t1++;
                        if (t1 > 20)//vib on every 20th message
                        {
                            mVib.Vibrate(10);
                            t1 = 0;
                        }
                        if (msg.SubType.Count() < 2) return;
                        if (msg.SubType[0] == 'D' && msg.SubType[1] == 'E')
                        {
                            DisplayError(b);
                            processed = true;
                        }

                        if (msg.SubType[0] == 'A' && msg.SubType[1] == 'B')
                        {
                            SetupButtons(b);
                            processed = true;
                        }


                        if (msg.SubType[0] == 'E' && msg.SubType[1] == 'W')
                        {
                            SIOEraseWindow(CurWindow);
                            processed = true;
                        }
                        if (msg.SubType[0] == 'A' && (msg.SubType[1] == 'D' || msg.SubType[1] == 'E'))
                        {
                            MAcceptData(canvas, paint, txt, txt, (char)msg.SubType[1]);// getTextParamBinMode(txt), 'D');
                            processed = true;
                        }


                        if (msg.SubType[0] == 'D' && msg.SubType[1] == 'H')
                        {
                            int row;
                            int col;
                            int siz;
                            char ActColrDisp;
                            int DispColr;
                            int type;
                            int thick;
                            int tag;
                            int MSG_HDR = 0;
                            //    COBOL/SIO starts numbering row/column at 1, C starts at 0.
                            row = ConvertBufNum(b, MSG_HDR, 3) - 1;
                            col = ConvertBufNum(b, MSG_HDR + 3, 3) - 1;
                            siz = ConvertBufNum(b, MSG_HDR + 6, 3);
                            ActColrDisp = b[MSG_HDR + 9];
                            DispColr = ConvertBufNum(b, MSG_HDR + 10, 3);
                            type = ConvertBufNum(b, MSG_HDR + 13, 3);
                            thick = ConvertBufNum(b, MSG_HDR + 16, 3);
                            tag = ConvertBufNum(b, MSG_HDR + 19, 3);
                            DisplayHorizSep(row, col, siz, ActColrDisp, DispColr, type, thick, tag);
                        }

                        if (msg.SubType[0] == 'D' && msg.SubType[1] == 'D')
                        {

                            int row;
                            int col;
                            int siz;
                            char ActColrDisp;
                            int DispColr;
                            string DisplayText;
                            //    int rbs = stxt.Length;
                            string CopyBuf;
                            int tag;
                            // short MsgSize;
                            bool FieldExpansion = true;

                            int offset = 0;
                            int DDVersion = 1;
                            string DDV = b.Substring(0, 3);
                            if (DDV[0] == 'V' && DDV[1] == '2')
                            {
                                offset = 3;
                                DDVersion = 2;
                            }

                            CopyBuf = b.Substring(3);// + t[4];

                            row = ConvertBufNum(CopyBuf, 0, 3) - 1;
                            col = ConvertBufNum(CopyBuf, 3, 3) - 1;
                            siz = ConvertBufNum(CopyBuf, 6, 3);
                            
                            int len = CopyBuf.Length;


                            ActColrDisp = CopyBuf[9];
                            DispColr = ConvertBufNum(CopyBuf, 10, 3);
                            _PCSFontAttributes fa = new _PCSFontAttributes();

                            fa.FontNumber = ConvertBufNum(CopyBuf, 13, 3) - 1;
                            fa.FontSize = ConvertBufNum(CopyBuf, 16, 3);
                            fa.FontWeight = ConvertBufNum(CopyBuf, 19, 3);
                            fa.FontItalics = (CopyBuf[22] == 'Y');
                            fa.FontUnderline = (CopyBuf[23] == 'Y');
                            fa.FontStrikeout = (CopyBuf[24] == 'Y');
                            fa.BackgroundColor = 0;
                            fa.ForegroundColor = 0;
                            fa.HorizAlign = 0;
                            fa.VertAlign = 0;
                            fa.Outline = false;
                            tag = ConvertBufNum(CopyBuf, 25, 3);
                            int j = 0;

                            if (DDVersion >= 2) j = 3;
                            try
                            {
                                DisplayText = CopyBuf.Substring(28 + j);
                                if (DisplayText.Contains("[") && DisplayText.Contains("]")) DisplayText = DisplayText.Replace('[',' ').Replace(']',' ');
                            }
                            catch (System.ArgumentOutOfRangeException ex)
                            {
                                DisplayText = spaces.Substring(0, siz);
                            }
                            if (DDVersion >= 2)
                            {
                                FieldExpansion = (CopyBuf[28] != 'N');
                                fa.HorizAlign = CopyBuf[29];
                                if (CopyBuf.Length>30) fa.VertAlign = CopyBuf[30];
                            }
                            fa.ForegroundColor = NextDisplay_FG;
                            fa.BackgroundColor = NextDisplay_BG;

                            NextDisplay_FG = 0;
                            NextDisplay_BG = 0;

                            DisplayData(row, col, siz, ActColrDisp, DispColr, DisplayText.Substring(0,siz>=DisplayText.Length?DisplayText.Length:siz), fa, tag, FieldExpansion);

                            //int bgColor = ConvertBufNum(spec, 10 + 3, 3);
                            //int fgColor = -2/*Blk*/;

                            //MDrawText(canvas, paint, spec, stxt, bgColor, fgColor);
                            processed = true;
                        }


                        if (msg.SubType[0] == 'D' && msg.SubType[1] == 'L')
                        {
                            MDrawLine(b, canvas, paint, msg.iMsgSize); //size needed by DarwLine,DisplayHLine(..,high,..)
                            processed = true;
                        }

                        if (msg.SubType[0] == 'D' && msg.SubType[1] == 'B')
                        {

                            MDrawBox(b, canvas, paint, msg.iMsgSize); //size needed by DarwLine,DisplayHLine(..,high,..)
                            processed = true;
                        }

                        if (msg.SubType[0] == 'S' && msg.SubType[1] == 'C')
                        {
                            int MSG_HDR = 0;
                            NextDisplay_FG = ConvertBufNum(b, MSG_HDR + 0, 3);//ConvertBufNum(b, MSG_HDR + j, 3);
                            NextDisplay_BG = ConvertBufNum(b, MSG_HDR + 3, 3);
                            processed = true;
                        }
                    
                        if (msg.SubType[0] == 'W' && msg.SubType[1] == 'P')
                        {
                            LoadWindowParms(b);
                        }

                        if (msg.SubType[0] == 'C' && msg.SubType[1] == 'W')
                        {
                            CurWindow--;
                            SIOOpenWindow(b);
                            processed = true;
                        }

                        if (msg.SubType[0] == 'W' && msg.SubType[1] == 'E')
                        {
                            SIOClearError(LastWinLoaded);
                            int CopyCurWindow = CurWindow;
                            CurWindow = LastWinLoaded + 1;
                            //InvalidateRect(PCSDialogWindow, NULL, FALSE);
                            //UpdateWindow(PCSDialogWindow);
                            CurWindow = CopyCurWindow;
                        }

                        if (msg.SubType[0] == 'C' && msg.SubType[1] == 'L')
                        {
                            _WindowData wd = FindWD(CurWindow);

                            if (wd != null)
                            {

                                Window[CurWindow].ZeroMemory();

                                int f;
                                for (f = NUM_FH - 1; f >= 0; f--)
                                {
                                    if (FieldEnh[f].Size != 0 && FieldEnh[f].Window == CurWindow)
                                    {
                                        FieldEnh[f].ZeroMemory();
                                        FieldEnh_Ptr--;
                                    }
                                }
                                CurWindow--;
                                
                            }

                            _WindowData NewWD = FindWD(CurWindow);
                            //C++ Lines 4843-4873//////////////////////////////////////TODO CL

                            _PCSFontAttributes fa;
                            if (NewWD != null && NewWD.FontNum != -1) fa.FontNumber = NewWD.FontNum;
                            else fa.FontNumber = MainFont;
                            fa.FontSize = 100;
                            fa.FontWeight = 400;

                            bool fp = false;
                            if (NewWD != null && NewWD.FixedPitch) fp = true;

                            SetFontData(ref CellWidth, ref CellHeight, ref CellNumberWidth);

                            

                            SKPoint ptx = new SKPoint(0, 0);
                            if (SavedBM[0].hbitmap != null)
                                canvas.DrawImage(SavedBM[0].hbitmap, ptx.X, ptx.Y, paint);
                            //Discard TopMost SavedBM//Pop
                            //    for (int i = 0; i < (NUM_BM-1); i++) {
                            //         SavedBM[i] = SavedBM[i + 1];
                            //     }

                            if (CurWindow <= 0)
                            {
                                EraseFill(ResolveSIOColor(711),1,1,MaxCol,MaxRow);
                            }
                            canvas.Flush();

                            processed = true;


                        }

                        

                        if (msg.SubType[0] == 'O' && msg.SubType[1] == 'P')
                        {
                            _WindowData wLast;
                            wLast = FindPoolEnd();

                            if (wLast != null)
                            {
                                _WindowData wd = FindWD(CurWindow);
                                CopyBitmap(wd);//Before
                                canvas.Flush();
                                Window[CurWindow + 1].WindowTrans = wLast;
                                Window[CurWindow + 1].FirstTran = null;
                                Window[CurWindow + 1].LastTran = null;
                                Window[CurWindow + 1].WindowTrans.WindowNumber = CurWindow + 1;

                                SIOOpenWindow(b);

                                SIOEraseWindow(CurWindow);
                                
                             }
                            processed = true;
                        }
                    }
                //    Console_WriteLine("[{0}{1}{2} {3}{4} {5}]", (char)msg.Type[0], (char)msg.Type[1], (char)msg.Type[2], (char)msg.SubType[0], (char)msg.SubType[1], txt);
                //    if (!processed) Console_WriteLine("DID NOT PROCESS");
                    //if (prototyping) DrawThumbs();
                    
                }

                test_data.Clear();

                
            }
        }
        int alertY = 0;

        void Alert(string msg) {
           // Console.WriteLine("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"+msg);
            return;
            PCSMessage mdd = new PCSMessage("");
            mdd.MsgSize[0] = 54;
            mdd.MsgSize[1] = 0;
            mdd.iMsgSize = 54;
            mdd.Type = s2b("SIO");
            mdd.Type = s2b("DD");
            mdd.Content = s2b("V2 001001012D731001075400NNN000Y "+msg.Substring(0,14));
            test_data.Add(mdd);
            return;
            alertY++;
            if (canvas == null) return;
            canvas.DrawText("#" + alertY + " - " + msg, pt(new SKPoint(100, 100 + 50 * alertY)), paint);
            PaintWindow();
        }

        char* s2b(string v)
        {
            return v.c_str();
        }

        void AlertEX(string msg, bool persist) {
            mVib.Vibrate(10);
            return;
            //try
            if (persist) {
                if (canvas!=null) canvas.DrawText(new string(' ',30), pt(new SKPoint(100, 100 + 50 * alertY)), paint);
            }
            if (canvas != null)
            {
                if (canvas!=null) canvas.DrawText("#" + alertY + " - " + msg, pt(new SKPoint(100, 100 + 50 * alertY)), paint);
                PaintWindow();
                alertY++;
            }
            //catch (Exception nex) { }

        }

        void onSpawnConnected()
        {
            PrintMessage(canvas, paint, " Spawn Connected .. Preparing Display", 12, 10, 40, 711, fa, 1, false);
            mVib.Vibrate(20);
            if (test_data!=null) test_data.Clear();
            PullData(null);
            
      //      PullData(null);
      //      dbg_autoINDV0254();
      //      PullData(null);
        }

        void OnExpiryÏnfo(char v)
        {
            PrintMessage(canvas, paint, " Sending Login to "+ip_server+"..", 12, 10, 40, 711, fa, 1, false);
            mVib.Vibrate(20);
            SendLogin();
            PullData(null);
        }

        bool Allowed = false;

        void OnClientAuth(char v)
        {
            switch (v) {
                case 'Y':
                    {
                        PrintMessage(canvas, paint, " Connection Allowed", 12, 10, 20, 711, fa, 1, false);
                        mVib.Vibrate(20);
                        Allowed = true;
                        break;
                    }
                case 'V':
                    {
                        DisplayAlert("Client version incompatible", "Login Rejected", "OK");
                        break;
                    }
                case 'M':
                    {
                        DisplayAlert("Server Memory critical", "Login Rejected", "OK");
                        break;
                    }
                case 'W':
                    {
                        DisplayAlert("Server Virtual Memory getting low, notify supervisor", "Warning", "OK");
                        Allowed = true;
                        break;
                    }
                case 'P':
                    {
                        DisplayAlert("Server Physical Memory getting low, notify supervisor", "Warning", "OK");
                        Allowed = true;
                        break;
                    }
                default:
                    {
                        break;
                    }
            }
        }

        SKImage Shrink(SKImage i) {
            SKImageInfo info = new SKImageInfo(3*180, 3*100, SKColorType.Bgra8888);
            SKImage r = SKImage.Create(info);
            i.ScalePixels(r.PeekPixels(), SKFilterQuality.None);
            return r;
        }

        bool prototyping = true;

        void horizLines(int startx, int width, int spacingY, int nlines) {
            for (int y = 0; y < nlines*spacingY; y += spacingY)
            {
                canvas.DrawLine(new SKPoint(startx, y), new SKPoint(startx + width, y), paint);
            }
        }
        void vertLines(int endy, int height, int spacingX, int nlines)
        {
            for (int x = 0; x < nlines * spacingX; x += spacingX)
            {
                canvas.DrawLine(new SKPoint(x, 0), new SKPoint(x ,height), paint);
            }
        }

        SKRect vBtnActuals[22];
        int numVBtns = 0;
        void vBtn(string txt, int row, int col, int bg = 701, bool expand = false) {
            
            int r = (1 + row * 3);
            int c = (0 + col * 7);//change 0 to 82
            SKRect actual = RenderBoxTran(r , c - (expand ? 2 : 0), r+1, c + 3 + (expand ? 4 : 0), 701, 10, true, true, 0, 0);
            vBtnActuals[numVBtns] = actual;
            numVBtns++;
            paint.Color = SKColors.Black;
            if (AcceptPending && row == 3)
            {
                if (IsNumeric(CurAccept.Default) && col == 1) paint.Color = SKColors.Red;
                if (!IsNumeric(CurAccept.Default) && col == 0) paint.Color = SKColors.Red;

            }
            _DrawText(canvas, txt.StartsWith("ENT")? "ENT " + CurAccept.Default:txt, GetSIOPoint(r,c), paint);
        }

        void DrawKbdGrid() {
            paint.Color = new SKColor(100, 255, 100);
            string b = "";
            numVBtns = 0;
            int r=0;
             vBtn("ESC", r, 0); vBtn("F1", r, 1); vBtn("***", r, 2); r++;
           vBtn("PgUp", r, 0); vBtn("seq", r, 1); vBtn("F7", r, 2); r++;
          vBtn("PgDn", r, 0); vBtn("INS", r, 1); vBtn("DEL", r, 2); r++;
          vBtn("abc", r, 0); vBtn("123", r, 1); vBtn("F2", r, 2); r++;
            vBtn("Y", r, 0); vBtn("C", r, 1, 711); vBtn("N", r, 2); r++;
            vBtn("A", r, 0); vBtn("UP", r, 1, 711); vBtn("R", r, 2); r++;
        vBtn("LT", r, 0, 711); vBtn("DN", r, 1, 711);vBtn("RT", r, 2, 711); r++;
        vBtn("ENT", r, 1, 711, true);
        }

        void DrawThumbs() {
            //DrawThumb
            /*DEBUGGING ONLY*/
            if (SavedBM[0].hbitmap != null) canvas.DrawImage(Shrink(SavedBM[0].hbitmap), new SKPoint(1900, 350 * 0), paint);
            if (SavedBM[1].hbitmap != null) canvas.DrawImage(Shrink(SavedBM[1].hbitmap), new SKPoint(1900, 350 * 1), paint);
            if (SavedBM[2].hbitmap != null) canvas.DrawImage(Shrink(SavedBM[2].hbitmap), new SKPoint(1900, 350 * 2), paint);
        }

        void DisplayHorizSep(int row, int col, int siz, char ActColrDisp, int DispColr, int type, int thick, int tag)
        {

            int Color;

            if (CurWindow < 0) return;
            _WindowData wd = FindWD(CurWindow);
            if (wd==null) return;

            Color = wd.ColorScreen;
            if (ActColrDisp == 'D') Color = DispColr;
            if (ActColrDisp == 'H') Color = wd.ColorHelp1;

            DisplayHSep(row, col, siz, 1, 1, Color, tag);
        }

        void RenderHSepTran(int win, int Row, int Left, int Right, int Size, int Foreground, int Type, int Thick, bool ClearLine, short Background)
        {
            /*
            PCSPGMLOC(" - Function Start")


            COLORREF fc;
            COLORREF bc;
            int y;
            short Color;
            BYTE Attribs;

            if (Size == 0) return;

            y = (Row) * CharHeight + (int)(.5 * CharHeight);
            int xl = Left * CharWidth + (int)(.1 * CharWidth);
            int xr = (Left + Size) * CharWidth - (int)(.1 * CharWidth);

            ResolveSIOColor(Foreground, &Color, &Attribs);
            ComputeRGB(Color, Attribs, &fc, &bc);

            //    CreatePen isn't what we want, I think.
            //    Create a DIB with the appropriate characteristics, and draw that.  How?

            HPEN hPen = NULL;
            if (Type == 1)
            {
                LOGBRUSH lb;
                lb.lbColor = fc;
                lb.lbHatch = 0;
                lb.lbStyle = BS_SOLID;
                double i = (CharWidth / 10);
                int dash = (int)(6 * i);
                DWORD pattern[] = { (DWORD)dash, (DWORD)(CharWidth - dash) };
                //    Only available for NT/2000/XP
                hPen = ExtCreatePen(PS_GEOMETRIC | PS_USERSTYLE, 1, &lb, 2, pattern);
                DebugCreateGDI("RenderHSepTran", "ExtCreatePen", hPen);
                //    Fallback for Win98
                if (!hPen)
                {
                    hPen = CreatePen(PS_SOLID, 1, fc);
                    DebugCreateGDI("RenderTextTran", "CreatePen", hPen);
                }
            }
            if (!hPen) return;

            HBRUSH hBrush;
            hBrush = CreateSolidBrush(bc);
            DebugCreateGDI("RenderHSepTran", "CreateSolidBrush", hBrush);
            if (!hBrush) return;
            RECT r;
            SetRect(&r, Left * CharWidth, Row * CharHeight,
                (Left + Size) * CharWidth, (Row + 1) * CharHeight);
            FillRect(hdc, &r, hBrush);
            DebugDeleteGDI("RenderHSepTran", "DeleteObject - brush", hBrush);

            SelectObject(hdc, hPen);
            MoveToEx(hdc, xl, y, NULL);
            LineTo(hdc, xr, y);
            DebugDeleteGDI("RenderHSepTran", "DeleteObject - pen", hPen);

            InvalidateRect(MainWindow, NULL, FALSE);
            */
        }


        void DisplayHSep(int row, int col, int size, int type, int thick, int color, int tag)
        {
            _WindowData wd = FindWD(CurWindow);
            if (wd!=null) RenderHSepTran(CurWindow, row, col, col + size, size, color, type, thick, false, 0);
        }

        void SIOClearError(int lastWinLoaded)
        {
           // throw new NotImplementedException();
        }

        void LoadWindowLines(string b)
        {
            //  throw new NotImplementedException();
        }

        void LoadWindowTrans(string w)
        {
            int MSG_HDR = 0;
            int offset = 3 + MSG_HDR;
            int win = ConvertBufNum(w, MSG_HDR, 3);
            int CPP_SHORT_SIZE = 2;
            short MsgSize = (short)ConvertBufNum(w, 3, CPP_SHORT_SIZE);//*((short*)&(w[3]));
            //TRANHEADER *th;
            short Type = (short)ConvertBufNum(w, offset + 7, CPP_SHORT_SIZE);// (*(short*)&w[offset + 7]);

            win--;
            //if (Type == 2) LoadTextTran(&w[offset]);
            //if (Type == 3) LoadHSepTran(&w[offset]);
            //if (Type == 4) LoadBoxTran(&w[offset]);
            //if (Type == 5) LoadHLineTran(&w[offset], (MsgSize > 30 + offset));
        }

        _WindowData FindPoolEnd()
        {
            return new _WindowData();
        }

        IVibrationService mVib;

        struct StructSavedBM
        {
            string Source;
            SKImage hbitmap;
        };
        const int NUM_BM = 50;
        StructSavedBM SavedBM[50];

        void CopyBitmap(_WindowData wd)
        {
            try
            {
                int i;
                for (i = NUM_BM - 1; i > 0; i--) SavedBM[i] = SavedBM[i - 1];
                savedN = surface.Snapshot();
                
                SKImage hbmWin = savedN;
                SavedBM[0].hbitmap = hbmWin;
                SavedBM[0].Source = "" + CurWindow + " - " + wd.ToString();

       //         Console_WriteLine("...SAVED...." + SavedBM[0].Source);
            }
            catch (System.Exception ex)
            {
                string err = ex.Message;
            }
        }

        void MakeBitmap(_WindowData wLast)
        {
          

        }

     /*   private static void ConnectSocket(string server, int port)
        {
            //Socket s = null;
            IPHostEntry hostEntry = null;

            // Get host related information.
            hostEntry = Dns.GetHostEntry(server);

            // Loop through the AddressList to obtain the supported AddressFamily. This is to avoid
            // an exception that occurs when the host IP Address is not compatible with the address family
            // (typical in the IPv6 case).
            foreach (IPAddress address in hostEntry.AddressList)
            {
                IPEndPoint ipe = new IPEndPoint(address, port);
                Socket tempSocket =
                    new Socket(ipe.AddressFamily, SocketType.Stream, ProtocolType.Tcp);

                tempSocket.Connect(ipe);

                if (tempSocket.Connected)
                {
                    s = tempSocket;
                    break;
                }
                else
                {
                    continue;
                }
            }
            return s;
        }
     */
        static Socket Server;
        static Socket sock;
        static char bytesSent[];
        static char bytesReceived[];

        static Socket SocketConnect(string server, int port)
        {
           string request = "GET / HTTP/1.1\r\nHost: " + server +
                "\r\nConnection: Close\r\n\r\n";
            bytesSent = Encoding.ASCII.GetBytes(request);
            bytesReceived = new byte[4096 * 4];


            IPHostEntry hostEntry = null;

            // Get host related information.
            hostEntry = Dns.GetHostEntry(server);

            // Loop through the AddressList to obtain the supported AddressFamily. This is to avoid
            // an exception that occurs when the host IP Address is not compatible with the address family
            // (typical in the IPv6 case).
            foreach (IPAddress address in hostEntry.AddressList)
            {
                IPEndPoint ipe = new IPEndPoint(address, port);
                Socket tempSocket =
                    new Socket(ipe.AddressFamily, SocketType.Stream, ProtocolType.Tcp);
                try
                {
                    tempSocket.Connect(ipe);
                }
                catch (System.Net.Sockets.SocketException sx) {
                    string msg = sx.Message;
                    throw sx;
                }
                if (tempSocket.Connected)
                {
                    return tempSocket;
                    
                }
                else
                {
                    continue;
                }
            }
            return null;
        }

        class PCSMessage {
            byte MsgSize[2];
            byte Content;// = null;
            byte Type[3];
            byte SubType[2];
            int n = 0;
            short iMsgSize =0;

            PCSMessage(string ini) {
            

            }

            bool Pull(Socket s)
            {
                int n1 = s.Receive(Type, Type.Length, SocketFlags.None);
                if (Type[0] == 32)
                {//WELL KNOWN ERROR CASE {SOMETIMES, ONE BYTE SLIPS, RESOLVE LATER, THIS WORKAROUND SEEMS TO WORK}
                    byte a1 = Type[1];
                    byte a2 = Type[2];
                    byte[] a3 = new byte[1];
                    int n0 = s.Receive(a3, 1, SocketFlags.None);
                    Type[0] = a1;
                    Type[1] = a2;
                    Type[2] = a3[0];
                }
                int n2, n3, n4;
                PullEx(s, out n2, out n3, out n4);
                if (n4 != Content.Length)
                {
                    Console_WriteLine(n4);
                    Console_WriteLine(Content.Length);
                    //Try to recover
                    byte[] Content2 = new byte[Content.Length - n4];
                    int n4b = s.Receive(Content2, Content2.Length, SocketFlags.None);
                    Content2.CopyTo(Content, n4 + 1);
                    Console.WriteLine("====DATA ERR== Content Recovery Attempt");
                }
                n = n1 + n2 + n3 + n4;
                return (n1 == Type.Length && n2 == MsgSize.Length && n3 == SubType.Length && iMsgSize > 0);


            }

            void PullEx(Socket s, out int n2, out int n3, out int n4)
            {
                n2 = s.Receive(MsgSize, MsgSize.Length, SocketFlags.None);
          //      Console.WriteLine("GOT n2="+n2);
                n3 = s.Receive(SubType, SubType.Length, SocketFlags.None);
           //     Console.WriteLine("GOT n3=" + n3);
                iMsgSize = (short)(MsgSize[0] | (MsgSize[1] << 8));
          //      Console.WriteLine("iMsgSize=" + iMsgSize);
                // iMsgSize = MsgSize[0] + MsgSize[1] * 255
                int ContentSize = (int)iMsgSize - 7;
                n4 = 0;
                if (ContentSize > 0)
                {
                    Content = new byte[ContentSize];
                    n4 = s.Receive(Content, Content.Length, SocketFlags.None);
                }
                else {
                    Content = new byte[1];
                    Content[0] = 0;
                    n4 = 1;
                }
         //       Console.WriteLine("GOT n4=" + n4);
            }
            void Console_WriteLine(string x)
            {
                return;
                Console.WriteLine(x);
            }

            void Console_WriteLine(int n4)
            {
                return;
                Console.WriteLine(n4);
            }

            ~PCSMessage() {
                
            }

            string Printable()
            {
                string ret = Type[0] + "" + Type[1] + "" + Type[2] + " " + SubType[0] + "" + SubType[1];
                try
                {
                    ret = ret + " " + Content.Take(20);
                }
                catch (IndexOutOfRangeException inr) {
                    ret = ret + "<ERR";
                }
                return ret;
            }
        };

        static char aa;
        static _PCSFontAttributes fa;
        // This method requests the home page content for the specified server.
        static std::list<PCSMessage> SocketSendReceive(MainPage pg)
        {
            List<PCSMessage> pcs = new List<PCSMessage>();
             try
            {
                bool ok = true;
                int total = 0;
                do {
                    PCSMessage p= new PCSMessage("");
                    if (sock.Available < 7)
                    {
                        break;
                    }
                    ok = p.Pull(sock);
                    try
                    {
                        Console.WriteLine(p.Printable());
                    }
                    catch (System.IndexOutOfRangeException inex) {
                        Console.WriteLine("Corruption!!");
                    }
                    if (!ok)
                    {
                  //      Console_WriteLine("NOT OK");
                    }
                    total += p.n;
                    if (ok)
                    {
                        
                        pcs.Add(p);
                        try
                        {
                         //   pg.PrintMessage(pg.canvas, pg.paint, "x", 5, 1, 1, 730, fa, 0, false);
                          //  pg.PaintWindow();
                        }
                        catch (Exception e) { }
                    }
                } while (ok);
                if (total>0) Console.WriteLine("Bytes rcvd:{0}",total);
            }
            catch (System.Exception ex)
            {
                return null;
            }

            return pcs;
            
        }


        string SimSIOOP(int posx, int posy, int width, int height, int bgColor, int fontColor, string title, string text)
        {
            return "SIO,OP,154,001001025080NSS701701701880701741721721001001001001     E RF YY  NN020041030    YN022041040YN023041040NN023041040YK022001040YK023001040NN023001040 ";
        }
//
//        string[] test_data_arr0 = {
// "CTL,VI,8, "
//, "SIO,OP,154,001001025080NSS701701701880701741721721001001001001     E RF YY  NN020041030    YN022041040YN023041040NN023041040YK022001040YK023001040NN023001040 "
//, "SIO,SH,11,100 "
//, "SIO,EW,8, "
//, "SIO,SC,14,000000 "
//, "SIO,DD,40,V2 001001080D731001100400NNN000Y "
//, "SIO,SC,14,000000 "
//, "SIO,DD,40,V2 024001080D731001100400NNN000Y "
//, "SIO,SC,14,000000 "
//, "SIO,DD,40,V2 025001080D731001100400NNN000Y "
//, "SIO,SC,14,000000 "
//, "SIO,DD,54,V2 001001012D731001075400NNN000Y  Jul  9, 2020 "
//, "SIO,SC,14,000000 "
//, "SIO,DD,40,V2 001016002D731001075400NNN000Y "
//, "SIO,SC,14,000000 "
//, "SIO,DD,52,V2 001030030D731001100400NNN000YC PCS Log On "
//, "SIO,SC,14,000000 "
//, "SIO,DD,52,V2 001070010D731001075400NNN000Y  MNSL6354 H "
//, "SIO,DL,32,001001079002001731000000 "
//, "SIO,DL,32,001001079004001731000000 "
//, "SIO,SC,14,000000 "
//, "SIO,DD,115,V2 024001080D731001075400NNN000Y            (C) Copyrights,  Perfect Circle Solutions, Inc.  1979 thru 2014 "
//, "SIO,SC,14,000000 "
//, "SIO,DD,40,V2 025001080D731001100400NNN000Y "
//, "SIO,SC,14,000000 "
//, "SIO,DD,96,V2 025001063D731001075400NNN000Y            San Diego, CA  (619) 817-8440, v5.4.12 (FWA) "
//, "SIO,SC,14,000000 "
//, "SIO,DD,46,V2 025064017D731001075400NNN000Y  USR: "
//, "SIO,DL,32,024064000003001731000001 "
//, "SIO,DL,32,024001079004001731000000 "
//, "SIO,DB,34,002001079019001001YY711000 "
//, "GFX,DB,75,S            0"
//, "SIO,DB,34,011029046005001001YY751000 "
//, "SIO,SC,14,000000 "
//, "SIO,DD,66,V2 014030024D751001100400NNN000Y  Logon:    [            ] "
//, "SIO,SC,14,000000 "
//, "SIO,DD,62,V2 015030024D751001100400NNN000Y  Password: [        ] "
//, "SIO,SC,14,000000 "
//, "SIO,DD,66,V2 012031025D751001100400NNN000Y   Perfect Circle Software "
//, "SIO,AD,223,V2 23274438014041012005001S880SSNNSSNSNSSSSRFY AUN000001100400NNNY  Enter user-name to login                                                                                                Edit: Arrow, Ins, Del, Bksp "
//, "SIO,SC,14,000000 "
//, "SIO,DD,46,V2 014041012S751001100400NNN000Y  TEST "
//, "SIO,AD,223,V2 23275053015041008005001S880SSNNSSNSNSSSSRFYYAUN000001100400NNNY  Enter password                                                                                                          Edit: Arrow, Ins, Del, Bksp "
//, "SIO,SC,14,000000 "
//, "SIO,DD,56,V2 014054020D751001100400NNN000Y  TEST SECURUITY "
//, "SIO,US,19,TEST        "
//////, "DEV,SAVE"
////, "CTL,VI,8, "
////, "SIO,OP,154,015020023080YSS761761761761761761761761014054020005     N RF YY  NN022041023100 NN022041040NN023041040NN023041040NN022001040NN023001040NN023001040 "
////, "SIO,SH,11,200 "
////, "SIO,SC,14,000000 "
////, "SIO,DD,44,V2 017039002S761001100400NNN000Y  51 "
////, "SIO,SC,14,000000 "
////, "SIO,DD,58,V2 017044030S761001100400NNN000Y  PCS Food Company "
////, "SIO,SC,14,000000 "
////, "SIO,DD,44,V2 018039002S761001100400NNN000Y  52 "
////, "SIO,SC,14,000000 "
////, "SIO,DD,62,V2 018044030S761001100400NNN000Y  PCS Furniture System "
////, "SIO,SC,14,000000 "
////, "SIO,DD,44,V2 019039002S761001100400NNN000Y  53 "
////, "SIO,SC,14,000000 "
////, "SIO,DD,63,V2 019044030S761001100400NNN000Y  PCS Export Management "
////, "SIO,SC,14,000000 "
////, "SIO,DD,44,V2 020039002S761001100400NNN000Y  54 "
////, "SIO,SC,14,000000 "
////, "SIO,DD,66,V2 020044030S761001100400NNN000Y  PCS Distribution Company "
////, "SIO,SC,14,000000 "
////, "SIO,DD,44,V2 021039002S761001100400NNN000Y  55 "
////, "SIO,SC,14,000000 "
////, "SIO,DD,67,V2 021044030S761001100400NNN000Y  PCS Manufacturing Company "
////, "SIO,SC,14,000000 "
////, "SIO,DD,66,V2 023039033S761001100400NNN000Y   (F2 for more companies) "
//////, "DEV,RESTORE"
////, "SIO,SC,14,000000 "
////, "SIO,DD,63,V2 016026021S761001100400NNN000Y  Enter Company No [  ] "
////, "SIO,SC,14,000000 "
////, "SIO,DD,44,V2 016044002S761001100400NNN000Y  99 "
////, "SIO,SC,14,000000 "
////, "SIO,DD,65,V2 016049030S761001100400NNN000Y  Perfect Circle Software "
////, "SIO,SH,11,100 "
////, "SIO,SC,14,000000 "
////, "SIO,DD,44,V2 016044002D711001100400NNN000Y  99 "
////, "SIO,SC,14,000000 "
//////, "SIO,DD,57,V2 016049030D711001100400NNN000Y  Invalid Company "
//////, "SIO,SC,14,000000 "
//////, "SIO,DD,44,V2 016044002S711001100400NNN000Y  99 "
//////, "SIO,SC,14,000000 "
////, "SIO,DD,40,V2 016049030S711001100400NNN000Y "
////, "SIO,AD,318,V2 23275336016044002001001S711SSNSSSSSRSSSSRFY   N000001100400NNNY  Enter Company Code                                                                                                      Enter Flag: ?/F2 for List                                                                                               99 "
////, "SIO,SC,14,000000 "
////, "SIO,DD,44,V2 016044002S711001100400NNN000Y  99 "
////, "SIO,CE,8, "
////, "SIO,OP,154,017023025080YSS731731731731731741721721016044002001     E RF YY  NN025028030100 NN021041040NN022041040NN023041040NN021001040NN022001040NN023001040 "
////, "SIO,DL,32,016043000001001731000001 "
////, "SIO,DL,32,016047000001001731000001 "
////, "SIO,SC,14,000000 "
////, "SIO,DD,44,V2 018027002S731001100400NNN000Y  51 "
////, "SIO,SC,14,000000 "
////, "SIO,DD,58,V2 018031048S731001100400NNN000Y  PCS Food Company "
////, "SIO,SC,14,000000 "
////, "SIO,DD,44,V2 019027002S731001100400NNN000Y  52 "
////, "SIO,SC,14,000000 "
////, "SIO,DD,62,V2 019031048S731001100400NNN000Y  PCS Furniture System "
////, "SIO,SC,14,000000 "
////, "SIO,DD,44,V2 020027002S731001100400NNN000Y  53 "
////, "SIO,SC,14,000000 "
////, "SIO,DD,63,V2 020031048S731001100400NNN000Y  PCS Export Management "
////, "SIO,SC,14,000000 "
////, "SIO,DD,44,V2 021027002S731001100400NNN000Y  54 "
////, "SIO,SC,14,000000 "
////, "SIO,DD,66,V2 021031048S731001100400NNN000Y  PCS Distribution Company "
////, "SIO,SC,14,000000 "
////, "SIO,DD,44,V2 022027002S731001100400NNN000Y  55 "
////, "SIO,SC,14,000000 "
////, "SIO,DD,67,V2 022031048S731001100400NNN000Y  PCS Manufacturing Company "
////, "SIO,SC,14,000000 "
////, "SIO,DD,44,V2 023027002S731001100400NNN000Y  56 "
////, "SIO,SC,14,000000 "
////, "SIO,DD,60,V2 023031048S731001100400NNN000Y  PCS Service Center "
////, "SIO,SC,14,000000 "
////, "SIO,DD,44,V2 024027002S731001100400NNN000Y  57 "
////, "SIO,SC,14,000000 "
////, "SIO,DD,60,V2 024031048S731001100400NNN000Y  PCS Retail Company "
////, "SIO,SC,14,000000 "
////, "SIO,DD,44,V2 018025002S731001100400NNN000N  -> "
////, "SIO,AD,221,V2 23275872018024001001001S731SSNSSSSSRSSSS2DY   N000001100400NNNN  Enter Company Code                                                                                                      Enter Flag: ?/F2 for List "
////, "SIO,SC,14,000000 "
////, "SIO,DD,40,V2 018024001S731001100400NNN000N "
////, "SIO,SC,14,000000 "
////, "SIO,DD,40,V2 018024003S731001100400NNN000N "
////, "SIO,SC,14,000000 "
////, "SIO,DD,44,V2 019025002S731001100400NNN000N  -> "
////, "SIO,AD,221,V2 23280050019024001001001S731SSNSSSSSRSSSS2DY   N000001100400NNNN  Enter Company Code                                                                                                      Enter Flag: ?/F2 for List "
////, "SIO,SC,14,000000 "
////, "SIO,DD,40,V2 019024001S731001100400NNN000N "
////, "SIO,SC,14,000000 "
////, "SIO,DD,40,V2 019024003S731001100400NNN000N "
////, "SIO,SC,14,000000 "
////, "SIO,DD,44,V2 020025002S731001100400NNN000N  -> "
////, "SIO,AD,221,V2 23280106020024001001001S731SSNSSSSSRSSSS2DY   N000001100400NNNN  Enter Company Code                                                                                                      Enter Flag: ?/F2 for List "
////, "SIO,DE,40,Invalid - Use '?' or F2 for list "
////, "SIO,AB,47,00210384671N  No    No - change company "
////, "SIO,AB,42,00110384671Y  Yes   Yes - continue "
//        };
    }
}

class PCSClientApp : iAlge {
   
public:
    iAlge* init() {
        return (iAlge*)this;
    }
    
};
