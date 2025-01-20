#ifndef _H_ANALYSIS_
#define _H_ANALYSIS_
#include <winsock2.h>
#include <ws2tcpip.h>
#include <windows.h>
#include <libssh2.h>
#include <string>
#include <iostream>

class Analysis {
    public:
        Analysis(std::string host, std::string id, const int length, const int num);
        ~Analysis();
        std::string run();
    private:
        std::string host;
        std::string id;
        int length;
		int num;
        LIBSSH2_SESSION *session;
    private:
        std::string generate(const int length);
};

#endif // _H_ANALYSIS_
