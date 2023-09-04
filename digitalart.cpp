#include <iostream>
#include <fstream>
#include <cstdint>
#include <vector>
#include <cmath>
#include <cstring>
#include "scriber.h"

#pragma pack(1) // Disable structure padding

//Define structures
struct BMPFileHeader
{
    char signature[2] = {'B', 'M'};
    uint32_t filesize; //Calculate
    uint16_t reserved1 = 0;
    uint16_t reserved2 = 0;
    uint32_t dataOffset; // Calculate
};
struct BMPDIBHeader
{
    uint32_t DIBHeaderSize = 40;
    uint32_t ImageWidth;    
    uint32_t ImageHeight;
    uint16_t NumberOfColorPlanes = 1;
    uint16_t BitsPerPixel = 24;
    uint32_t CompressionMethod = 0;
    uint32_t ImageSize; //Calculate
    uint32_t HorizontalResolution = 0;
    uint32_t VerticalResolution = 0;
    uint32_t NumberOfColorsInPallette = 0;
    uint32_t NumberOfImportantColors = 0;
};
struct shape
{
    char type;
    int width;//Also can be radius
    int height;
    char position;
    bool isfilled;
};


int main(int argc, char* argv[])
{
    //UI   // Note to me : Add ensuring operations
    //variables
    int WIDTH;
    int HEIGHT;
    std::vector<shape> order;
    //Developer fast test area
    if (!strcmp(argv[1],"-t"))
    {
        WIDTH = 500;
        HEIGHT= 500;
        shape tempshape;
        tempshape.type = 'r';
        tempshape.isfilled = 1;
        tempshape.width = 101;
        tempshape.width = 101;
        tempshape.position = 'c';
        order.push_back(tempshape);
    }
    //
    else
    { 
        std::cout << "Welcome to Digital Art Program!\n";
        std::cout << "Input width of picture that you want to create : ";
        std::cin >> WIDTH;
        std::cout << "Input height of picture that you want to create : ";
        std::cin >> HEIGHT;
        while (true)
        {
            shape tempshape;
            std::cout << "############### Let's begin to create our art #########################\n";
            std::cout << "R -> Rectangle\n";
            std::cout << "T -> Triangle\n";
            std::cout << "C -> Circle\n";
            std::cout << "P -> Process\n";
            std::cout << "E -> Exit\n";
            std::cout << "-->";
            std::cin >> tempshape.type;
            if (tempshape.type == 'E' || tempshape.type == 'e')
            {
                return 2;
            }
            else if (tempshape.type == 'P' || tempshape.type == 'p')
            {
                if (order.empty())
                {
                    std::cout << "Eroor: Order is null!\n";
                    return 3;
                }
                break;
            }
            else
            {
                std::cout << "---Set Position--- \n";
                std::cout << "C -> Center \n";
                std::cout << "1 -> Area 1\n";
                std::cout << "2 -> Area 2\n";
                std::cout << "3 -> Area 3\n";
                std::cout << "4 -> Area 4\n";
                std::cout << "-->";
                std::cin >> tempshape.position;
                std::cout << "0->Not filled\n";
                std::cout << "1->Filled\n";
                std::cout << "-->";
                std::cin >> tempshape.isfilled;
                if (tempshape.type == 'R' || tempshape.type == 'r')
                {
                    std::cout << "Width :";
                    std::cin >>tempshape.width;
                    std::cout << "Height :";
                    std::cin >>tempshape.height;
                }
                else if (tempshape.type == 'T' || tempshape.type == 't')
                {
                    std::cout << "Height :";
                    std::cin >>tempshape.height;
                    tempshape.width = 0; // Not important we don't use it
                }
                else if (tempshape.type == 'C' || tempshape.type == 'c')
                {
                    std::cout << "Radious :";
                    std::cin >>tempshape.width;
                    tempshape.height; // Not important we don't use it
                }
                order.push_back(tempshape);
            } 
        }
    }
    //Create canvas
    scribe canvas;
    //Make blank picture
    BMPFileHeader fileHeader;
    BMPDIBHeader dibHeader;

    //Decleration width and height and implamet

    dibHeader.ImageWidth = static_cast<uint32_t>(WIDTH);
    dibHeader.ImageHeight = static_cast<uint32_t>(HEIGHT);

    //Calculations
    uint32_t imageSize = WIDTH * HEIGHT * 3;

    dibHeader.ImageSize = imageSize;
    fileHeader.dataOffset = sizeof(fileHeader) + sizeof(dibHeader);
    fileHeader.filesize = fileHeader.dataOffset + imageSize;

    
    //Creating blank image
    std::vector<uint8_t> blank_image(imageSize, 255);

    //Create file
    std::ofstream outFile("image.bmp", std::ios::binary);

    //Ensureing is open
    if (!outFile)
    {
        std::cout << "File could not be create" << std::endl;
        return 1;
    }

    //Write Bmp file

    outFile.write(reinterpret_cast<char*>(&fileHeader), sizeof(fileHeader));
    outFile.write(reinterpret_cast<char*>(&dibHeader), sizeof(dibHeader));
    outFile.write(reinterpret_cast<char*>(blank_image.data()), imageSize);

    //Modify Image
    //BPM keep pixels left bottom cornet to right top corner
    //Keep RGB order BGR
    for (int i = 0; i < order.size(); i++)
    {
        //Decleration coord postions
        int positionX = 0, positionY = 0;
        switch (order[i].position)
        {
        case 'C':
        case 'c':
            positionX = std::round(WIDTH / 2);
            positionY = std::round(HEIGHT / 2);
            break;
        case '1':
            positionX = std::round(WIDTH * 3 / 4);
            positionY = std::round(HEIGHT * 3 / 4);
            break;
        case '2':
            positionX = std::round(WIDTH / 4);
            positionY = std::round(HEIGHT * 3 / 4);
            break;
        case '3':
            positionX = std::round(WIDTH / 4);
            positionY = std::round(HEIGHT / 4);
            break;
        case '4':
            positionX = std::round(WIDTH * 3 / 4);
            positionY = std::round(HEIGHT / 4);
            break;
        default:
            break;
        }
        std::cout << positionX<<" , "<<positionY <<"\n";
        std::vector<pixel> tmpvector;
        if (order[i].type == 'R' || order[i].type == 'r')
        {
            tmpvector = canvas.Colorizer_Transition(canvas.rectangle(positionX, positionY, order[i].width, order[i].height, order[i].isfilled),2 , 0.3f );
        }
        else if (order[i].type == 'T' || order[i].type == 't')
        {
            tmpvector = canvas.Colorizer_Transition(canvas.triangle(positionX, positionY, order[i].height, order[i].isfilled),1);
        }
        
        for (int i = 0; i < tmpvector.size(); i++)
        {
            //Replace
            int pixelplace = tmpvector[i].coord[0] + (tmpvector[i].coord[1] * WIDTH);
            outFile.seekp((fileHeader.dataOffset + pixelplace*3));

            outFile.put(tmpvector[i].RGB[2]);
            outFile.put(tmpvector[i].RGB[1]);
            outFile.put(tmpvector[i].RGB[0]);
        }
    }
    //Close file
    outFile.close();
    
    std::cout << "Success" << std:: endl;
    
    return 0;
}
