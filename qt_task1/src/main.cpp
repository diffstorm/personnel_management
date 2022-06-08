#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "listmodel.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    ListModel listModel(&engine);
    listModel.load();

    engine.rootContext()->setContextProperty(QStringLiteral("listModel"), &listModel);
    engine.load(QUrl(QLatin1String("qrc:/main.qml")));

    return app.exec();
}
