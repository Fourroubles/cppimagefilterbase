#include "Filter.h"

void RedFilter::RedPainting(image_data &imgData, const WorkFile qq) {
	int x1 = 0 ,x2 = 0 ,y1=0,y2= 0;
	if (qq.u != 0) {
		x1 = imgData.h / qq.u;
	}
	if (qq.b != 0) {
		x2 = imgData.h / qq.b;
	}
	if (qq.l != 0) {
		y1 = imgData.w / qq.l;
	}
	if (qq.r != 0) {
		y2 = imgData.w / qq.r;
	}
		size_t img_size = imgData.w *imgData.h;
		for (int i = x1; i < x2; ++i) {
			for (int j = y1; j < y2; ++j) {
				int ptr = (i*imgData.w + j)*imgData.compPerPixel;
					imgData.pixels[ptr + 0] = (unsigned char)255;         // red
					imgData.pixels[ptr + 1] = (unsigned char)0;
					imgData.pixels[ptr + 2] = (unsigned char)0;
			}
		}
	/*	for (int i = 0; i < imgData.w *imgData.h; p += imgData.compPerPixel, ++i) {
			if(i*imgData.h + imgData.w && i<=x2)
				
		}*/
	
}