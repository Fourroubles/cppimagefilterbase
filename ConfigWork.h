#pragma once
#include <iostream>
#include <vector>
#include "Filter.h"

enum nameFilter {
	RED_FILTER = 0,
	THRESHOLD_FILTER,
	BLUR_FILTER,
	EDGE_FILTER,
	BLACK_WHITE_FILTER
};

class configWork {
public:
	void usingFilter(std::vector<Data> MassData, image_data &imgData);
	void detectFilter(std::vector<Data> MassData);
	void filingFilter();
private:
	std::vector<Filter*> typeFilter;
	std::vector<nameFilter> name;
	static Filter* createFilter(nameFilter);
	std::vector<int> ColcualteCoordinate(Data ConfigCoordinate, image_data &imgData);
	int ColcualteUpCoordinate(image_data &imgData, Data ConfigCoordinate);
	int ColcualteLeftCoordinate(image_data &imgData, Data ConfigCoordinate);
	int ColcualteBackCoordinate(image_data &imgData, Data ConfigCoordinate);
	int ColcualteRightCoordinate(image_data &imgData, Data ConfigCoordinate);

};