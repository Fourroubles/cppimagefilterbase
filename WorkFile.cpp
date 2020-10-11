#include "WorkFile.h"

void WorkFile::OutPutFile(const std::string &config) {
	std::ifstream file(config);
	if (!file) {
		std::cout << "File not open!";
		exit(0);
	}
	file >> FilterName >> up >> left >> back >> right;
	file.close();
}