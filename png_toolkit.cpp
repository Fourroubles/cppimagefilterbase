#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <array>
#include <cstdlib>
#include <iostream>
#include "stb_image_write.h"
#include "png_toolkit.h"

png_toolkit::png_toolkit()
{
}

png_toolkit::~png_toolkit()
{
    stbi_image_free(imgData.pixels);
}

bool png_toolkit::load( const std::string &pictureName )
{
    imgData.pixels = stbi_load(pictureName.c_str(), &imgData.w, &imgData.h, &imgData.compPerPixel, 0);
    return imgData.pixels != nullptr;
}

bool png_toolkit::save( const std::string &pictureName )
{
    return stbi_write_png(pictureName.c_str(),
                   imgData.w, imgData.h,
                   imgData.compPerPixel,
                          imgData.pixels, 0) != 0;
}


image_data png_toolkit::getPixelData( void ) const
{
    return imgData;
}


//void png_toolkit::FilterRed() {
//	int width, height, channels;
//	int desired_no_channels = 3;
//	unsigned char *img = stbi_load("Pytin.jpg", &width, &height, &channels, 0);
//	if (img == NULL) {
//		printf("Error in loading the image\n");
//		exit(1);
//		getchar();
//	}
//	printf("Loaded image with a width of %dpx, a height of %dpx and %d channels\n", width, height, channels);
//	size_t img_size = (width) * (height) * channels;
//	unsigned char *p = img;
//	unsigned char *sepia_img = (unsigned char *)malloc(img_size);
//	for (int i = 0; i < height*width; p += channels, ++i) {
//		if (i>=(0 + 0 * height) && (150 + 100 * height) >= i) {
//			*(p) = (uint8_t)255.0;         // red
//			*(p + 1) = (uint8_t)0.0;
//			*(p + 2) = (uint8_t)0.0;
//		}
//	}
//
//	stbi_write_jpg("lutin.jpg", width, height, channels, img, 100);
//	getchar();
//}