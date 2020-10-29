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
		if (str[k + 2] >= '0' && str[k + 2] <= '9') {
			up = up * 10 + (str[k + 2] - '0');
			k++;
		}
	
		
		left = str[k + 3] - '0';
		if (str[k + 4] >= '0' && str[k + 4] <= '9') {
			left = left * 10 + str[k + 3] - '0';
			k++;
		}
	

		back = str[k + 5] - '0';
		if (str[k + 6] >= '0' && str[k + 6] <= '9') {
			back = back * 10 + str[k + 6] - '0';
			k++;
		}
		

		right = str[k + 7] - '0';
		if (str[k + 8] >= '0' && str[k + 8] <= '9') {
			right = right * 10 + str[k + 8] - '0';
			k++;
		}
		
	}
	file.close();

	std::cout << FilterName<<up<<left<<back<<right;
}