#ifdef CMICROSVC_INCLUDED
#else
#define CMICROSVC_INCLUDED
#include <process.h>
#include <vector>

using namespace std;

class CMicroservice {
	static vector<CMicroservice*> services;
public:
	string fullpath;
	int returnValue;

	CMicroservice() {
		
	}
	
	int Start() {
		return system(fullpath);
	}

	void Stop() {

	}

	~CMicroservice() {
	}

	static CMicroservice* Create(string _fullpath) {
		CMicroservice svc;
		svc.fullpath = _fullpath;
		svc.Start();
		services.push_back(&svc);
	}

	static StopAll() {
		for (auto const& svc : services) {
			svc->Stop();
			delete svc;
		}
		services.clear();
	}
};
#endif