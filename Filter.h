#pragma once

#include "png_toolkit.h"
#include "WorkFile.h"
#include "ManagerFilter.h"
#include <vector>
#include <ctime>


class Filter {
public:
	virtual void filter(image_data &imgData, std::vector<int> CoordinateUsingFilter) = 0;
	virtual ~Filter() {};
};

class Red : public Filter  {
public:
	void filter(image_data &imgData, std::vector<int> CoordinateUsingFilter) override;
};

class BlackWhite : public Filter {
public:
	void filter(image_data &imgData, std::vector<int> CoordinateUsingFilter) override;
};

class Threshold : public Filter {
private:
	  image_data CopyPixel;
	  std::vector<int> intensity;
public:
	void filter(image_data &imgData, std::vector<int> CoordinateUsingFilter)  override;
	~Threshold() { delete[] CopyPixel.pixels; };
};

class Blur : public Filter {
private:
	image_data CopyPixel;
	std::vector<int> intensity;
public:
	void filter(image_data &imgData, std::vector<int> CoordinateUsingFilter) override;
	~Blur() { delete[] CopyPixel.pixels; };
};

class Edge : public Filter {
private:
	image_data CopyPixel;
	std::vector<int> intensity;
public:
	void filter(image_data &imgData, std::vector<int> CoordinateUsingFilter) override;
	~Edge() { delete[] CopyPixel.pixels; };
};