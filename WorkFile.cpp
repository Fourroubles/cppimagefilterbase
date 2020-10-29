#include "WorkFile.h"

void WorkFile::OutPutFile(const std::string &config) {
	std::ifstream file(config);
	char *str = new char[150];
	int k = 0;
	while (!file.eof()) {

		file.getline(str, 150);
		FilterName.clear();
		for (int i = 0; str[i] != '\n'; ++i) {
			if (str[i] == ' ') {
				
				k = i;
				break;
			}
			FilterName.push_back(str[i]);
		}
		up = str[k + 1] - '0';
		left = str[k + 3] - '0';
		back = str[k + 5] - '0';
		right = str[k + 7] - '0';
	}
	file.close();
}