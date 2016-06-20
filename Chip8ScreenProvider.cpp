#include "Chip8ScreenProvider.h"
#include "Chip8.h"

Chip8ScreenProvider::Chip8ScreenProvider() :
    QQuickImageProvider(QQuickImageProvider::Image)
{

}

QImage Chip8ScreenProvider::requestImage(const QString &, QSize *size, const QSize &requestedSize)
{
    uint width = 64;
    uint height = 32;

    if(size)
    {
        *size = QSize(width, height);
    }

    QImage image(requestedSize.width() > 0 ? requestedSize.width() : width,
                   requestedSize.height() > 0 ? requestedSize.height() : height,
                 QImage::Format_RGB16);
    if(mChip8 != nullptr)
    {
        std::uint8_t* data = mChip8->getChip8Screen()->getData();
        for(uint i = 0; i < height; ++i)
        {
            for(uint j = 0; j < width; ++j)
            {
                int n = (64 * i + j) * 4;
                image.setPixel(j, i, data[n] == 0 ? QColor::fromRgb(0, 0, 0).rgba() : QColor::fromRgb(255, 255, 255).rgba());
                /*if(i == height / 2)
                    image.setPixel(j, i, QColor(255, 255, 255, 255).rgba());*/
            }
        }
    }

    return image;
}
