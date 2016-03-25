#include "Pixel.h"

Pixel::Pixel(int red, int green, int blue) : m_red(red), m_green(green), m_blue(blue) {}

void Pixel::SetRed(int red)
{
    this->m_red = red;
}
void Pixel::SetGreen(int green)
{
    this->m_green = green;
}

void Pixel::SetBlue(int blue)
{
    this->m_blue = blue;
}

bool Pixel::operator==(const Pixel& pixel)
{
    return (this->m_red == pixel.m_red && this->m_green == pixel.m_green && this->m_blue == pixel.m_blue);
}

void Pixel::Print()
{
    std::cout << "(" << m_red << ", " << m_green << ", " << m_blue << ")";
}

bool Pixel::Compare(const Pixel& pixel)
{
    if((abs(pixel.GetRed() - this->GetRed()) < 10) &&
       (abs(pixel.GetGreen() - this->GetGreen()) < 10) &&
       (abs(pixel.GetBlue() - this->GetBlue()) < 10))
        return true;

    return false;
}
