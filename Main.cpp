#include "image.h"

float add(float value)
{
    value += 0.5f;
    return value;
}


// Function to clamp values to prevent over/under flow
unsigned char ClampConvert(int value)
{
    unsigned int newValue;

    if (value < 0)
    {
        newValue = 0;
    }
    else if (value > 255)
    {
        newValue = 255;
    }
    else
    {
        newValue = value;
    }

    unsigned char newChar = (unsigned char)(newValue + '\0');

    return newChar;

}


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


// Function to apply the Overlay blending mode on two TGA images
// B<= 0.5; C = 2 * A * B
// B > 0.5; C = 1 - 2 * (1 - A) * (1 - B)

Image Overlay(Image &A, Image &B)
{
    Image C;
    Image::Header HeaderA = A.AccessHeader();
    C.AdjustHeader(HeaderA);

    vector<Pixel> VectorA = A.AccessVector();
    vector<Pixel> VectorB = B.AccessVector();

    for (unsigned int i = 0; i < VectorA.size(); i++)
    {
        VectorA[i].blueInt = (int)(VectorA[i].blue);
        VectorA[i].greenInt = (int)(VectorA[i].green);
        VectorA[i].redInt = (int)(VectorA[i].red);
    }

    for (unsigned int i = 0; i < VectorB.size(); i++)
    {
        VectorB[i].blueInt = (int)(VectorB[i].blue);
        VectorB[i].greenInt = (int)(VectorB[i].green);
        VectorB[i].redInt = (int)(VectorB[i].red);

    }

    vector<Pixel> VectorC;

    for (unsigned int i = 0; i < VectorA.size(); i++)
    {
        Pixel pixelC;

        if (VectorA[i].blueInt <= 127)
        {
            pixelC.blue = ClampConvert(2 * VectorA[i].blueInt * VectorB[i].blueInt / 255.0f);
        }
        else if (VectorA[i].blueInt > 127)
        {
            pixelC.blue = ClampConvert(255 - 2 * (255 - VectorA[i].blueInt) * (255 - VectorB[i].blueInt) / 255.0f);
        }

        if (VectorA[i].greenInt <= 127)
        {
            pixelC.green = ClampConvert(2 * VectorA[i].greenInt * VectorB[i].greenInt / 255.0f);
        }
        else if (VectorA[i].greenInt > 127)
        {
            pixelC.green = ClampConvert(255 - 2 * (255 - VectorA[i].greenInt) * (255 - VectorB[i].greenInt) / 255.0f);
        }

        if (VectorA[i].redInt <= 127)
        {
            pixelC.red = ClampConvert(2 * VectorA[i].redInt * VectorB[i].redInt / 255.0f);
        }
        else if (VectorA[i].redInt > 127)
        {
            pixelC.red = ClampConvert(255 - 2 * (255 - VectorA[i].redInt) * (255 - VectorB[i].redInt) / 255.0f);
        }

        VectorC.push_back(pixelC);
    }
    C.AdjustVector(VectorC);
    return C;


}


// Function to add a value to a specific color channel of a TGA image

// Function to add 200 to the green channel of an image
Image AddColor(Image &A, int blueChannel, int greenChannel, int redChannel)
{
    Image B;
    Image::Header newHeader = A.AccessHeader();
    B.AdjustHeader(newHeader);

    vector<Pixel> VectorA = A.AccessVector();

    for (unsigned int i = 0; i < VectorA.size(); i++)
    {
        VectorA[i].blueInt = (int)((VectorA[i].blue) - '\0');
        VectorA[i].greenInt = (int)((VectorA[i].green) - '\0');
        VectorA[i].redInt = (int)((VectorA[i].red) - '\0');
    }

    vector<Pixel> VectorB;

    for (unsigned int i = 0; i < VectorA.size(); i++)
    {
        Pixel PixelB;

        PixelB.blue = VectorA[i].blue;
        PixelB.green = ClampConvert(VectorA[i].greenInt + greenChannel);
        PixelB.red = VectorA[i].red;

        VectorB.push_back(PixelB);

    }
    B.AdjustVector(VectorB);
    return B;
}


// Function to multiply a channel by a value
Image MultiplyColor(Image &A, int blueChannel, int greenChannel, int redChannel)
{
    Image B;
    Image::Header newHeader = A.AccessHeader();
    B.AdjustHeader(newHeader);

    vector<Pixel> VectorA = A.AccessVector();

    for (unsigned int i = 0; i < VectorA.size(); i++)
    {
        VectorA[i].blueInt = (int)((VectorA[i].blue) - '\0');
        VectorA[i].greenInt = (int)((VectorA[i].green) - '\0');
        VectorA[i].redInt = (int)((VectorA[i].red) - '\0');
    }

    vector<Pixel> VectorB;

    for (unsigned int i = 0; i < VectorA.size(); i++)
    {
        Pixel PixelB;

        PixelB.blue = ClampConvert(VectorA[i].blueInt * blueChannel);
        PixelB.green = ClampConvert(VectorA[i].greenInt * greenChannel);
        PixelB.red = ClampConvert(VectorA[i].redInt * redChannel);

        VectorB.push_back(PixelB);

    }
    B.AdjustVector(VectorB);
    return B;
}


