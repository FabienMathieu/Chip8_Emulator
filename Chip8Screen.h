#ifndef CHIP8SCREEN_H
#define CHIP8SCREEN_H

#include <QObject>
#include <array>

class Chip8Screen : public QObject
{
    Q_OBJECT
public:
    explicit Chip8Screen(QObject *parent = 0);

    void resize(std::uint32_t size);
    void clear();

    void setPixel(unsigned int pixel, std::uint8_t color);
    std::uint8_t getPixel(unsigned int pixel);

    unsigned int length() { return mScreen.size(); }

signals:

public slots:
    std::uint8_t* getData();


private:
    std::vector< std::uint8_t > mScreen;

};

#endif // CHIP8SCREEN_H
