#ifndef SCRIBE_H
#define SCRIBE_H

#include <iostream>
#include <vector>
#include <cstdint>
#include <cmath>

struct pixel
{
    int coord[2]; //Pixel coordinates
    int RGB[3];   //Pixel RGB values
};

class scribe //drowe accourding to coordinates
{
public:
    scribe();
    // These funtions give us an circle coordinate vector
    std::vector<pixel> rectangle(int origin_coordX, int origin_coordY, int width, int height, bool isfilled, int R = 0, int G = 0, int B = 0);
    std::vector<pixel> triangle (int origin_coordX, int origin_coordY, int height, bool isfilled, int R = 0, int G = 0, int B = 0);
    std::vector<pixel> circle(int origin_coordX, int origin_coordY, int radious, bool isfilled, int R = 0, int G = 0, int B = 0);
    std::vector<pixel> spiral(int origin_coordX, int origin_coordY, int radious, bool isfilled, int scale = 2, int R = 0, int G = 0, int B = 0);

    //Color Filters
    std::vector<pixel> Colorizer_Transition(std::vector<pixel> element, int mode = 1, float scale = 1);

private:
};
#endif