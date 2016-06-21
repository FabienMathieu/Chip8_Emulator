#ifndef CHIP8_H
#define CHIP8_H

#include <cstdint>
#include <stack>
#include <QtCore/QString>
#include <QtCore/QTimer>
#include <array>
#include <Chip8Screen.h>

class Chip8 : public QObject
{

Q_OBJECT

public:
    Chip8();

    Chip8Screen* getChip8Screen() { return &mScreenBuffer; }

public slots:
    void loadRom(const QString& urlAsString);
    void startEmulation();
    void stopEmulation();

signals:
    void imageChanged();

private:
    std::uint16_t PC = 0x200;         // Compteur d'instruction
    std::array< std::int8_t, 16 > V;      // Registres V0 -> V15
    std::array< std::int8_t, 8 > RPL;       // Regitres RPL
    std::uint16_t I;          // Registre I
    std::array< std::int8_t, 4096 > memory; // Ram dans laquelle le programme sera stocké

    std::int8_t DT;    // Timer d'usage général
    std::int8_t ST;    // Timer pour le son

    bool keyboard[16];  // Pour la gestion des entrées clavier

    Chip8Screen mScreenBuffer;

    // Variables temporaires nécessaire aux intrutions */
    ushort NNN;
    std::uint8_t KK;
    std::uint8_t K;
    std::uint8_t X;
    std::uint8_t Y;

    std::stack< std::uint16_t > adressStack;

    std::random_device r;

    // Choose a random mean between 1 and 6
    std::default_random_engine e1;
    std::uniform_int_distribution< std::uint8_t  > uniform_dist;

    bool extendedMode = false;

    QTimer mChip8Timer;

    void emulate();

    // Instructions //
    void Inst_00CK();
    void Inst_00E0();
    void Inst_00EE();
    void Inst_00FB();
    void Inst_00FC();
    void Inst_00FE();
    void Inst_00FF();
    void Inst_1NNN();
    void Inst_2NNN();
    void Inst_3XKK();
    void Inst_4XKK();
    void Inst_5XY0();
    void Inst_6XKK();
    void Inst_7XKK();
    void Inst_8XY0();
    void Inst_8XY1();
    void Inst_8XY2();
    void Inst_8XY3();
    void Inst_8XY4();
    void Inst_8XY5();
    void Inst_8XY6();
    void Inst_8XY7();
    void Inst_8XYE();
    void Inst_9XY0();
    void Inst_ANNN();
    void Inst_BNNN();
    void Inst_CXKK();
    void Inst_DXYK();
    void Inst_EX9E();
    void Inst_EXA1();
    void Inst_FX07();
    void Inst_FX0A();
    void Inst_FX15();
    void Inst_FX18();
    void Inst_FX1E();
    void Inst_FX29();
    void Inst_FX30();
    void Inst_FX33();
    void Inst_FX55();
    void Inst_FX65();
    void Inst_FX75();
    void Inst_FX85();
};

#endif // CHIP8_H
