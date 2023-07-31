
#ifndef REDO_IMAGE_H
#define REDO_IMAGE_H
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

// Define the structure for the Pixel
struct Pixel
{
    unsigned char blue;
    unsigned char green;
    unsigned char red;

    int blueInt;
    int greenInt;
    int redInt;

    unsigned int blueUInt;
    unsigned int greenUInt;
    unsigned int redUInt;
};

// Define the structure for the TGA header
class Image
{
public:
    struct Header
    {
        char idLength;
        char colorMapType;
        char dataTypeCode;
        short colorMapOrigin;
        short colorMapLength;
        char colorMapDepth;
        short xOrigin;
        short yOrigin;
        short width;
        short height;
        char bitsPerPixel;
        char imageDescriptor;

    };


    void ReadImage(string inFile);
    void WriteImage(string outFile);

    Header AccessHeader();
    vector<Pixel> AccessVector();
    void AdjustVector(vector<Pixel> &vector);
    void AdjustHeader(Image::Header &HeaderA);

    void AdjustHeaderValues(int height, int width);

    void SetValues();
    unsigned int ConvertChar(unsigned char value);
    unsigned char ConvertInt(unsigned int value);

protected:
    Header header;
    Pixel pixel;
    vector<Pixel> pixelVector;
};


#endif //REDO_IMAGE_H
