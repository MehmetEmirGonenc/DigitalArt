#include "scriber.h"

std::vector<pixel> scribe::circle(int origin_coord[2], int radious)
{
    std::vector<pixel> circleVector;


    return circleVector;
}
scribe::scribe()
{
}
std::vector<pixel> scribe::rectangle(int origin_coordX, int origin_coordY, int width, int height, int R, int G, int B)
{
    std::vector<pixel> rectangleVector;
    // We need to seperate odd and even numbers because
    /* 0-> null, #-> line, X->Origin
       Odd                Even
    00000000          0000000000   
    0#####00          000####000
    0#0X0#00          000#00#000
    0#####00          000####000
    00000000          0000000000
    Notice: We have a certain origin for odd numbers but we have no certain origin for evens.
    So we will seperate them.
    */
    if (width%2 != 0 && height%2 != 0)
    {
        //if all odd
        int tempY = origin_coordY - ((height - 1)/2);
        for (int i = 0; i < height; i++, tempY++)
        {
            int tempX = origin_coordX - ((width - 1)/2);
            for (int j = 0; j < width; j++, tempX++)
            {
                pixel temppix;
                temppix.coord[0] = tempX;
                temppix.coord[1] = tempY;
                temppix.RGB[0] = R;
                temppix.RGB[1] = G;
                temppix.RGB[2] = B;
                rectangleVector.push_back(temppix);
            }
        }
    }
    
    else
    {

    }
    return rectangleVector;
}
