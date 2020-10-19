#ifdef CLOG_INCLUDED
#else
#define CLOG_INCLUDED
class CLog {
	FILE *outp;
public:
	CLog() {
#ifndef METRO
		outp = fopen("log2.txt", "w");
#endif
	}

	void it(char* line) {
#ifndef METRO
		fprintf(outp,", \"%s\"\n", line);
#endif
	}

	~CLog() {
#ifndef METRO
		if (outp)
		fclose(outp);
#endif
	}

};
#endif