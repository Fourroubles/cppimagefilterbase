#pragma once

#include <string>
#include <fstream>
#include <cstdlib>
#include <iostream>

class WorkFile {
public:
	std::string FilterName;
	int u, l, b, r;
	void OutPutFile(const std::string &config);
};
