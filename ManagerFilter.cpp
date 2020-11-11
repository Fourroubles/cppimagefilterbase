#include "ManagerFilter.h"

image_data ManagerFilter::copyImage(image_data &imgData){
	image_data CopyPixel;
	CopyPixel = imgData;
	CopyPixel.h = imgData.h;
	CopyPixel.compPerPixel = imgData.compPerPixel;
	CopyPixel.w = imgData.w;
	int tmp = imgData.w*imgData.h*imgData.compPerPixel;
	CopyPixel.pixels = new stbi_uc[tmp];
	for (int i = 0; i < tmp; i++) {
		CopyPixel.pixels[i] = imgData.pixels[i];
	}
	return CopyPixel;
}

std::vector<int> ManagerThresholdFilter::calculateIntensity(std::vector<int> CoordinateUsingFilter, image_data &imgData, int  i, int j) {
		std::vector<int> intensity;
		for (int k = i - 2; k <= i + 2; ++k) {
			if (k >= CoordinateUsingFilter[0] && k <= CoordinateUsingFilter[1]) {
				for (int h = j - 2; h <= j + 2; ++h) {
					if (h >= CoordinateUsingFilter[2] && h < CoordinateUsingFilter[3]) {
						intensity.push_back(imgData.pixels[(k*imgData.w + h)*imgData.compPerPixel]);
					}
				}
			}
		}
		std::sort(intensity.begin(), intensity.end());
		return intensity;
}

std::vector<int> ManagerBlurFilter::calculateIntensity(std::vector<int> CoordinateUsingFilter, image_data &imgData, int  i, int j) {
	std::vector<int> intensity;
	int mass = 0;
	int red = 0, green = 0, blue = 0;
	for (int k = i - 1; k <= i + 1; ++k) {
		if (k >= CoordinateUsingFilter[0] && k < CoordinateUsingFilter[1]) {
			for (int h = j - 1; h <= j + 1; ++h) {
				if (h >= CoordinateUsingFilter[2] && h < CoordinateUsingFilter[3]) {
					int ptr = (k*imgData.w + h)*imgData.compPerPixel;
					red += imgData.pixels[ptr + 0];
					green += imgData.pixels[ptr + 1];
					blue += imgData.pixels[ptr + 2];
					mass++;
				}
			}

		}
	}
	intensity.push_back(red / mass);
	intensity.push_back(green / mass);
	intensity.push_back(blue / mass);
	return intensity;
}

std::vector<int> ManagerEdgeFilter::calculateIntensity(std::vector<int> CoordinateUsingFilter, image_data &imgData, int  i, int j) {
	std::vector<int> intensity;
	intensity.push_back(0);
	for (int k = i - 1; k <= i + 1; ++k) {
		if (k >= CoordinateUsingFilter[0] && k < CoordinateUsingFilter[1]) {
			for (int h = j - 1; h <= j + 1; ++h) {
				if (h >= CoordinateUsingFilter[2] && h < CoordinateUsingFilter[3]) {
					int ptr = (k*imgData.w + h)*imgData.compPerPixel;
					if (k == i && h == j) 
						intensity[0] += 9 * imgData.pixels[ptr + 0];
					else
						intensity[0] -= imgData.pixels[ptr + 0];
				}
			}

		}
	}

	if (intensity[0] < 0)
		intensity[0] = 0;
	if (intensity[0] > 255)
		intensity[0] = 255;
	return intensity;
}