#include <iostream>
#include <fstream>
#include <cstdint>
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

int main()
{
    //Create canvas
    scribe canvas;
    //Make blank picture
    BMPFileHeader fileHeader;
    BMPDIBHeader dibHeader;

    //Decleration width and height and implamet
    const int WIDTH = 500;
    const int HEIGHT = 500;

    dibHeader.ImageWidth = static_cast<uint32_t>(WIDTH);
    dibHeader.ImageHeight = static_cast<uint32_t>(HEIGHT);

    //Creating image
    uint8_t image[HEIGHT][WIDTH][3];

    for (int y = 0; y < HEIGHT; y++)
    {
        for ( int x = 0; x < WIDTH; x++)
        {
            image[y][x][0] = 255;
            image[y][x][1] = 255;
            image[y][x][2] = 255;
        }
    }

    //Calculations
    uint32_t imageSize = sizeof(image);

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
    outFile.write(reinterpret_cast<char*>(&image), imageSize);


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
