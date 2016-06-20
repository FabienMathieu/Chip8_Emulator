#include "Chip8.h"
#include <QtCore/QFile>
#include <QtCore/QByteArray>
#include <QtCore/QUrl>
#include <QtCore/QDebug>

#include <climits>
#include <iostream>

Chip8::Chip8()
{
    memory.fill(0);

    // Initialisation du text
    memory[0] = 240; memory[1] = 144; memory[2] = 144; memory[3] = 144; memory[4] = 240;
    memory[5] = 32; memory[6] = 96; memory[7] = 32; memory[8] = 32; memory[9] = 112;
    memory[10] = 240; memory[11] = 16; memory[12] = 240; memory[13] = 128; memory[14] = 240;
    memory[15] = 240; memory[16] = 16; memory[17] = 240; memory[18] = 16; memory[19] = 240;
    memory[20] = 144; memory[21] = 144; memory[22] = 240; memory[23] = 16; memory[24] = 16;
    memory[25] = 240; memory[26] = 128; memory[27] = 240; memory[28] = 16; memory[29] = 240;
    memory[30] = 240; memory[31] = 128; memory[32] = 240; memory[33] = 144; memory[34] = 240;
    memory[35] = 240; memory[36] = 16; memory[37] = 32; memory[38] = 64; memory[39] = 64;
    memory[40] = 240; memory[41] = 144; memory[42] = 240; memory[43] = 144; memory[44] = 240;
    memory[45] = 240; memory[46] = 144; memory[47] = 240; memory[48] = 16; memory[49] = 240;
    memory[50] = 240; memory[51] = 144; memory[52] = 240; memory[53] = 144; memory[54] = 144;
    memory[55] = 224; memory[56] = 144; memory[57] = 224; memory[58] = 144; memory[59] = 224;
    memory[60] = 240; memory[61] = 128; memory[62] = 128; memory[63] = 128; memory[64] = 240;
    memory[65] = 224; memory[66] = 144; memory[67] = 144; memory[68] = 144; memory[69] = 224;
    memory[70] = 240; memory[71] = 128; memory[72] = 240; memory[73] = 128; memory[74] = 240;
    memory[75] = 240; memory[76] = 128; memory[77] = 240; memory[78] = 128; memory[79] = 128;

    std::random_device r;

    // Choose a random mean between 0 and 255
    e1 = std::default_random_engine(r());
    uniform_dist = std::uniform_int_distribution< std::uint8_t  > (0, 255);

    mChip8Timer.setInterval(16);
    QObject::connect(&mChip8Timer, &QTimer::timeout, this, &Chip8::emulate);

    DT = ST = 0;

}

void Chip8::loadRom(const QString &urlAsString)
{
    QUrl url(urlAsString);
    QString filename = url.toLocalFile();
    QFile file(filename);
    if(!file.exists())
        std::cout << "le fichier " << filename.toStdString().c_str() << " n'existe pas" << std::endl;
    file.open(QIODevice::ReadOnly);
    QByteArray byteArray = file.readAll();
    file.close();

    // Copie de la rom dans le tableau
    for(int i = 0; i < byteArray.size(); ++i)
    {
        this->memory[0x200 + i] = byteArray.at(i);
    }

    std::cout << filename.toStdString().c_str() << std::endl;


}

void Chip8::startEmulation()
{
    // Demarre le timer
    mChip8Timer.start();
}

void Chip8::stopEmulation()
{
    // Demarre le timer
    mChip8Timer.stop();
}

