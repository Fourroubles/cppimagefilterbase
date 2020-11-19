#pragma once
#include <iostream>
#include "png_toolkit.h"
#include <vector>
#include <algorithm>

class ManagerFilter {
public:
	virtual std::vector<unsigned char> calculateIntensity(std::vector<int> CoordinateUsingFilter, image_data &imgData, int  i, int j) = 0;
	virtual ~ManagerFilter() {};
	static image_data copyImage(image_data &imgData);
};

class ManagerThresholdFilter : public ManagerFilter{
public:
	std::vector<unsigned char> calculateIntensity(std::vector<int> CoordinateUsingFilter, image_data &imgData, int  i, int j) override;
};

class ManagerBlurFilter : public ManagerFilter {
public: 
	std::vector<unsigned char> calculateIntensity(std::vector<int> CoordinateUsingFilter, image_data &ImgData, int i, int j) override;
};

class ManagerEdgeFilter : public ManagerFilter {
public:
	std::vector<unsigned char> calculateIntensity(std::vector<int> CoordinateUsingFilter, image_data &ImgData, int i, int j) override;
};