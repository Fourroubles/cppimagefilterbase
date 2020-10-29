#pragma once

#include "png_toolkit.h"
#include "WorkFile.h"
#include <vector>
#include <algorithm>
#include <ctime>



class Filter {
public:
	/*virtual void RedPainting(image_data &imgData) {};
	virtual void BlackWhitePainting(image_data &imgData, std::vector<int> CoordinateUsingFilter) {};
	virtual void ThresholdPainting(WorkFile ConfigData, image_data &imgData) {};*/

	int ColcualteUpCoordinate(image_data &imgData, Data ConfigCoordinate);
	int ColcualteLeftCoordinate(image_data &imgData, Data ConfigCoordinate);
	int ColcualteBackCoordinate(image_data &imgData, Data ConfigCoordinate);
	int ColcualteRightCoordinate(image_data &imgData, Data ConfigCoordinate);
	void ColcualteCoordinate(Data ConfigCoordinate, image_data &imgData, std::vector<int> &CoordinateUsingFilter);
};

class RedFilter: public Filter {
public:
	/*virtual */void RedPainting(image_data &imgData);
	std::vector<int> CoordinateUsingFilter;
};

class BlackWhiteFilter: public Filter {
public:
	/*virtual*/ void BlackWhitePainting(image_data &imgData, std::vector<int> CoordinateUsingFilter);
};

class ThresholdFilter : public Filter {
public:
	/*virtual*/ void ThresholdPainting(Data ConfigData, image_data &imgData);
	std::vector<int> CoordinateUsingFilter;
private:
	bool CalculateMediana(std::vector<int> CoordinateUsingFilter, const image_data &imgData, int i, int j);
	std::vector<int> FillingqontainerIntensity(std::vector<int> CoordinateUsingFilter, const image_data &imgData, int  i, int j);
	void ChangePixel(image_data &imgData, std::vector<int> CoordinateUsingFilter);
};


class BlurFilter : public Filter {
public:
	/*virtual*/ void BlurPainting(Data ConfigData, image_data &imgData);
	std::vector<int> CoordinateUsingFilter;
private:
	std::vector<int>�onvolution�ount(std::vector<int> CoordinateUsingFilter, const image_data &imgData, int  i, int j);

};

class SelectionFilter {
public:
	void Selection(WorkFile ConfigData, image_data &imgData);
};