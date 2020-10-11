#pragma once

#include <string>
#include <fstream>
#include <cstdlib>
#include <iostream>

class WorkFile {
public:
	std::string FilterName;
	int up, left, back, right;
	void OutPutFile(const std::string &config);
};
