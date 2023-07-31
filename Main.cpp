#include "image.h"
// Function to apply multiplication blending tool
Image Multiply(Image &A, Image &B)
{
    Image C;
    Image::Header HeaderA = A.AccessHeader();
    C.AdjustHeader(HeaderA);

    vector<Pixel> VectorA = A.AccessVector();
    vector<Pixel> VectorB = B.AccessVector();

    for (unsigned int i = 0; i < VectorA.size(); i++)
    {
        VectorA[i].blueUInt = (unsigned int)(VectorA[i].blue - '\0');
        VectorA[i].greenUInt = (unsigned int)(VectorA[i].green - '\0');
        VectorA[i].redUInt = (unsigned int)(VectorA[i].red - '\0');
    }

    for (unsigned int i = 0; i < VectorB.size(); i++)
    {
        VectorB[i].blueUInt = (unsigned int)(VectorB[i].blue - '\0');
        VectorB[i].greenUInt = (unsigned int)(VectorB[i].green - '\0');
        VectorB[i].redUInt = (unsigned int)(VectorB[i].red - '\0');

    }

    vector<Pixel> VectorC;

    for (unsigned int i = 0; i < VectorA.size(); i++)
    {
        Pixel pixelC;

        unsigned int blue = (unsigned int)add(VectorA[i].blueUInt * VectorB[i].blueUInt / 255.0f);
        pixelC.blue = (unsigned char)(blue + '\0');

        unsigned int green = (unsigned int)add(VectorA[i].greenUInt * VectorB[i].greenUInt / 255.0f);
        pixelC.green = (unsigned char)(green + '\0');

        unsigned int red = (unsigned int)add(VectorA[i].redUInt * VectorB[i].redUInt / 255.0f);
        pixelC.red = (unsigned char)(red + '\0');

        VectorC.push_back(pixelC);
    }
    C.AdjustVector(VectorC);
    return C;


}

