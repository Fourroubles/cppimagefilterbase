#pragma once

#include "png_toolkit.h"
#include "WorkFile.h"

class Filter {
public:
	virtual void RedPainting(image_data &imgData, const WorkFile qq) = 0;
};

class RedFilter : public Filter {
public:
	virtual void RedPainting(image_data &imgData, const WorkFile qq);
};