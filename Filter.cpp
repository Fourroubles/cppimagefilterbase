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
			imgData.pixels[ptr + 0] = imgData.pixels[ptr + 1] = imgData.pixels[ptr + 2] = (unsigned char)intensity;
		}
	}
}

std::vector<int> ThresholdFilter::Filling—ontainerIntensity(std::vector<int> CoordinateUsingFilter, const image_data &imgData, int  i, int j) {
	std::vector<int> intensity;
	for (int k = i - 2; k <= i + 2; ++k) {
		if (k >= CoordinateUsingFilter[0] && k <= CoordinateUsingFilter[1]) {
			for (int h = j - 2; h <= j + 2; ++h) {
				if (k >= CoordinateUsingFilter[2] && k <= CoordinateUsingFilter[3]) {
					intensity.push_back(imgData.pixels[(k*imgData.w + h)*imgData.compPerPixel]);
				}
			}
		}
	}
	return intensity;
}

bool ThresholdFilter::CalculateMediana(std::vector<int> CoordinateUsingFilter, const image_data &imgData, int  i, int j) {
	std::vector<int> intensity = Filling—ontainerIntensity(CoordinateUsingFilter, imgData, i, j);
	std::sort(intensity.begin(), intensity.end());
	if (imgData.pixels[(i*imgData.w + j)*imgData.compPerPixel] < intensity[intensity.size() / 2])
		return false;
	return true;
}

void ThresholdFilter::ChangePixel(image_data &imgData, std::vector<int> CoordinateUsingFilter) {
	image_data CopyPixel;
	CopyPixel = imgData;
	CopyPixel.h = imgData.h;
	CopyPixel.compPerPixel = imgData.compPerPixel;
	CopyPixel.w = imgData.w;
	CopyPixel.pixels = new stbi_uc[imgData.w*imgData.h*imgData.compPerPixel];
	memcpy(CopyPixel.pixels, imgData.pixels, CopyPixel.w*CopyPixel.h*CopyPixel.compPerPixel);
	for (int i = CoordinateUsingFilter[0]; i < CoordinateUsingFilter[1]; ++i) {
		for (int j = CoordinateUsingFilter[2]; j < CoordinateUsingFilter[3]; ++j) {
			if (CalculateMediana(CoordinateUsingFilter, CopyPixel, i, j) == false) {
				int ptr = (i*imgData.w + j)*imgData.compPerPixel;
				imgData.pixels[ptr + 0] = imgData.pixels[ptr + 1] = imgData.pixels[ptr + 2] = (unsigned char)0;
			}
		}
	}
	delete[] CopyPixel.pixels;
}

void ThresholdFilter::ThresholdPainting(WorkFile ConfigData, image_data &imgData) {
	BlackWhiteFilter BW;
	Filter filter;
	filter.ColcualteCoordinate(ConfigData, imgData, CoordinateUsingFilter);
	BW.BlackWhitePainting(imgData, CoordinateUsingFilter);
	ChangePixel(imgData, CoordinateUsingFilter);
}

void SelectionFilter::Selection(WorkFile ConfigData, image_data &imgData) {
	if (ConfigData.FilterName == "Red") {
		RedFilter red;
		/*Filter &filter = red;*/
		red.ColcualteCoordinate(ConfigData, imgData, red.CoordinateUsingFilter);
		red.RedPainting(imgData);
	}
	/*else  {
		ThresholdFilter threshold;
		Filter &filter = threshold;;
		filter.ThresholdPainting(ConfigData, imgData);
	}*/
}