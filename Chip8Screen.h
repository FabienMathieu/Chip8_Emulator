#ifndef CHIP8SCREEN_H
#define CHIP8SCREEN_H

#include <QObject>
#include <array>

class Chip8Screen : public QObject
{
    Q_OBJECT
public:
    explicit Chip8Screen(QObject *parent = 0);

    void clear();

    void setPixel(unsigned int pixel, std::uint8_t color);
    std::uint8_t getPixel(unsigned int pixel);

    unsigned int length() { return mScreen.size(); }

signals:

public slots:
    std::uint8_t* getData();


private:
    std::array< std::uint8_t, 8192 > mScreen; // Ecran du chip 8 (64 * 32 * 4)

};

#endif // CHIP8SCREEN_H
