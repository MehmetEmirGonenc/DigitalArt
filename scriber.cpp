#include "scriber.h"


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
std::vector<pixel> scribe::triangle (int origin_coordX, int origin_coordY, int height, bool isfilled, int mode,int R, int G, int B)
{  
    ///###Improve it!!!
    std::vector<pixel> triangleVector;
    int n; //For number of pixel for every row
    int tempY; 
    if (mode == 0)
    {
        n = 1;
        tempY = origin_coordY + (height-1)/2;
    }
    else if (mode == 1)
    {
        n = 1;
        tempY = origin_coordY - (height-1)/2;
    }
    for (int i = tempY; i >= (origin_coordY - (height-1)/2);)
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
        if (mode == 0)
        {
            n +=2;
            i--;
        }
        else if (mode == 1)
        {
            n +=2;
            i++;
            if (i > origin_coordY + (height-1)/2)
            {
                break;
            }
        }
    }


    return triangleVector;
}

std::vector<pixel> scribe::circle(int origin_coordX, int origin_coordY, int radious, bool isfilled,int R, int G, int B)
{
    std::vector<pixel> circleVector;
    int r = radious;
    int y = 0;
    int radiusError = 1 - r;

    while (r >= y)
    {
        circleVector.push_back({origin_coordX + r, origin_coordY + y});    //Coord
        circleVector.push_back({R, G, B});                                 //Color
        circleVector.push_back({origin_coordX - r, origin_coordY + y});    //Coord
        circleVector.push_back({R, G, B});                                 //Color
        circleVector.push_back({origin_coordX + r, origin_coordY - y});    //Coord
        circleVector.push_back({R, G, B});                                 //Color
        circleVector.push_back({origin_coordX - r, origin_coordY - y});    //Coord
        circleVector.push_back({R, G, B});                                 //Color
        circleVector.push_back({origin_coordX + y, origin_coordY + r});    //Coord
        circleVector.push_back({R, G, B});                                 //Color
        circleVector.push_back({origin_coordX - y, origin_coordY + r});    //Coord
        circleVector.push_back({R, G, B});                                 //Color
        circleVector.push_back({origin_coordX + y, origin_coordY - r});    //Coord
        circleVector.push_back({R, G, B});                                 //Color
        circleVector.push_back({origin_coordX - y, origin_coordY - r});    //Coord
        circleVector.push_back({R, G, B});                                 //Color

        if (isfilled == 1)
        {
            for (int i = origin_coordY - y; i <= origin_coordY + y; i++)
            {
                for (int j = origin_coordX - r; j <= origin_coordX + r; j++)
                {
                    circleVector.push_back({j,i});
                    circleVector.push_back({R, G, B});
                }
            }
            for (int i = origin_coordY - r; i <= origin_coordY + r; i++)
            {
                for (int j = origin_coordX - y; j <= origin_coordX + y; j++)
                {
                    circleVector.push_back({j,i});
                    circleVector.push_back({R, G, B});
                }
            }
        }
        y++;

        if (radiusError < 0) {
            radiusError += 2 * y + 1;
        } else {
            r--;
            radiusError += 2 * (y - r + 1);
        }
    }
    return circleVector;
}
std::vector<pixel> scribe::spiral(int origin_coordX, int origin_coordY, int radious, bool isfilled, int mode/*for differen combinations*/,int scale, int R, int G, int B)
{
    // 0 -> Normal Spiral
    // 1 -> Reverse Spiral
    // 2 -> Hopper
    // 3 -> Reverse Hopper
    std::vector<pixel> spiralVector;
    int tempX = origin_coordX;
    int tempY = origin_coordY;
    int tempRadi = radious;
    bool reverse = false;
    while (radious > 1)
    {
        std::vector<pixel> partofcircle = scribe::circle(tempX, tempY, radious, isfilled, R, G, B);
        for (int i = 0; i < partofcircle.size(); i++)
        {
            pixel tmp = partofcircle[i];
            if (reverse == 0 && tmp.coord[1] >= tempY)
            {
                spiralVector.push_back(tmp);
            }
            else if (reverse == 1 && tmp.coord[1] <= tempY)
            {
                spiralVector.push_back(tmp);
            }
        }
        radious -= scale;
        if (reverse == 0)
        {
            if (mode == 0)
            {
                tempX -= scale;
            }
            else if (mode == 1)
            {
                tempX -= -scale;
            }
            else if (mode == 2)
            {
                tempX -= (scale + 1);
            }
            else if (mode == 3)
            {
                tempX += (scale + 1);
            }
            reverse = 1;
        }
        else
        {
            if (mode == 0)
            {
                tempX -= -scale;
            }
            else if (mode == 1)
            {
                tempX -= scale;
            }
            else if (mode == 2)
            {
                tempX -= (scale + 1);
            }
            else if (mode == 3)
            {
                tempX += (scale + 1);
            }
            reverse = 0;
        }
    }
    return spiralVector;
}
std::vector<pixel> scribe::butterfly(int origin_coordX, int origin_coordY, int height, bool isfilled, int mode, int R, int G, int B)
{
    std::vector<pixel> butterfly;
    std::vector<pixel> tri1 = triangle(origin_coordX, origin_coordY, height, isfilled, 0);
    std::vector<pixel> tri2 = triangle(origin_coordX, origin_coordY, height, isfilled, 1);
    for (int i = 0; i < tri1.size(); i++)
    {
        butterfly.push_back(tri1[i]);
    }
    for (int i = 0; i < tri2.size(); i++)
    {
        butterfly.push_back(tri2[i]);
    }
    return butterfly;
}

std::vector<pixel> scribe::parallelogram(int origin_coordX, int origin_coordY, int height, bool isfilled, int R, int G, int B)
{
    std::vector<pixel> parallelVector;
    return parallelVector;
}