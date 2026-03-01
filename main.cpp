#include "backend.h"
#include "VaultProxy.h"
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQuickStyle>
#include <QQmlContext>

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    // This makes it look like a desktop app instead of a mobile app
    // QQuickStyle::setStyle("FluentWinUI3");
    // QQuickStyle::setStyle("Material");
    QQuickStyle::setStyle("Fusion");

    QCoreApplication::setAttribute(Qt::AA_DontUseNativeMenuBar, true);

    Backend myBackend; // Create the C++ backend
    QQmlApplicationEngine engine;

    // Make 'deviceModel' available in QML
    engine.rootContext()->setContextProperty("vaultProxy", new VaultProxy(&app));
    engine.rootContext()->setContextProperty("cppBackend", &myBackend);

    // Load the QML file
    const QUrl url(QStringLiteral("qrc:/qt/qml/retrovaultUI/qml/main.qml"));

    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
        &app, [url](QObject *obj, const QUrl &objUrl) {
            if (!obj && url == objUrl)
                QCoreApplication::exit(-1);
        }, Qt::QueuedConnection);

    engine.load(url);

    return app.exec();
}