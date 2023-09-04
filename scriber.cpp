#include "scriber.h"

std::vector<pixel> scribe::circle(int origin_coord[2], int radious)
{
    std::vector<pixel> circleVector;


    return circleVector;
}

std::vector<pixel> scribe::Colorizer_Transition(std::vector<pixel> element, int mode,float scale)
{
    int finder_counter = element[0].coord[1];
    float j = 0;
    for (size_t i = 0; i < element.size(); i++, j+= scale)
    {
        if (mode == 2)
        {
            if (element[i].coord[1] == finder_counter)
            {
            std::cout<< element[i].coord[1]<<"\n";
            j = 0;
            finder_counter++;
            }
        }

        element[i].RGB[0] = static_cast<int>(std::round(j*8))%255;
        element[i].RGB[1] = std::round((0)%255);
        element[i].RGB[2] = std::round((0)%255);
        
    }
    return element;
}

scribe::scribe()
{
}
//Shapes
std::vector<pixel> scribe::rectangle(int origin_coordX, int origin_coordY, int width, int height, bool isfilled, int R, int G, int B)
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
        int edgeX1 = origin_coordX - ((height - 1)/2);
        int edgeX2 = origin_coordX + ((height - 1)/2);
        int edgeY1 = origin_coordY + ((width - 1)/2);
        int edgeY2 = origin_coordY - ((width - 1)/2);
        int tempY = origin_coordY - ((height - 1)/2);
        for (int i = 0; i < height; i++, tempY++)
        {
            int tempX = origin_coordX - ((width - 1)/2);
            for (int j = 0; j < width; j++, tempX++)
            {
                if (isfilled == 0)
                {
                    if (tempY == edgeY1 || tempY == edgeY2 || tempX == edgeX1 || tempX == edgeX2)
                    {
                    }
                    else
                    {
                        continue;
                    }
                }
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
std::vector<pixel> scribe::triangle (int origin_coordX, int origin_coordY, int height, bool isfilled, int R, int G, int B)
{
    std::vector<pixel> triangleVector;
    //if odd
    if (height%2 != 0)
    {
        int tempY = origin_coordY + (height-1)/2;
        int n = 1; //For number of pixel for every row
        for (int i = tempY; i >= (origin_coordY - (height-1)/2); i--, n+=2)
        {
            int tempX = origin_coordX - ((n-1)/2);
            for (int j = n; j > 0; j--, tempX++)
            {
                pixel temppix;
                temppix.coord[0] = tempX;
                temppix.coord[1] = i;
                temppix.RGB[0] = R;
                temppix.RGB[1] = G;
                temppix.RGB[2] = B;
                triangleVector.push_back(temppix);
            }
        }
    }
    else
    {

    }
    return triangleVector;
}
