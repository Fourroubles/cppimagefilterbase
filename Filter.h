#pragma once

#include "png_toolkit.h"
#include "WorkFile.h"
#include <vector>

class Filter {
public:
	virtual void RedPainting(image_data &imgData) = 0;

	int ColcualteUpCoordinate(image_data &imgData, const WorkFile ConfigCoordinate);
	int ColcualteLeftCoordinate(image_data &imgData, const WorkFile ConfigCoordinate);
	int ColcualteBackCoordinate(image_data &imgData, const WorkFile ConfigCoordinate);
	int ColcualteRightCoordinate(image_data &imgData, const WorkFile ConfigCoordinate);
};

class RedFilter: public Filter {
public:
	void ColcualteCoordinate(WorkFile ConfigCoordinate, image_data &imgData);
	virtual void RedPainting(image_data &imgData);
private:
	std::vector<int> CoordinateUsingFilter;
};

class SelectionFilter {
public:
	void Selection(WorkFile ConfigData, image_data &imgData);
};