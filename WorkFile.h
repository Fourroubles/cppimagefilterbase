#pragma once

#include <string>
#include <vector>
#include <fstream>
#include <cstdlib>
#include <iostream>

typedef struct Data {
	std::string FilterName;
	int up, left, back, right;
}Data;

class WorkFile {
public:
	std::vector<Data> massData;
	void OutPutFile(const std::string &config);
};
