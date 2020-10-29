#include "Filter.h"

int Filter::ColcualteUpCoordinate(image_data &imgData, Data ConfigCoordinate) {
	if (ConfigCoordinate.up == 0)
		return 0;
	else
		return imgData.h / ConfigCoordinate.up;
}

int Filter::ColcualteLeftCoordinate(image_data &imgData, Data ConfigCoordinate) {
	if (ConfigCoordinate.left == 0)
		return 0;
	else
		return imgData.w / ConfigCoordinate.left;
}

int Filter::ColcualteBackCoordinate(image_data &imgData, Data ConfigCoordinate) {
	if (ConfigCoordinate.back == 0)
		return 0;
	else
		return imgData.h / ConfigCoordinate.back;
}

int Filter::ColcualteRightCoordinate(image_data &imgData, Data ConfigCoordinate) {
	if (ConfigCoordinate.right == 0)
		return 0;
	else
		return imgData.w / ConfigCoordinate.right;
}

void Filter::ColcualteCoordinate(Data ConfigCoordinate, image_data &imgData, std::vector<int> &CoordinateUsingFilter) {
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
			int r = imgData.pixels[ptr + 0];
			int g = imgData.pixels[ptr + 1];
			int b = imgData.pixels[ptr + 2];
			int intensity = (3 * r + 6 * g + 1*b) / 10;
			imgData.pixels[ptr + 0] = (unsigned char)intensity;
			imgData.pixels[ptr + 1] = (unsigned char)intensity;
			imgData.pixels[ptr + 2] = (unsigned char)intensity;
		}
	}
}

std::vector<int> ThresholdFilter::FillingqontainerIntensity(std::vector<int> CoordinateUsingFilter, const image_data &imgData, int  i, int j) {
	std::vector<int> intensity;
	for (int k = i - 2; k <= i + 2; ++k) {
		if (k >= CoordinateUsingFilter[0] && k < CoordinateUsingFilter[1]) {
			for (int h = j - 2; h <= j + 2; ++h) {
				if (h >= CoordinateUsingFilter[2] && h < CoordinateUsingFilter[3]) {
					intensity.push_back(imgData.pixels[(k*imgData.w + h)*imgData.compPerPixel]);
				}
			}
		}
	}
	return intensity;
}

bool ThresholdFilter::CalculateMediana(std::vector<int> CoordinateUsingFilter, const image_data &imgData, int  i, int j) {
	std::vector<int> intensity = FillingqontainerIntensity(CoordinateUsingFilter, imgData, i, j);
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
	int tmp = imgData.w*imgData.h*imgData.compPerPixel;
	CopyPixel.pixels = new stbi_uc[tmp];
	for (int i = 0; i < tmp; i++) {
		CopyPixel.pixels[i] = imgData.pixels[i];
	}
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

void ThresholdFilter::ThresholdPainting(Data ConfigData, image_data &imgData) {
	BlackWhiteFilter BW;
	Filter filter;
	filter.ColcualteCoordinate(ConfigData, imgData, CoordinateUsingFilter);
	BW.BlackWhitePainting(imgData, CoordinateUsingFilter);
	ChangePixel(imgData, CoordinateUsingFilter);
}

std::vector<int> BlurFilter::qonvolutionqount(std::vector<int> CoordinateUsingFilter, const image_data &imgData, int  i, int j) {
	std::vector<int> intensity;
	int r = 0, g = 0, b = 0;
	for (int k = i - 1; k <= i + 1; ++k) {
		if (k >= CoordinateUsingFilter[0] && k < CoordinateUsingFilter[1]) {
			for (int h = j - 1; h <= j + 1; ++h) {
				if (h >= CoordinateUsingFilter[2] && h < CoordinateUsingFilter[3]) {
					int ptr = (k*imgData.w + h)*imgData.compPerPixel;
					r += imgData.pixels[ptr + 0];
					g += imgData.pixels[ptr + 1];
					b += imgData.pixels[ptr + 2];
				}
			}
		}
	}
	intensity.push_back(r / 9);
	intensity.push_back(g / 9);
	intensity.push_back(b / 9);
	return intensity;
}

void BlurFilter::BlurPainting(Data ConfigData, image_data &imgData) {
	Filter filter;
	filter.ColcualteCoordinate(ConfigData, imgData, CoordinateUsingFilter);

	std::vector<int> ptq;
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
	for (int i = CoordinateUsingFilter[0]; i < CoordinateUsingFilter[1]; ++i) {
		for (int j = CoordinateUsingFilter[2]; j < CoordinateUsingFilter[3]; ++j) {
			ptq = qonvolutionqount(CoordinateUsingFilter, CopyPixel, i, j);
				int ptr = (i*imgData.w + j)*imgData.compPerPixel;
				imgData.pixels[ptr + 0] = ptq[0];
				imgData.pixels[ptr + 1] = ptq[1];
				imgData.pixels[ptr + 2] = ptq[2];;
		}
	}
	delete[] CopyPixel.pixels;

}

void SelectionFilter::Selection(WorkFile ConfigData, image_data &imgData) {
	for (auto tmp : ConfigData.MassData) {
		if (tmp.FilterName == "Red") {
			RedFilter red;
			Filter filter = red;
			filter.ColcualteCoordinate(tmp, imgData, red.CoordinateUsingFilter);
			red.RedPainting(imgData);
		}
		if(tmp.FilterName == "Threshold"){
			ThresholdFilter threshold;
			threshold.ThresholdPainting(tmp, imgData);
		}
		if (tmp.FilterName == "Blur") {
			BlurFilter blur;
			blur.BlurPainting(tmp, imgData);
		}
	}
}