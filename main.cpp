// -----------------------------------------------------------------------------
// This file is part of RetroVault
//
// Copyright (C) Dirk W. Hoffmann. www.dirkwhoffmann.de
// Licensed under the Mozilla Public License v2
//
// See https://mozilla.org/MPL/2.0 for license information
// -----------------------------------------------------------------------------

#include "QmlAdapter.h"
#include "UsageDisplay.h"
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQuickStyle>
#include <QQmlContext>

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;

    // Configure app appearance
    QQuickStyle::setStyle("Fusion");
    QCoreApplication::setAttribute(Qt::AA_DontUseNativeMenuBar, true);

    // Make the adapter available in QML
    QmlAdapter proxy(&app);

    // engine.rootContext()->setContextProperty("proxy", &proxy);
    qmlRegisterSingletonInstance<QmlAdapter>("Backend", 1, 0, "Backend", &proxy);
    qmlRegisterSingletonType(QUrl("qrc:/qt/qml/retrovaultUI/qml/UIController.qml"),
                             "Retrovault.Signals", 1, 0, "UIController");
    qmlRegisterUncreatableType<DeviceInfo>("DeviceInfo", 1, 0, "DeviceInfo",
                                       "DeviceInfo is read-only and managed by C++");
    qmlRegisterType<UsageDisplay>("UsageDisplay", 1, 0, "UsageDisplay");

    // Load the QML file
    const QUrl url(QStringLiteral("qrc:/qt/qml/retrovaultUI/qml/Main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
        &app, [url](QObject *obj, const QUrl &objUrl) {
            if (!obj && url == objUrl)
                QCoreApplication::exit(-1);
        }, Qt::QueuedConnection);
    engine.load(url);

    proxy.refreshSidebar();

    // Run the app
    return app.exec();
}