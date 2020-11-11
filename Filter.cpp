#include "Filter.h"

void Red::filter(image_data &imgData, std::vector<int> CoordinateUsingFilter) {
	for (int i = CoordinateUsingFilter[0]; i < CoordinateUsingFilter[1]; ++i) {
		for (int j = CoordinateUsingFilter[2]; j < CoordinateUsingFilter[3]; ++j) {
			int ptr = (i*imgData.w + j)*imgData.compPerPixel;
			imgData.pixels[ptr + 0] = (unsigned char)255;
			imgData.pixels[ptr + 1] = imgData.pixels[ptr + 2] = (unsigned char)0;
		}
	}
}

void BlackWhite::filter(image_data &imgData, std::vector<int> CoordinateUsingFilter) {
	for (int i = CoordinateUsingFilter[0]; i <= CoordinateUsingFilter[1]; ++i) {
		for (int j = CoordinateUsingFilter[2]; j <= CoordinateUsingFilter[3]; ++j) {
			int ptr = (i*imgData.w + j)*imgData.compPerPixel;
			int red = imgData.pixels[ptr + 0];
			int green = imgData.pixels[ptr + 1];
			int blue = imgData.pixels[ptr + 2];
			int intensity = (3 * red + 6 * green + blue) / 10;
			imgData.pixels[ptr + 0] = imgData.pixels[ptr + 1] = imgData.pixels[ptr + 2] = (unsigned char)intensity;
		}
	}
}

void Threshold::filter(image_data &imgData, std::vector<int> CoordinateUsingFilter) {
	ManagerFilter* manager = new ManagerThresholdFilter();
	CopyPixel = ManagerFilter::copyImage(imgData);
	for (int i = CoordinateUsingFilter[0]; i <= CoordinateUsingFilter[1]; ++i) {
		for (int j = CoordinateUsingFilter[2]; j <= CoordinateUsingFilter[3]; ++j) {
			int ptr = (i*imgData.w + j)*imgData.compPerPixel;
			intensity = manager->calculateIntensity(CoordinateUsingFilter, CopyPixel, i, j);
			if (imgData.pixels[ptr] < intensity[intensity.size() / 2]) {
				imgData.pixels[ptr + 0] = imgData.pixels[ptr + 1] = imgData.pixels[ptr + 2] = (unsigned char)0;
			}
		}
	}
}

void Blur::filter(image_data &imgData, std::vector<int> CoordinateUsingFilter) {
	ManagerFilter* manager = new ManagerBlurFilter();
	CopyPixel = ManagerFilter::copyImage(imgData);
	for (int i = CoordinateUsingFilter[0]; i <= CoordinateUsingFilter[1]; ++i) {
		for (int j = CoordinateUsingFilter[2]; j <= CoordinateUsingFilter[3]; ++j) {
			int ptr = (i*imgData.w + j)*imgData.compPerPixel;
			intensity = manager->calculateIntensity(CoordinateUsingFilter, CopyPixel, i, j);
			imgData.pixels[ptr + 0] = (unsigned char)intensity[0];
			imgData.pixels[ptr + 1] = (unsigned char)intensity[1];
			imgData.pixels[ptr + 2] = (unsigned char)intensity[2];
		}
	}
}


void Edge::filter(image_data &imgData, std::vector<int> CoordinateUsingFilter) {
	ManagerFilter* manager = new ManagerEdgeFilter();
	CopyPixel = ManagerFilter::copyImage(imgData);
	for (int i = CoordinateUsingFilter[0]; i < CoordinateUsingFilter[1]; ++i) {
		for (int j = CoordinateUsingFilter[2]; j < CoordinateUsingFilter[3]; ++j) {
			int ptr = (i*imgData.w + j)*imgData.compPerPixel;
			intensity = manager->calculateIntensity(CoordinateUsingFilter, CopyPixel, i, j);
			imgData.pixels[ptr + 0] = imgData.pixels[ptr + 1] = imgData.pixels[ptr + 2] = (unsigned char)intensity[0];

		}
	}
}