// Function to write each channel to separate files
Image SeparateByChannel(int AsciiInt, Image &A)
{
    Image B;
    Image::Header newHeader = A.AccessHeader();
    B.AdjustHeader(newHeader);


    vector<Pixel> VectorA = A.AccessVector();

    for (unsigned int i = 0; i < VectorA.size(); i++)
    {
        VectorA[i].blueUInt = (unsigned int)((VectorA[i].blue) - '\0');
        VectorA[i].greenUInt = (unsigned int)((VectorA[i].green) - '\0');
        VectorA[i].redUInt = (unsigned int)((VectorA[i].red) - '\0');
    }

    vector<Pixel> VectorB;

    for (unsigned int i = 0; i < VectorA.size(); i++)
    {
        Pixel PixelB;

        if (AsciiInt == 66) // ASCII value for B representing the BlueChannel
        {
            PixelB.blue = VectorA[i].blue;
            PixelB.green = VectorA[i].blue;
            PixelB.red = VectorA[i].blue;
        }

        else if (AsciiInt == 71) // ASCII value for G representing the GreenChannel
        {
            PixelB.blue = VectorA[i].green;
            PixelB.green = VectorA[i].green;
            PixelB.red = VectorA[i].green;
        }

        else if (AsciiInt == 82) // ASCII value for R representing the RedChannel
        {
            PixelB.blue = VectorA[i].red;
            PixelB.green = VectorA[i].red;
            PixelB.red = VectorA[i].red;
        }
        VectorB.push_back(PixelB);
    }
    B.AdjustVector(VectorB);
    return B;
}


// Function to combine the channels from different TGA images
Image CombineByChannel(Image &B, Image &G, Image &R)
{
    Image A;
    Image::Header newHeader = B.AccessHeader();
    A.AdjustHeader(newHeader);


    vector<Pixel> VectorB = B.AccessVector();
    vector<Pixel> VectorG = G.AccessVector();
    vector<Pixel> VectorR = R.AccessVector();

    vector<Pixel> CopyVector;

    for (unsigned int i = 0; i < VectorB.size(); i++)
    {
        VectorB[i].blueUInt = (unsigned int)((VectorB[i].blue) - '\0');
        VectorG[i].greenUInt = (unsigned int)((VectorG[i].green) - '\0');
        VectorR[i].redUInt = (unsigned int)((VectorR[i].red) - '\0');
    }

    vector<Pixel> VectorA;

    for (unsigned int i = 0; i < VectorB.size(); i++)
    {
        Pixel PixelA;

        PixelA.blue = VectorB[i].blueUInt;
        PixelA.green = VectorG[i].greenUInt;
        PixelA.red = VectorR[i].redUInt;

        VectorA.push_back(PixelA);
    }
    A.AdjustVector(VectorA);
    return A;
}


// Function to rotate a TGA image 180 degrees
Image Rotate(Image &A)
{
    Image B;
    Image::Header newHeader = A.AccessHeader();
    B.AdjustHeader(newHeader);

    vector<Pixel> VectorA = A.AccessVector();
    vector<Pixel> VectorB;

    int Pixels = newHeader.height * newHeader.width;

    for (int i = Pixels - 1; i >= 0; i--)
    {
        Pixel PixelB;

        PixelB.blue = (VectorA[i].blue);
        PixelB.green = (VectorA[i].green);
        PixelB.red = (VectorA[i].red);

        VectorB.push_back(PixelB);

    }
    B.AdjustVector(VectorB);
    return B;
}


Image CombineQuadrants(Image &A, Image &B, Image &C, Image &D)
{
    Image::Header newHeader = A.AccessHeader();
    short halfHeight = A.AccessHeader().height;
    short halfWidth = A.AccessHeader().width;
    short totalHeight = halfHeight * 2;
    short totalWidth = halfWidth * 2;

    Image newImage;
    newImage.AdjustHeader(newHeader);
    newImage.AdjustHeaderValues(totalHeight, totalWidth);

    vector<Pixel> VectorA = A.AccessVector();
    vector<Pixel> VectorB = B.AccessVector();
    vector<Pixel> VectorC = C.AccessVector();
    vector<Pixel> VectorD = D.AccessVector();
    vector<Pixel> newVector;



    for (unsigned int i = 0; i < halfHeight; i++)
    {
        for (unsigned int j = 0; j < halfWidth; j++)
        {
            Pixel PixelA;

            PixelA.blue = VectorA[i * halfWidth + j].blue;
            PixelA.green = VectorA[i * halfWidth + j].green;
            PixelA.red = VectorA[i * halfWidth + j].red;
            newVector.push_back(PixelA);
        }
        for (unsigned int j = 0; j < halfWidth; j++)
        {
            Pixel PixelB;

            PixelB.blue = VectorB[i * halfWidth + j].blue;
            PixelB.green = VectorB[i * halfWidth + j].green;
            PixelB.red = VectorB[i * halfWidth + j].red;
            newVector.push_back(PixelB);
        }

    }

    for (unsigned int i = 0; i < halfHeight; i++)
    {
        for (unsigned int j = 0; j < halfWidth; j++)
        {
            Pixel PixelC;

            PixelC.blue = VectorC[i * halfWidth + j].blue;
            PixelC.green = VectorC[i * halfWidth + j].green;
            PixelC.red = VectorC[i * halfWidth + j].red;
            newVector.push_back(PixelC);
        }
        for (unsigned int j = 0; j < halfWidth; j++)
        {
            Pixel PixelD;

            PixelD.blue = VectorD[i * halfWidth + j].blue;
            PixelD.green = VectorD[i * halfWidth + j].green;
            PixelD.red = VectorD[i * halfWidth + j].red;
            newVector.push_back(PixelD);
        }

    }
    newImage.AdjustVector(newVector);
    return newImage;

}




