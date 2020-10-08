#include "Filter.h"

void RedFilter::RedPainting(image_data &imgData, const WorkFile qq) {
	int x1 = 0,x2 = imgData.w,y1= 0,y2= imgData.h;
	if (qq.u != 0) {
		x1 = imgData.w / qq.u;
	}
	if (qq.b != 0) {
		x2 = imgData.w / qq.b;
	}
	if (qq.l != 0) {
		y1 = imgData.h / qq.l;
	}
	if (qq.r != 0) {
		y2 = imgData.h / qq.r;
	}
		size_t img_size = imgData.w *imgData.h;
		unsigned char *p = imgData.pixels;
		for (int i = 0; i < imgData.h; ++i) {
			for (int j = 0; j < imgData.w; ++j) {
				if (i >= y1 && i <= y2 && j >= x1 && j <= x2) {
					*(p) = (uint8_t)255;         // red
					*(p + 1) = (uint8_t)0;
					*(p + 2) = (uint8_t)0;
				}
				
				p += imgData.compPerPixel;
			}
		}
	/*	for (int i = 0; i < imgData.w *imgData.h; p += imgData.compPerPixel, ++i) {
			if(i*imgData.h + imgData.w && i<=x2)
				
		}*/
	
}