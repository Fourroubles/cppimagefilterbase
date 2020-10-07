#include "WorkFile.h"

void WorkFile::OutPutFile(const std::string &config) {
	std::ifstream file(config);
	if (!file) {
		std::cout << "File not open!";
		exit(0);
	}
	file >> FilterName >> u >> l >> b >> r;
	file.close();
}