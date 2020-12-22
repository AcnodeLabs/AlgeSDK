#ifndef NO_NATS
#ifdef CNETMSG_H_INCLUDED
#else
#define CNETMSG_H_INCLUDED

#include <nats.h>
#include <string>
using namespace std;

#define STATS_IN        0x1
#define STATS_OUT       0x2
#define STATS_COUNT     0x4
#define MAX_SERVERS     (10)


class CNetMsg {
	natsConnection      *conn = NULL;
	natsOptions         *opts = NULL;
	natsSubscription    *sub = NULL;
	natsStatistics      *stats = NULL;
	natsMsg             *msg = NULL;
	natsStatus          s;

	
	string appname;
		
public:
	string prepend;

	CNetMsg();
	
	void Post(string data);

	void Post(string subject, string data);

	int Connect(string _appname, bool local);
	int Connect(string _appname);

	int SubscribeConnect(string _appname, bool local);

	static void TestCNetMsg();

	~CNetMsg();

};

#endif

#endif //NO_NATS
