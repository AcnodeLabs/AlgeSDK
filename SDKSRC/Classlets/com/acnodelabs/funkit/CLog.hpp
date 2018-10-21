#ifdef CLOG_INCLUDED
#else
#define CLOG_INCLUDED
class CLog {
	FILE *outp;
public:
	CLog() {
#ifndef METRO
		outp = fopen("log.txt", "w");
#endif
	}

	void it(char* line) {
#ifndef METRO
		fprintf(outp,"%s", line);
#endif
	}

	~CLog() {
#ifndef METRO
		fclose(outp);
#endif
	}

};
#endif