void Chip8::emulate()
{
    //qDebug() << "instruction\n";

    ushort opCode = static_cast< ushort >((this->memory[this->PC] << 8) + this->memory[this->PC + 1]);

    this->PC += 2;

    ushort code = static_cast< ushort >(opCode & 0xF000);
    NNN = static_cast< ushort >(opCode & 0x0FFF);
    KK = static_cast< ushort >(opCode & 0x00FF);
    K = static_cast< ushort >(opCode & 0x000F);
    X = static_cast< ushort >(opCode & 0x0F00) >> 8;
    Y = static_cast< ushort >(opCode & 0x00F0) >> 4;


    switch(code)
    {
    case 0x0000:
        switch(KK)
        {
        case 0xE0: Inst_00E0(); break;
        case 0xEE: Inst_00EE(); break;
        }
        break;

    case 0x1000: Inst_1NNN(); break;
    case 0x2000: Inst_2NNN(); break;
    case 0x3000: Inst_3XKK(); break;
    case 0x4000: Inst_4XKK(); break;
    case 0x5000: Inst_5XY0(); break;
    case 0x6000: Inst_6XKK(); break;
    case 0x7000: Inst_7XKK(); break;

    case 0x8000:
        switch(K)
        {
        case 0x0: Inst_8XY0(); break;
        case 0x1: Inst_8XY1(); break;
        case 0x2: Inst_8XY2(); break;
        case 0x3: Inst_8XY3(); break;
        case 0x4: Inst_8XY4(); break;
        case 0x5: Inst_8XY5(); break;
        case 0x6: Inst_8XY6(); break;
        case 0x7: Inst_8XY7(); break;
        case 0xE: Inst_8XYE(); break;
        }

        break;

    case 0x9000: Inst_9XY0(); break;

    case 0xA000: Inst_ANNN(); break;
    case 0xB000: Inst_BNNN(); break;
    case 0xC000: Inst_CXKK(); break;
    case 0xD000: Inst_DXYK(); break;

    case 0xE000:
        switch(KK)
        {
        case 0x9E: Inst_EX9E(); break;
        case 0xA1: Inst_EXA1(); break;
        }
        break;

    case 0xF000:
        switch(KK)
        {
        case 0x07: Inst_FX07(); break;
        case 0x0A: Inst_FX0A(); break;
        case 0x15: Inst_FX15(); break;
        case 0x18: Inst_FX18(); break;
        case 0x1E: Inst_FX1E(); break;
        case 0x29: Inst_FX29(); break;
        case 0x30: Inst_FX30(); break;
        case 0x33: Inst_FX33(); break;
        case 0x55: Inst_FX55(); break;
        case 0x65: Inst_FX65(); break;
        case 0x75: Inst_FX75(); break;
        case 0x85: Inst_FX85(); break;
        }
        break;
    }

    // Emulation de la fréquence d'horloge
    if(ST > 0)
        ST--;

    if(DT > 0)
        DT--;
    /*ST = ST > 0 ? ST-- : 0;
    DT = DT > 0 ? DT-- : 0;*/
}

void Chip8::Inst_00E0()
{
    mScreenBuffer.clear();
}

void Chip8::Inst_00EE()
{
    PC = adressStack.top();
    adressStack.pop();
}

void Chip8::Inst_1NNN()
{
    PC = NNN;
}

void Chip8::Inst_2NNN()
{
    adressStack.push(PC);
    PC = NNN;
}

void Chip8::Inst_3XKK()
{
    if(V[X] == KK)
        PC += 2;
}

void Chip8::Inst_4XKK()
{
    if(V[X] != KK)
        PC += 2;
}

void Chip8::Inst_5XY0()
{
    if(V[X] == V[Y])
        PC += 2;
}

void Chip8::Inst_6XKK()
{
    V[X] = KK;
}

void Chip8::Inst_7XKK()
{
    V[X] += KK;
}

void Chip8::Inst_8XY0()
{
    V[X] = V[Y];
}

void Chip8::Inst_8XY1()
{
    V[X] |= V[Y];
}

void Chip8::Inst_8XY2()
{
    V[X] &= V[Y];
}

void Chip8::Inst_8XY3()
{
    V[X] ^= V[Y];
}

void Chip8::Inst_8XY4()
{
    V[15] = V[X] + V[Y] > 255 ? 1 : 0;
    V[X] += V[Y];
}

void Chip8::Inst_8XY5()
{
    V[15] = V[X] > V[Y] ? 1 : 0;
    V[X] -= V[Y];
}

void Chip8::Inst_8XY6()
{
    V[15] = V[X] & 0x01;
    V[X] >>= 1;
}

void Chip8::Inst_8XY7()
{
    V[15] = V[X] < V[Y] ? 1 : 0;
    V[X] = V[Y] - V[X];
}

