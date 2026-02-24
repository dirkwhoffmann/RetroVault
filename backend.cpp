#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>  // Required for setContextProperty
#include "backend.h"

/*
int main(int argc, char *argv[]) {
    QGuiApplication app(argc, argv);

    Backend myBackend; // Create the C++ object
    QQmlApplicationEngine engine;

    // This makes 'myBackend' available in QML under the name 'cppBackend'
    engine.rootContext()->setContextProperty("cppBackend", &myBackend);

    // const QUrl url(u"qrc:/qt/qml/vBoardUI/main.qml"_s);
    const QUrl url(QStringLiteral("qrc:/qt/qml/vBoardUI/main.qml"));
    engine.load(url);

    return app.exec();
}
*/