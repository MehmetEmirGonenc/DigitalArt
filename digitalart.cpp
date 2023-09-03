#include <iostream>
#include <fstream>
#include <cstdint>
#include <vector>
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
};


int main()
{
    //UI   // Note to me : Add ensuring operations
    //variables
    int WIDTH;
    int HEIGHT;
    std::vector<shape> order;
    shape tempshape;
    std::cout << "Welcome to Digital Art Program!\n";
    std::cout << "Input width of picture that you want to create : ";
    std::cin >> WIDTH;
    std::cout << "Input height of picture that you want to create : ";
    std::cin >> HEIGHT;
    while (true)
    {
        std::cout << "############### Let's begin to create our art #########################\n";
        std::cout << "R -> Eectangle\n";
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
            if (order.size() == 0)
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
            if (tempshape.type == 'R' || tempshape.type == 'r')
            {
                std::cout << "Width :";
                std::cin >>tempshape.width;
                std::cout << "Height :";
                std::cin >>tempshape.height;
            }
            else if (tempshape.type == 'T' || tempshape.type == 't')
            {
                std::cout << "Width :";
                std::cin >>tempshape.width;
            }
            else if (tempshape.type == 'C' || tempshape.type == 'c')
            {
                std::cout << "Radious :";
                std::cin >>tempshape.width;
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

    //Creating blank image
    std::vector<uint8_t> blank_image;
    for (int i = 0; i < WIDTH * HEIGHT * 3; i++)
    {
        blank_image.push_back(255);
    }

    //Calculations
    uint32_t imageSize = sizeof(blank_image);

    dibHeader.ImageSize = imageSize;
    fileHeader.dataOffset = sizeof(fileHeader) + sizeof(dibHeader);
    fileHeader.filesize = fileHeader.dataOffset + imageSize;

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
    outFile.write(reinterpret_cast<char*>(&blank_image), imageSize);

    //Decleration coord postions
    int CENTER[2] = {(WIDTH / 2), (HEIGHT / 2)};
    int AREA1[2] = {(WIDTH * 3 / 4), (HEIGHT * 3 / 4)};
    int AREA2[2] = {(WIDTH / 4), (HEIGHT * 3 / 4)};
    int AREA3[2] = {(WIDTH / 4), (HEIGHT / 4)};
    int AREA4[2] = {(WIDTH * 3 / 4), (HEIGHT / 4)};

    //Modify Image
    //BPM keep pixels left bottom cornet to right top corner
    //Keep RGB order BGR
    //Create a rectangle
    std::vector<pixel> tmpvector = canvas.rectangle(250, 250, 5, 5, 255, 100, 50);
    for (int i = 0; i < tmpvector.size(); i++)
    {
        //Replace
        int pixelplace = tmpvector[i].coord[0] + (tmpvector[i].coord[1] * WIDTH);
        outFile.seekp((fileHeader.dataOffset + pixelplace*3));

        outFile.put(tmpvector[i].RGB[2]);
        outFile.put(tmpvector[i].RGB[1]);
        outFile.put(tmpvector[i].RGB[0]);
    }

    //Close file
    outFile.close();
    
    //TEST AREA(DEBUG)
    //for (int i = 0; i < tmpvector.size(); ++i) {
    //    int values[5] = {tmpvector[i].coord[0],tmpvector[i].coord[1],tmpvector[i].RGB[0],tmpvector[i].RGB[1],tmpvector[i].RGB[2]};
    //    for (int j = 0; j < 5; j++)
    //    {
    //        std::cout<<values[j] << ", ";
    //    }
    //    std::cout<<std::endl;
    //}
    //
    
    std::cout << "Success" << std:: endl;
    
    return 0;
}
