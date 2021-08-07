#ifdef CCFG_INCLUDED
#else
#define CCFG_INCLUDED
#include <string>
#include <vector>
#include <map>

using namespace std;

class CCfg {
	std::map<int, std::string> stringLookupTable;
	FILE *finp;
	char line[1024];
public:
	map<string,string> vals;
	vector<int> ints;
	int sum = 0;
	CCfg(const char* fname) {
#ifndef METRO
		FILE* finp = fopen(fname, "r");
		if (finp) {
			while (!feof(finp)) {
				fgets(line, 1024, finp);
				try {
					char* a = strchr(line, ',');
					if (a) {
						a[0] = 0;
						a++;
						vals[string(line)] = a;
						int intt = std::stoi(string(a));
						ints.push_back(intt);
						sum += intt;
					}
				}
				catch (...) {}
			}
			fclose(finp);
			finp = NULL;
		}
		//printf("%s", vals["kamwali"].c_str());
		printf("sum in %s=%d\n", fname, sum);
#endif
	}

	void it(char* line, bool printalso = true) {
#ifndef METRO
		//if (&finp) fprintf(&finp,"%s", line);
#endif
		if (printalso) printf(line);
	}

	void its(std::string line, bool printalso = true) {
		it((char*)line.c_str(),printalso);
		it((char*)"\n",printalso);
	}

	~CCfg() {
#ifndef METRO
		if (finp) fclose(finp);
#endif
	}

};
#endif
