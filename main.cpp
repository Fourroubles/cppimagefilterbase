#include <iostream>
#include <fstream>
#include <cstring>
#include "png_toolkit.h"
#include "WorkFile.h"
#include "Filter.h"


int main(int argc, char *argv[])
{
    // toolkit filter_name base_pic_name sudent_tool student_pic_name limitPix limitMSE
    // toolkit near test images!
    try
    {
        if (argc != 4)
            throw "Not enough arguments";

        png_toolkit studTool;
		WorkFile tmp;
		RedFilter red;
		Filter &gg = red;
		image_data ss;
        studTool.load(argv[2]);
		tmp.OutPutFile(argv[1]);
		ss = studTool.getPixelData();
		red.RedPainting(ss, tmp);
        studTool.save(argv[3]);
		
    }
    catch (const char *str)
    {
        std::cout << "Error: " << str << std::endl;
		getchar();
        return 1;
    }
    return 0;
}
