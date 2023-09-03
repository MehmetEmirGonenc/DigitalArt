#ifndef SCRIBE_H
#define SCRIBE_H

#include <iostream>
#include <vector>
#include <cstdint>

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
    std::vector<pixel> rectangle(int origin_coordX, int origin_coordY, int width, int height, int R, int G, int B);
    std::vector<pixel> circle(int origin_coord[2], int radious);

private:
};
#endif