#include "WorkFile.h"

void WorkFile::OutPutFile(const std::string &config) {
	std::ifstream file(config);
	file >> FilterName >> up >> left >> back >> right;
	file.close();
}