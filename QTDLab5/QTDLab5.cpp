// Dinh, Thomas  CS230 Section 11614 6/9/2022
// Fifth Laboratory Assignment - Count colors
// Completed on Windows 10 Visual Studio 2022

#include <iostream>
#include <string>
#include "windows.h"
#include <fstream>
using namespace std;

ULONGLONG getTime64(LPFILETIME a);

int main(int argc, char* argv[])
{
    int input;
    int count = 0;
    //int tempCount = 0;
    int pixelCount = 0;
    SYSTEMTIME loct;

    ifstream bitmap;
    ifstream colorValues;
    bitmap.open("CS546.bmp", std::ios::in | ios::binary);
    colorValues.open("C:\\Temp\\Colors64.txt", ios::in);
    if (!bitmap.is_open() || !colorValues.is_open())
    {
        cout << "Could not be opened." << std::endl;
        return 0;
    }
    GetLocalTime(&loct);
    double fStartTime = loct.wHour * 3600 + loct.wMinute * 60 + loct.wSecond + (loct.wMilliseconds / 1000.0);

     struct RGB
    {
        string name;
        unsigned int r = 256, g = 256, b = 256;
        int matchCount = 0;
    };
    RGB bmiColors[64];

    for (int i = 0; !colorValues.eof(); i++)
    {
        /*
        colorValues >> bmiColors[i].r >> bmiColors[i].g >> bmiColors[i].b;
        colorValues.ignore();
        getline(colorValues, bmiColors[i].name);
        */

        for (int j = 0; j < 3; j++)
        {
            colorValues >> input;
            if (input < 0)
            {
                cout << "Invalid input! RGB values cannot be negative." << endl;
                colorValues.ignore(1000, '\n');
                break;
            }
            else if (input > 255)
            {
                cout << "Invalid input! RGB values cannot be over 255." << endl;
                colorValues.ignore(1000, '\n');
                break;
            }
            else
            {
                if (j == 0)
                    bmiColors[i].r = input;
                else if (j == 1)
                    bmiColors[i].g = input;
                else
                {
                    bmiColors[i].b = input;
                    colorValues.ignore(8, '\t');
                    getline(colorValues, bmiColors[i].name);
                }
            }
        }
    }
    colorValues.close();

    BITMAPFILEHEADER bmfh;
    BITMAPINFOHEADER bmih;

    bitmap.read((char*)&bmfh, sizeof(BITMAPFILEHEADER));

    bitmap.read((char*)&bmih, sizeof(BITMAPINFOHEADER));

    bool isFound = 0;
    int previousPixel = 0;
    unsigned char red, green, blue;
    unsigned int oldRed, oldGreen, oldBlue;
    bool check = false;
    bool check2 = false;
    int n = sizeof(bmiColors) / sizeof(bmiColors[0]);
    int mid = 32;
    for (int i = 0; i < bmih.biSizeImage/3; i++)
    {
        isFound = false;
        int front = 0;
        int back = n-1;
        bitmap.read((char*)&blue, sizeof(unsigned char));
        bitmap.read((char*)&green, sizeof(unsigned char));
        bitmap.read((char*)&red, sizeof(unsigned char));

        if (check == false && check2 == false)
        {
            oldRed = int(red);
            oldGreen = int(green);
            oldBlue = int(blue);
            check = true;
        }
        if (oldBlue == int(blue) && oldGreen == int(green) && oldRed == int(red) && check2 == true)
        {
        bmiColors[previousPixel].matchCount += 1;
        isFound = true;
        count++;
        }

        while (front <= back && isFound == false)
        {
            if (int(blue) == bmiColors[front].b && int(green) == bmiColors[front].g && int(red) == bmiColors[front].r)
            {
                bmiColors[front].matchCount += 1;
                previousPixel = front;
                isFound = true;
            }
            else if (int(blue) == bmiColors[back].b && int(green) == bmiColors[back].g && int(red) == bmiColors[back].r)
            {
                bmiColors[back].matchCount += 1;
                previousPixel = back;
                isFound = true;
            }
            front++;
            back--;
            count++; //

        }
            oldRed = int(red);
            oldGreen = int(green);
            oldBlue = int(blue);
            if (oldRed == bmiColors[previousPixel].r && oldGreen == bmiColors[previousPixel].g && oldBlue == bmiColors[previousPixel].b)
                check2 = true;
            else check2 = false;
    }
    
    for (int i = 0; i < 64; i++)
    {
       //pixelCount += bmiColors[i].matchCount;
        if(bmiColors[i].matchCount > 0)
        cout << bmiColors[i].name << ": " << bmiColors[i].matchCount << endl;
    }
    //cout << pixelCount << endl;

    cout << "Counts of comparisons: " << count << endl;

    GetLocalTime(&loct);
    double fEndTime = loct.wHour * 3600 + loct.wMinute * 60 + loct.wSecond + (loct.wMilliseconds / 1000.0);
    double cpuTime = fEndTime - fStartTime;
    cout << "CPU time used: " << cpuTime << endl;
}