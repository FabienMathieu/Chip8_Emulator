#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "Chip8.h"
#include "Chip8ScreenProvider.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    Chip8 chip8;
    Chip8ScreenProvider* chip8ScreenProvider = new Chip8ScreenProvider;
    chip8ScreenProvider->setChip8(&chip8);

    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("chip8", &chip8);
    engine.addImageProvider(QLatin1String("chip8Screen"), chip8ScreenProvider);// nous passons ensuite notre object Chip8Screen comme contextProperty dans notre QML. C'est ainsi que nous pourrons l'utiliser.
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));


    return app.exec();
}