void Chip8::Inst_8XYE()
{
    V[15] = (V[X] & 0x80) >> 7;
    V[X] <<= 1;
}

void Chip8::Inst_9XY0()
{
    if(V[X] != V[Y])
        PC += 2;
}

void Chip8::Inst_ANNN()
{
    I = NNN;
}

void Chip8::Inst_BNNN()
{
    PC += (NNN + V[0]);
}

void Chip8::Inst_CXKK()
{
    std::uint8_t mean = uniform_dist(e1);

    V[X] = mean & KK;
    //V[X] = 97 & KK;
}

void Chip8::Inst_DXYK()
{
    V[15] = 0;
    for(std::uint8_t i = 0; i < K; ++i)
    {
        std::uint8_t ligne = memory[I + i];
        for(std::uint8_t n = 0; n < 8; ++n)
        {
            std::uint8_t pixel = static_cast< std::uint8_t >(static_cast< std::uint8_t >(ligne << n) >> 7);
            int pixelAdress = V[X] + n + (V[Y] + i) * 64;
            pixelAdress *= 4;
            pixelAdress %= mScreenBuffer.length();

            // recup la couleur dans le screen buffer
            int couleur = mScreenBuffer.getPixel(pixelAdress) + mScreenBuffer.getPixel(pixelAdress + 1) + mScreenBuffer.getPixel(pixelAdress + 2);

            if ((pixel != 0 && couleur == 0) || (pixel == 0 && couleur != 0))
            {
                mScreenBuffer.setPixel(pixelAdress, 255) ;
                mScreenBuffer.setPixel(pixelAdress + 1, 255);
                mScreenBuffer.setPixel(pixelAdress + 2, 255);
                mScreenBuffer.setPixel(pixelAdress + 3, 255);
            }
            else
            {
                mScreenBuffer.setPixel(pixelAdress, 0);
                mScreenBuffer.setPixel(pixelAdress + 1, 0);
                mScreenBuffer.setPixel(pixelAdress + 2, 0);
                mScreenBuffer.setPixel(pixelAdress + 3, 255);
            }

            if(pixel != 0 && couleur != 0)
                V[15] = 1;
        }
    }
}

void Chip8::Inst_EX9E()
{
    if(keyboard[V[X]])
        PC += 2;
}

void Chip8::Inst_EXA1()
{
    if(!keyboard[V[X]])
        PC += 2;
}

void Chip8::Inst_FX07()
{
    V[X] = DT;
}

void Chip8::Inst_FX0A()
{
    while (true)    // Tant qu'une touche n'est pas enfoncée( on return du coup)
    {
        for (std::uint8_t i = 0; i < 16; i++)
            if (keyboard[i] == true)
            {
                V[X] = i;
                return;
            }
    }
}

void Chip8::Inst_FX15()
{
    DT = V[X];
}

void Chip8::Inst_FX18()
{
    ST = V[X];
}

void Chip8::Inst_FX1E()
{
    I += V[X];
}

void Chip8::Inst_FX29()
{
    I = V[X] * 5;
}

void Chip8::Inst_FX30()
{
    I = V[X] * 5;
}

void Chip8::Inst_FX33()
{
    memory[I] = (V[X] / 100);
    memory[I + 1] = ((V[X] % 100) / 10);
    memory[I + 2] = ((V[X] % 100) % 10);
}

void Chip8::Inst_FX55()
{
    for(int i = 0; i < 15; ++i)
    {
        memory[I + i] = V[i];
    }
}

void Chip8::Inst_FX65()
{
    for(int i = 0; i < 15; ++i)
    {
        V[i] = memory[I + i];
    }
}

void Chip8::Inst_FX75()
{
    int maxX = std::max(X, static_cast< std::uint8_t >(7));
    for(int i = 0; i <= maxX; ++i)
    {
        RPL[i] = V[i];
    }
}

void Chip8::Inst_FX85()
{
    int maxX = std::max(X, static_cast< std::uint8_t >(7));
    for(int i = 0; i <= maxX; ++i)
    {
        V[i] = RPL[i];
    }
}
