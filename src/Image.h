#ifndef IMAGE
#define IMAGE

#include <iostream>
#include "Pixel.h"
#include "CImg.h"
#include <string>

#define GREEN_R 2
#define GREEN_G 120
#define GREEN_B 39

#define CARD_WIDTH 50 // to be removed and centralized in constants file
#define CARD_HEIGHT 36

class Image
{
    private :
        Pixel** m_image;
        int m_height, m_width;
        std::string m_name;

    public :
        Image(std::string name);
        ~Image();
        void SetHeight(int height);
        void SetWidth(int width);
        int GetHeight();
        int GetWidth();
        void SetPixel(int i, int j, Pixel pixel);
        void Reset();
        Pixel GetPixel(int i, int j);
        void Print();
        bool Compare(const Image& image, double equalsProportion = 0.96, double progressLimit = 0.50) const;
        bool GreenCard();
};

#endif