int main()
{
    Image Car;

    Image Pattern1;
    Image Pattern2;

    Image Layer1;
    Image Layer2;
    Image LayerBlue;
    Image LayerGreen;
    Image LayerRed;

    Image Text;
    Image Text2;
    Image Circles;


    // Part 1
    Pattern1.ReadImage("./input/pattern1.tga");
    Layer1.ReadImage("./input/layer1.tga");
    Image Part1 = Multiply(Pattern1, Layer1);
    Part1.WriteImage("./output/part1.tga");
    cout << endl;


    // Part 2
    Car.ReadImage("./input/car.tga");
    Layer2.ReadImage("./input/layer2.tga");
    Image Part2 = Subtract(Car, Layer2);
    Part2.WriteImage("./output/part2.tga");
    cout << endl;


    // Part 3
    Layer1.ReadImage("./input/layer1.tga");
    Pattern2.ReadImage("./input/pattern2.tga");
    Text.ReadImage("./input/text.tga");
    Image Part3A = Multiply(Pattern2, Layer1);
    Image Part3B = Screen(Part3A, Text);
    Part3B.WriteImage("./output/part3.tga");
    cout << endl;


    // Part 4
    Layer2.ReadImage("./input/layer2.tga");
    Circles.ReadImage("./input/circles.tga");
    Pattern2.ReadImage("./input/pattern2.tga");
    Image Part4A = Multiply(Circles, Layer2);
    Image Part4B = Subtract(Part4A, Pattern2);
    Part4B.WriteImage("./output/part4.tga");



    // Part 5: Combine “layer1.tga” (as the top layer)
    // with “pattern1.tga” using the Overlay blending mode

    Image Part5 = Overlay(Pattern1, Layer1);
    Part5.WriteImage("./output/part5.tga");


    // Part 6: Load “car.tga” and add 200 to the green channel
    Image Part6 = AddColor(Car, 0, 200, 0);
    Part6.WriteImage("./output/part6.tga");

    // Part 7: Load “car.tga” and scale/multiply the red channel by 4
    // and the blue channel by 0
    Image Part7 = MultiplyColor(Car, 0, 1, 4);
    Part7.WriteImage("./output/part7.tga");


    // Part 8: Load “car.tga” and write each channel to a separate file
    // the red channel should be “part8_r.tga”
    // the green channel should be “part8_g.tga”
    // the blue channel should be “part8_b.tga”
    Image BlueChannel = SeparateByChannel(66, Car);
    Image GreenChannel = SeparateByChannel(71, Car);
    Image RedChannel = SeparateByChannel(82, Car);
    BlueChannel.WriteImage("./output/part8_b.tga");
    GreenChannel.WriteImage("./output/part8_g.tga");
    RedChannel.WriteImage("./output/part8_r.tga");

    // Part 9: Load “layer_red.tga”, “layer_green.tga” and “layer_blue.tga”
    // combine the three files into one file
    // The data from “layer_red.tga” is the red channel of the new image
    // layer_green is green, and layer_blue is blue.
    LayerBlue.ReadImage("./input/layer_blue.tga");
    LayerGreen.ReadImage("./input/layer_green.tga");
    LayerRed.ReadImage("./input/layer_red.tga");
    Image Part9 = CombineByChannel(LayerBlue, LayerGreen, LayerRed);
    Part9.WriteImage("./output/part9.tga");



    // Part 10: Load “text2.tga”, and rotate it 180 degrees, flipping it upside down
    Text2.ReadImage("./input/text2.tga");
    Image Part10 = Rotate(Text2);
    Part10.WriteImage("./output/part10.tga");

    // Extra Credit
    Car.ReadImage("./input/car.tga");
    Circles.ReadImage("./input/circles.tga");
    Pattern1.ReadImage("./input/pattern1.tga");
    Text.ReadImage("./input/text.tga");
    Image ExtraCredit = CombineQuadrants(Text, Pattern1, Car, Circles);
    ExtraCredit.WriteImage("./output/extracredit.tga");

    return 0;
}




