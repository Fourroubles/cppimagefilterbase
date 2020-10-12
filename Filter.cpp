#include "Filter.h"

int Filter::ColcualteUpCoordinate(image_data &imgData, const WorkFile ConfigCoordinate) {
	if (ConfigCoordinate.up == 0)
		return 0;
	else
		return imgData.h / ConfigCoordinate.up;
}

int Filter::ColcualteLeftCoordinate(image_data &imgData, const WorkFile ConfigCoordinate) {
	if (ConfigCoordinate.left == 0)
		return 0;
	else
		return imgData.w / ConfigCoordinate.left;
}

int Filter::ColcualteBackCoordinate(image_data &imgData, const WorkFile ConfigCoordinate) {
	if (ConfigCoordinate.back == 0)
		return 0;
	else
		return imgData.h / ConfigCoordinate.back;
}

int Filter::ColcualteRightCoordinate(image_data &imgData, const WorkFile ConfigCoordinate) {
	if (ConfigCoordinate.right == 0)
		return 0;
	else
		return imgData.w / ConfigCoordinate.right;
}

void Filter::ColcualteCoordinate(WorkFile ConfigCoordinate, image_data &imgData, std::vector<int> &CoordinateUsingFilter) {
	CoordinateUsingFilter.push_back(ColcualteUpCoordinate(imgData, ConfigCoordinate));
	CoordinateUsingFilter.push_back(ColcualteBackCoordinate(imgData, ConfigCoordinate));
	CoordinateUsingFilter.push_back(ColcualteLeftCoordinate(imgData, ConfigCoordinate));
	CoordinateUsingFilter.push_back(ColcualteRightCoordinate(imgData, ConfigCoordinate));
}

void RedFilter::RedPainting(image_data &imgData) {
		for (int i = CoordinateUsingFilter[0]; i < CoordinateUsingFilter[1]; ++i) {
			for (int j = CoordinateUsingFilter[2]; j < CoordinateUsingFilter[3]; ++j) {
				int ptr = (i*imgData.w + j)*imgData.compPerPixel;
					imgData.pixels[ptr + 0] = (unsigned char)255;    
					imgData.pixels[ptr + 1] = (unsigned char)0;
					imgData.pixels[ptr + 2] = (unsigned char)0;
			}
		}
}

void BlackWhiteFilter::BlackWhitePainting(image_data &imgData, std::vector<int> CoordinateUsingFilter) {
	for (int i = CoordinateUsingFilter[0]; i < CoordinateUsingFilter[1]; ++i) {
		for (int j = CoordinateUsingFilter[2]; j < CoordinateUsingFilter[3]; ++j) {
			int ptr = (i*imgData.w + j)*imgData.compPerPixel;
			int intensity = (3 * imgData.pixels[ptr + 0] + 6 * imgData.pixels[ptr + 1] + imgData.pixels[ptr + 2]) / 10;
			imgData.pixels[ptr + 0] = (unsigned char)intensity;
			imgData.pixels[ptr + 1] = (unsigned char)intensity;
			imgData.pixels[ptr + 2] = (unsigned char)intensity;
		}
	}
}

int ThresholdFilter::CalculateMediana(std::vector<int> CoordinateUsingFilter, const image_data &imgData, int  i, int j) {
	std::vector<int> intensity;
	for (int k = i - 2; k <= i + 2; ++k) {
		if (k >= CoordinateUsingFilter[0] && k < CoordinateUsingFilter[1]){}
		else
			continue;

		for (int h = j - 2; h <= j + 2; ++h) {
			if (k >= CoordinateUsingFilter[2] && k < CoordinateUsingFilter[3]){}
			else
				continue;

			intensity.push_back(imgData.pixels[(k*imgData.w + h)*imgData.compPerPixel]);

		}
	}

	std::sort(intensity.begin(), intensity.end());
	if (imgData.pixels[(i*imgData.w + j)*imgData.compPerPixel] < intensity[intensity.size() / 2])
		return 0;
	intensity.clear();
	return 1;
}

void ThresholdFilter::ThresholdPainting(image_data &imgData) {
	for (int i = CoordinateUsingFilter[0]; i < CoordinateUsingFilter[1]; ++i) {
		for (int j = CoordinateUsingFilter[2]; j < CoordinateUsingFilter[3]; ++j) {
			if (CalculateMediana(CoordinateUsingFilter, imgData, i, j) == 0) {
				int ptr = (i*imgData.w + j)*imgData.compPerPixel;
				imgData.pixels[ptr + 0] = (unsigned char)0;
				imgData.pixels[ptr + 1] = (unsigned char)0;
				imgData.pixels[ptr + 2] = (unsigned char)0;
			}
		}
	}
}

void SelectionFilter::Selection(WorkFile ConfigData, image_data &imgData) {
	if (ConfigData.FilterName == "Red") {
		RedFilter red;
		Filter &filter = red;
		red.ColcualteCoordinate(ConfigData, imgData, red.CoordinateUsingFilter);
		filter.RedPainting(imgData);
	}
	if (ConfigData.FilterName == "Threshold") {
	
		BlackWhiteFilter BW;
		ThresholdFilter threshold;
		Filter &filter = threshold;
		filter.ColcualteCoordinate(ConfigData, imgData, threshold.CoordinateUsingFilter);
		BW.BlackWhitePainting(imgData, threshold.CoordinateUsingFilter);
		filter.ThresholdPainting(imgData);
	
	}
}