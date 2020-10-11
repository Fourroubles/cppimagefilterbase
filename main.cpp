#include <iostream>
#include <fstream>
#include <cstring>
#include "png_toolkit.h"
#include "WorkFile.h"
#include "Filter.h"


int main(int argc, char *argv[])
{
    try
    {
        if (argc != 4)
            throw "Not enough arguments";

        png_toolkit studTool;
		SelectionFilter start;
		WorkFile data;
		image_data MassPixel;
        studTool.load(argv[2]);
		data.OutPutFile(argv[1]);
		MassPixel = studTool.getPixelData();
		start.Selection(data, MassPixel);
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
