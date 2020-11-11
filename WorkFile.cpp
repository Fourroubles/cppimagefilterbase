#include "WorkFile.h"

void WorkFile::OutPutFile(const std::string &config) {
	std::ifstream file(config);
	Data tmp;
	while (!file.eof())
	{
		file >> tmp.FilterName >> tmp.up >> tmp.left >> tmp.back >> tmp.right;
		massData.push_back(tmp);
	} 
	file.close();
}