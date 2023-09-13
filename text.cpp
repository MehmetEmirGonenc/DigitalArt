schemes
//
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
        if (reverse == 0)
        {
            reverse = 1;
        }
        else
        {
            reverse = 0;
        }
        radious -= 2;
        tempX -= 3;
    }
    return spiralVector;
    //