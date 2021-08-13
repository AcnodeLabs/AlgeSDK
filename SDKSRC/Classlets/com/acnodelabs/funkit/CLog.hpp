#ifdef CLOG_INCLUDED
#else
#define CLOG_INCLUDED
#include <string>

class CLog {
    FILE *outp;
public:
    CLog() {
#ifndef METRO
        outp = fopen("log.txt", "w");
#endif
    }

    void it(char* line, bool printalso = true) {
#ifndef METRO
        if (outp) fprintf(outp,"%s", line);
#endif
        if (printalso) printf("%s",line);
    }

    void its(std::string line, bool printalso = true) {
        it((char*)line.c_str(),printalso);
        it((char*)"\n",printalso);
    }

    ~CLog() {
#ifndef METRO
        if (outp) fclose(outp);
#endif
    }

};
#endif
