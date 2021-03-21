#ifdef WIN32
#include "stdafx.h"
#endif

#ifndef NO_NATS

#ifdef CNETMSG_CPP_INCLUDED
#else
#define CNETMSG_CPP_INCLUDED
#include "CNetMsg.h"

bool        async = true;
const char  *subj = "foo";
const char  *txt = "hello";
const char  *name = "worker";
volatile int64_t     total = 1000000;

volatile int64_t countIn = 0;

volatile int64_t dropped = 0;
int64_t          start = 0;
volatile int64_t elapsed = 0;
bool             print = false;
int64_t          timeout = 10000; // 10 seconds.

const char       *certFile = NULL;
const char       *keyFile = NULL;

void (*callBackIn)(string) = NULL;                        // C

	CNetMsg::CNetMsg() {
#ifdef WIN32
		//MessageBoxA(NULL, "callback scheme from CNats is Disabled", "Info", MB_OK);
#endif // WIN32

		prepend = "xal";
		conn = NULL;
		msg = NULL;
		s = NATS_ERR;
	}
	
		static void onMsgIn(natsConnection *nc, natsSubscription *sub, natsMsg *msg, void *closure) 
	{
		//printf("Received msg: %s - %.*s\n",	natsMsg_GetSubject(msg),natsMsg_GetDataLength(msg),	natsMsg_GetData(msg));

		if (start == 0)	start = nats_Now();

		// We should be using a mutex to protect those variables since
		// they are used from the subscription's delivery and the main
		// threads. For demo purposes, this is fine.
		if (++countIn == total)	elapsed = nats_Now() - start;
		try {
			if (callBackIn != nullptr) callBackIn(natsMsg_GetData(msg));
			natsMsg_Destroy(msg);
		}
		catch (...) {
		}
	}

	void CNetMsg::Post(string data) {
		Post(prepend +"."+ appname , data);
	}

	void CNetMsg::Post(string subject, string data) {
		s = natsMsg_Create(&msg, subject.c_str(), NULL, data.c_str(), data.length());
		if (s == NATS_OK)
		{
			s = natsConnection_PublishMsg(conn, msg);
		}
		natsMsg_Destroy(msg);
		s = NATS_OK;
	}
	
	//use when you want to listen and act
	int CNetMsg::SubscribeConnect(string _appname, bool local) {
		string arukas;
		if (local) arukas = "nats://localhost:4222";
	//	else arukas = "http://seaof-163-43-82-147.jp-tokyo-01.arukascloud.io:31706/";
        else arukas = "nats://192.168.100.153:4222/";

		//"nats://localhost:4222";
		this->appname = _appname;
		s = natsConnection_ConnectTo(&conn, arukas.c_str());// NATS_DEFAULT_URL);
		Post("hello!");

		//SUBSCRIBE::https://github.com/nats-io/cnats/blob/master/examples/subscriber.c
		string subjectSub = (prepend + "." + appname );
		s = natsConnection_Subscribe(&sub, conn, subjectSub.c_str(), onMsgIn, NULL);
		return s;
	}
	
	//use when you want to serve data
	//clients should use n.SubscribeConnect(_appname, false);
	int CNetMsg::Connect(string _appname, bool local) {
		string arukas;
		if (local) arukas = "nats://localhost:4222";
		else arukas = "http://seaof-163-43-82-147.jp-tokyo-01.arukascloud.io:31706/";
	
		//"nats://localhost:4222";
		this->appname = _appname;
		s = natsConnection_ConnectTo(&conn, arukas.c_str());// NATS_DEFAULT_URL);
		Post("hello!");
		
		//SUBSCRIBE::https://github.com/nats-io/cnats/blob/master/examples/subscriber.c
		string subjectSub = (prepend + "." + appname + ".In");
		s = natsConnection_Subscribe(&sub, conn, subjectSub.c_str() , onMsgIn, NULL);
		return s;
	}

	CNetMsg::~CNetMsg() {
		// Anything that is created need to be destroyed
		Post("Bye!");
		natsConnection_Destroy(conn);
	}

	void CNetMsg::TestCNetMsg() {
		CNetMsg c;
		c.Connect("tester", true);
		c.Post("hello");
	}

	
#endif
#endif//f NO_NATS
