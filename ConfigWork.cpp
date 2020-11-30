#include "ConfigWork.h"

Filter* configWork::createFilter(nameFilter name) {
	Filter* filter = nullptr;
	switch (name)
	{
	case RED_FILTER:
		filter = new Red();
		break;
	case THRESHOLD_FILTER:
		filter = new Threshold();
		break;
	case BLUR_FILTER:
		filter = new Blur();
		break;
	case EDGE_FILTER:
		filter = new Edge();
		break;
	case BLACK_WHITE_FILTER:
		filter = new BlackWhite();
		break;
	default:
		break;
	}
	return filter;
}

void configWork::detectFilter(std::vector<Data> massData) {
	for (unsigned int i = 0; i < massData.size(); ++i) {
		if (massData[i].FilterName == "Red")
			name.push_back(RED_FILTER);
		if (massData[i].FilterName == "Threshold") {
			name.push_back(BLACK_WHITE_FILTER);
			name.push_back(THRESHOLD_FILTER);
		}
		if (massData[i].FilterName == "Blur")
			name.push_back(BLUR_FILTER);
	/*	if (massData[i].FilterName == "Edge") {
			name.push_back(BLACK_WHITE_FILTER);
			name.push_back(EDGE_FILTER);
		}*/
	}
}

void configWork::filingFilter() {
	for (unsigned int i = 0; i < name.size(); ++i) {
		typeFilter.push_back(configWork::createFilter(name[i]));
	}
}

void configWork::usingFilter(std::vector<Data> MassData, image_data &imgData) {
	for (unsigned int i = 0, j = 0; i < typeFilter.size(); ++i) {
		j = i;
		if (name[i - 1] == BLACK_WHITE_FILTER && i!=0)
			j -= 1;
		typeFilter[i]->filter(imgData, ColcualteCoordinate(MassData[j], imgData));
	}
}

int configWork::ColcualteUpCoordinate(image_data &imgData, Data ConfigCoordinate) {
	return ConfigCoordinate.up != 0 ? imgData.h / ConfigCoordinate.up : 0;
}

int configWork::ColcualteLeftCoordinate(image_data &imgData, Data ConfigCoordinate) {
	return ConfigCoordinate.left != 0 ? imgData.w / ConfigCoordinate.left : 0;
}

int configWork::ColcualteBackCoordinate(image_data &imgData, Data ConfigCoordinate) {
	return ConfigCoordinate.back != 0 ? imgData.h / ConfigCoordinate.back : 0;
}

int configWork::ColcualteRightCoordinate(image_data &imgData, Data ConfigCoordinate) {
	return ConfigCoordinate.right != 0 ? imgData.w / ConfigCoordinate.right : 0;
}

std::vector<int> configWork::ColcualteCoordinate(Data ConfigCoordinate, image_data &imgData) {
	std::vector<int> CoordinateUsingFilter;
	CoordinateUsingFilter.push_back(ColcualteUpCoordinate(imgData, ConfigCoordinate));
	CoordinateUsingFilter.push_back(ColcualteBackCoordinate(imgData, ConfigCoordinate));
	CoordinateUsingFilter.push_back(ColcualteLeftCoordinate(imgData, ConfigCoordinate));
	CoordinateUsingFilter.push_back(ColcualteRightCoordinate(imgData, ConfigCoordinate));
	return CoordinateUsingFilter;
}

