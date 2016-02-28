#include <QApplication>
#include <QQmlApplicationEngine>
#include "hexview.h"
#include "hexmodel.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QQmlApplicationEngine engine;
    qmlRegisterType<HexView>("Forensics", 1, 0, "HexView2");
    qmlRegisterType<HexModel>("Forensics", 1, 0, "HexModel2");
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    return app.exec();
}

