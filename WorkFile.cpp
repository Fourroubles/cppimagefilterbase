#include "WorkFile.h"

void WorkFile::OutPutFile(const std::string &config) {
	std::ifstream file(config);
	while (!file.eof())
	{
		file >> FilterName >> up >> left >> back >> right;
	}
	file.close();
}