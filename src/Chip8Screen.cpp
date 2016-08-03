#include "Chip8Screen.h"

Chip8Screen::Chip8Screen(QObject *parent) : QObject(parent)
{
    resize(8192);
}

void Chip8Screen::resize(uint32_t size)
{
    mScreen.resize(size, 0);
}

void Chip8Screen::clear()
{
    mScreen.insert(mScreen.end(), 0);
}

void Chip8Screen::setPixel(unsigned int pixel, uint8_t color)
{
    mScreen.at(pixel) = color;
}

std::uint8_t Chip8Screen::getPixel(unsigned int pixel)
{
    return mScreen.at(pixel);
}

std::uint8_t* Chip8Screen::getData()
{
    return mScreen.data();
}
