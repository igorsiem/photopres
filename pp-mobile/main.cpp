#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "ppcore.h"

/**
 * @brief Entry point to the mobile application
 *
 * @param argc Number of command-line args
 *
 * @param argv Vector of command-line arg strings
 *
 * @return Non-zero on error
 */
int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);

    // Register the C++ interface classes
    qmlRegisterType<PpCore>("com.igorsiemienowicz.ppcore", 1, 0, "PpCore");

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}   // end main function
