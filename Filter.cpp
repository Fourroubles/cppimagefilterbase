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

void RedFilter::ColcualteCoordinate(WorkFile ConfigCoordinate, image_data &imgData) {
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

void SelectionFilter::Selection(WorkFile ConfigData, image_data &imgData) {
	if (ConfigData.FilterName == "Red") {
		RedFilter red;
		Filter &filter = red;
		red.ColcualteCoordinate(ConfigData, imgData);
		filter.RedPainting(imgData);
	}
}