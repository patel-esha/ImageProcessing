#include "image.h"

using namespace std;


// Members
// Function to read a TGA file and store its data in memory
void Image::ReadImage(string inFile)
{
    ifstream myFile(inFile, ios_base::binary);
    if (myFile.is_open())
    {
        myFile.read(&header.idLength, sizeof(header.idLength));
        myFile.read(&header.colorMapType, sizeof(header.colorMapType));
        myFile.read(&header.dataTypeCode, sizeof(header.dataTypeCode));
        myFile.read((char*)&header.colorMapOrigin, sizeof(header.colorMapOrigin));
        myFile.read((char*)&header.colorMapLength, sizeof(header.colorMapLength));
        myFile.read(&header.colorMapDepth, sizeof(header.colorMapDepth));
        myFile.read((char*)&header.xOrigin, sizeof(header.xOrigin));
        myFile.read((char*)&header.yOrigin, sizeof(header.yOrigin));
        myFile.read((char*)&header.width, sizeof(header.width));
        myFile.read((char*)&header.height, sizeof(header.height));
        myFile.read(&header.bitsPerPixel, sizeof(header.bitsPerPixel));
        myFile.read(&header.imageDescriptor, sizeof(header.imageDescriptor));
    }

    unsigned int totalPixels = header.height * header.width;

    for (int i = 0; i < totalPixels; i++)
    {
        Pixel pixel;

        myFile.read((char*)&pixel.blue, sizeof(pixel.blue));
        myFile.read((char*)&pixel.green, sizeof(pixel.green));
        myFile.read((char*)&pixel.red, sizeof(pixel.red));

        pixelVector.push_back(pixel);
    }
}


// Function to write the TGA data to a new file
void Image::WriteImage(string outFile)
{
    ofstream myFile(outFile, ios_base::binary);
    if (myFile.is_open())
    {
        myFile.write(&header.idLength, sizeof(header.idLength));
        myFile.write(&header.colorMapType, sizeof(header.colorMapType));
        myFile.write(&header.dataTypeCode, sizeof(header.dataTypeCode));
        myFile.write((char*)&header.colorMapOrigin,sizeof(header.colorMapOrigin));
        myFile.write((char*)&header.colorMapLength, sizeof(header.colorMapLength));
        myFile.write(&header.colorMapDepth, sizeof(header.colorMapDepth));
        myFile.write((char*)&header.xOrigin, sizeof(header.xOrigin));
        myFile.write((char*)&header.yOrigin, sizeof(header.yOrigin));
        myFile.write((char*)&header.width, sizeof(header.width));
        myFile.write((char*)&header.height, sizeof(header.height));
        myFile.write(&header.bitsPerPixel, sizeof(header.bitsPerPixel));
        myFile.write(&header.imageDescriptor, sizeof(header.imageDescriptor));
    }


    for (int i = 0; i < pixelVector.size(); i++)
    {
        Pixel pixel = pixelVector.at(i);

        myFile.write((char*)&pixel.blue, 1);
        myFile.write((char*)&pixel.green, 1);
        myFile.write((char*)&pixel.red, 1);

    }

}


// Function to access the header
Image::Header Image::AccessHeader()
{
    return header;
}


vector<Pixel> Image::AccessVector()
{
    return pixelVector;
}


void Image::AdjustVector(vector<Pixel> &vector)
{
    for (unsigned int i = 0; i < vector.size(); i++)
    {
        pixelVector.push_back(vector[i]);
    }
}


void Image::AdjustHeader(Image::Header &HeaderA)
{
    header.idLength = HeaderA.idLength;
    header.colorMapType = HeaderA.colorMapType;
    header.dataTypeCode = HeaderA.dataTypeCode;
    header.colorMapOrigin = HeaderA.colorMapOrigin;
    header.colorMapLength = HeaderA.colorMapLength;
    header.colorMapDepth = HeaderA.colorMapDepth;
    header.xOrigin = HeaderA.xOrigin;
    header.yOrigin = HeaderA.yOrigin;
    header.width = HeaderA.width;
    header.height = HeaderA.height;
    header.bitsPerPixel = HeaderA.bitsPerPixel;
    header.imageDescriptor = HeaderA.imageDescriptor;
}


void Image::AdjustHeaderValues(int height, int width)
{
    header.height = height;
    header.width = width;
}

unsigned int Image::ConvertChar(unsigned char value)
{
    unsigned int newValue = (unsigned int)(value - '\0');
    return newValue;
}
unsigned char Image::ConvertInt(unsigned int value)
{
    unsigned char newValue = (unsigned char)(value + '\0');
    return newValue;
}

void Image::SetValues()
{
    for (unsigned int i = 0; i < pixelVector.size(); i++)
    {
        pixelVector[i].blueInt = ConvertChar(pixelVector[i].blue);
        pixelVector[i].greenInt = ConvertChar(pixelVector[i].green);
        pixelVector[i].redInt = ConvertChar(pixelVector[i].red);
    }
}

