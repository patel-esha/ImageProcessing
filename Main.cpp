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


// Function to apply subtraction blending tool
Image Subtract(Image &A, Image&B)
{
    Image C;
    Image::Header newHeader = A.AccessHeader();
    C.AdjustHeader(newHeader);

    vector<Pixel> VectorA = A.AccessVector();
    vector<Pixel> VectorB = B.AccessVector();

    for (unsigned int i = 0; i < VectorA.size(); i++)
    {
        VectorA[i].blueInt = (int)((VectorA[i].blue) - '\0');
        VectorA[i].greenInt = (int)((VectorA[i].green) - '\0');
        VectorA[i].redInt = (int)((VectorA[i].red) - '\0');
    }

    for (unsigned int i = 0; i < VectorB.size(); i++)
    {
        VectorB[i].blueInt = (int)((VectorB[i].blue) - '\0');
        VectorB[i].greenInt = (int)((VectorB[i].green) - '\0');
        VectorB[i].redInt = (int)((VectorB[i].red) - '\0');
    }

    vector<Pixel> VectorC;

    for (unsigned int i = 0; i < VectorA.size(); i++)
    {
        Pixel PixelC;

        PixelC.blue = ClampConvert(VectorA[i].blueInt - VectorB[i].blueInt);
        PixelC.green = ClampConvert(VectorA[i].greenInt - VectorB[i].greenInt);
        PixelC.red = ClampConvert(VectorA[i].redInt - VectorB[i].redInt);

        VectorC.push_back(PixelC);

    }
    C.AdjustVector(VectorC);
    return C;
}


// Function to apply screen blending tool

Image Screen(Image &A, Image &B)
{
    Image C;
    Image::Header HeaderA = A.AccessHeader();
    C.AdjustHeader(HeaderA);

    vector<Pixel> VectorA = A.AccessVector();
    vector<Pixel> VectorB = B.AccessVector();

    for (unsigned int i = 0; i < VectorA.size(); i++)
    {
        VectorA[i].blueInt = (int)(VectorA[i].blue - '\0');
        VectorA[i].greenInt = (int)(VectorA[i].green) - '\0';
        VectorA[i].redInt = (int)(VectorA[i].red - '\0');
    }

    for (unsigned int i = 0; i < VectorB.size(); i++)
    {
        VectorB[i].blueInt = (int)(VectorB[i].blue - '\0');
        VectorB[i].greenInt = (int)(VectorB[i].green - '\0');
        VectorB[i].redInt = (int)(VectorB[i].red - '\0');

    }

    vector<Pixel> VectorC;

    for (unsigned int i = 0; i < VectorA.size(); i++)
    {
        Pixel pixelC;

        float blueFloat = (255 - (255 - (float)VectorA[i].blueInt) * (255 - (float)VectorB[i].blueInt) / 255.0f);
        pixelC.blue = ClampConvert(add(blueFloat));

        float greenFloat = (255 - (255 - (float)VectorA[i].greenInt) * (255 - (float)VectorB[i].greenInt) / 255.0f);
        pixelC.green = ClampConvert(add(greenFloat));

        float redFloat = (255 - (255 - (float)VectorA[i].redInt) * (255 - (float)VectorB[i].redInt) / 255.0f);
        pixelC.red = ClampConvert(add(redFloat));

        VectorC.push_back(pixelC);
    }
    C.AdjustVector(VectorC);
    return C;


}





