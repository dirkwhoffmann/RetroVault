// -----------------------------------------------------------------------------
// This file is part of RetroVault
//
// Copyright (C) Dirk W. Hoffmann. www.dirkwhoffmann.de
// Licensed under the Mozilla Public License v2
//
// See https://mozilla.org/MPL/2.0 for license information
// -----------------------------------------------------------------------------

#include "backend/Model.h"
#include "AppController.h"
#include "Assets.h"
#include "DeviceManager.h"
// #include "UsageDisplay.h"
#include "DevicePanelController.h"
#include "SidebarController.h"
#include "SplashPanelController.h"
#include "VolumePanelController.h"
#include "WindowController.h"
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQuickStyle>
#include <QIcon>

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;

    // Configure app appearance
    QQuickStyle::setStyle("Fusion");
    QCoreApplication::setAttribute(Qt::AA_DontUseNativeMenuBar, true);
    app.setWindowIcon(QIcon(":/assets/images/AppIcon.png"));

    // Register types
    qmlRegisterType<DevicePanelController>("RetroVault.Controllers", 1, 0, "DevicePanelController");
    qmlRegisterType<SidebarController>("RetroVault.Controllers", 1, 0, "SidebarController");
    qmlRegisterType<SplashPanelController>("RetroVault.Controllers", 1, 0, "SplashPanelController");
    qmlRegisterType<VolumePanelController>("RetroVault.Controllers", 1, 0, "VolumePanelController");
    qmlRegisterType<WindowController>("RetroVault.Controllers", 1, 0, "WindowController");

    qmlRegisterSingletonType(QUrl("qrc:/qt/qml/retrovaultUI/qml/UIController.qml"),
                             "RetroVault.Signals", 1, 0, "UIController");
    qmlRegisterSingletonInstance("RetroVault.Controllers", 1, 0, "AppController", AppController::instance());
    qmlRegisterSingletonInstance("RetroVault.Assets", 1, 0, "Assets", Assets::instance());

    // Load the QML file
    const QUrl url(QStringLiteral("qrc:/qt/qml/retrovaultUI/qml/Main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
        &app, [url](QObject *obj, const QUrl &objUrl) {
            if (!obj && url == objUrl)
                QCoreApplication::exit(-1);
        }, Qt::QueuedConnection);
    engine.load(url);

    // Run the app
    try
    {
        return app.exec();
    } catch (std::exception &e) { printf("FATAL ERROR: ***\n%s\n", e.what()); }
}