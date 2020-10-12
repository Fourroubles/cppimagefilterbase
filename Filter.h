#pragma once

#include "png_toolkit.h"
#include "WorkFile.h"
#include <vector>
#include <algorithm>
#include <ctime>

class Filter {
public:
	virtual void RedPainting(image_data &imgData) {};
	virtual void BlackWhitePainting(image_data &imgData, std::vector<int> CoordinateUsingFilter) {};
	virtual void ThresholdPainting(image_data &imgData) {};

	int ColcualteUpCoordinate(image_data &imgData, const WorkFile ConfigCoordinate);
	int ColcualteLeftCoordinate(image_data &imgData, const WorkFile ConfigCoordinate);
	int ColcualteBackCoordinate(image_data &imgData, const WorkFile ConfigCoordinate);
	int ColcualteRightCoordinate(image_data &imgData, const WorkFile ConfigCoordinate);
	void ColcualteCoordinate(WorkFile ConfigCoordinate, image_data &imgData, std::vector<int> &CoordinateUsingFilter);
};

class RedFilter: public Filter {
public:
	virtual void RedPainting(image_data &imgData);
	std::vector<int> CoordinateUsingFilter;
};

class BlackWhiteFilter: public Filter {
public:
	virtual void BlackWhitePainting(image_data &imgData, std::vector<int> CoordinateUsingFilter);
};

class ThresholdFilter : public Filter {
public:
	virtual void ThresholdPainting(image_data &imgData);
	std::vector<int> CoordinateUsingFilter;
private:
	int CalculateMediana(std::vector<int> CoordinateUsingFilter, image_data &imgData, int i, int j);
};

class SelectionFilter {
public:
	void Selection(WorkFile ConfigData, image_data &imgData);
};