#ifndef CHIP8SCREENPROVIDER_H
#define CHIP8SCREENPROVIDER_H

#include <QtQuick/QQuickImageProvider>

class Chip8;

class Chip8ScreenProvider : public QQuickImageProvider
{
public:
    Chip8ScreenProvider();

    void setChip8(Chip8* chip8) { mChip8 = chip8; }

    virtual QImage requestImage(const QString &, QSize *size, const QSize &requestedSize);

private:
    Chip8* mChip8 = nullptr;
};

#endif // CHIP8SCREENPROVIDER_H
