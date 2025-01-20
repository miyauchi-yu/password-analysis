#include "analysis.hpp"

/*
 * password analysis main
 */
int main(int argc, char *argv[]) {
    // parameter check
    if (argc != 5) {
        std::cout << "Usage: ./pascheck <IP Address> <ID> <Password length> <Number of times>\n";
        return 1;
    }
    // call analysis
    std::string host = argv[1];
    std::string id = argv[2];
	const int length = std::stoi(argv[3]);
	const int num = std::stoi(argv[4]);
    Analysis analysis = Analysis(host, id, length, num);
    std::string password = analysis.run();
    std::cout << "Generated password: " << password << "\n";
    return 0;
}
