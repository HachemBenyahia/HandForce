#ifndef PIXEL
#define PIXEL

#include <iostream>
#include <stdlib.h>

class Pixel
{
    private :
        int m_red, m_green, m_blue;

    public :
        Pixel(int red = 0, int green = 0, int blue = 0);
        void SetRed(int red);
        void SetGreen(int green);
        void SetBlue(int blue);
        int GetRed() const {return m_red;}
        int GetGreen() const {return m_green;}
        int GetBlue() const {return m_blue;}
        void Print();
        bool Compare(const Pixel& pixel);
        bool operator==(const Pixel& pixel);
};

#endif
