#include "Image.h"

Image::Image(std::string name) : m_name(name)
{
    cimg_library::CImg<unsigned char> src((char*)name.c_str());
    m_width = src.width();
    m_height = src.height();

    m_image = new Pixel*[m_height];
    for(int i = 0 ; i < m_height ; i++)
        m_image[i] = new Pixel[m_width];

    for(int i = 0 ; i < m_height ; i++)
        for(int j = 0 ; j < m_width ; j++)
            m_image[i][j] = Pixel(src(j, i, 0, 0), src(j, i, 0, 1), src(j, i, 0, 2));
}

Pixel Image::GetPixel(int i, int j)
{
    return m_image[i][j];
}

int Image::GetHeight()
{
    return m_height;
}

int Image::GetWidth()
{
    return m_width;
}

bool Image::Compare(const Image& image, double equalsProportion, double progressLimit) const
{
    double size = image.m_height * image.m_width;
    double k = 0, equal = 0;

    for(int i = 0 ; i < image.m_height ; i++)
        for(int j = 0 ; j < image.m_width ; j++)
        {
            if(this->m_image[i][j].Compare(image.m_image[i][j]))
                equal++;

            k++;

            if(equal / k < equalsProportion && k / size > progressLimit)
                return false;
        }

    return true;
}

void Image::Print()
{
    for(int i = 0 ; i < m_height ; i++)
    {
        for(int j = 0 ; j < m_width ; j++)
        {
            m_image[i][j].Print();
            std::cout << " ";
        }
        std::cout << std::endl;
    }
}

void Image::SetPixel(int i, int j, Pixel pixel)
{
    m_image[i][j] = pixel;
}

void Image::Reset()
{
    for(int i = 0 ; i < m_height ; i++)
        for(int j = 0 ; j < m_width ; j++)
            m_image[i][j] = 0;
}

Image::~Image()
{
    for(int i = 0 ; i < m_height ; i++)
        delete[] m_image[i];
    delete[] m_image;
}

void Image::SetHeight(int height)
{
    this->m_height = height;
}

void Image::SetWidth(int width)
{
    this->m_width = width;
}

bool Image::GreenCard()
{
    int k = 0;

    Pixel green(GREEN_R, GREEN_G, GREEN_B);

    for(int i = 0 ; i < CARD_HEIGHT ; i++)
        for(int j = 0 ; j < CARD_WIDTH ; j++)
            if(m_image[i][j].Compare(green))
                k++;

    if(k > (CARD_HEIGHT * CARD_WIDTH)/4)
        return true;

    return false;
}
