#include "WorkFile.h"

void WorkFile::OutPutFile(const std::string &config) {
	std::ifstream file(config);
	do
	{
		file >> FilterName >> up >> left >> back >> right;
	} while (!file.eof());
	file.close();

	std::cout << FilterName<<up<<left<<back<<right;
}