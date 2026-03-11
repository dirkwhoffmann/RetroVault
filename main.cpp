// -----------------------------------------------------------------------------
// This file is part of RetroVault
//
// Copyright (C) Dirk W. Hoffmann. www.dirkwhoffmann.de
// Licensed under the Mozilla Public License v2
//
// See https://mozilla.org/MPL/2.0 for license information
// -----------------------------------------------------------------------------

#include "backend/Model.h"
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

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;

    // Configure app appearance
    QQuickStyle::setStyle("Fusion");
    QCoreApplication::setAttribute(Qt::AA_DontUseNativeMenuBar, true);

    // Register the QML model type
    qmlRegisterUncreatableType<Model>("RetroVault.Models", 1, 0, "Model", "Managed by C++");

    // Create the pure C++ model
    DeviceManager* manager = new DeviceManager();

    // 2. Wrap it in a QObject
    Model* model = new Model(manager, &app);

    // 3. Inject it as a context property
    engine.rootContext()->setContextProperty("mainModel", model);

    // Register types
    qmlRegisterType<DevicePanelController>("RetroVault.Controllers", 1, 0, "DevicePanelController");
    qmlRegisterType<SidebarController>("RetroVault.Controllers", 1, 0, "SidebarController");
    qmlRegisterType<SplashPanelController>("RetroVault.Controllers", 1, 0, "SplashPanelController");
    qmlRegisterType<VolumePanelController>("RetroVault.Controllers", 1, 0, "VolumePanelController");
    qmlRegisterType<WindowController>("RetroVault.Controllers", 1, 0, "WindowController");

    qmlRegisterSingletonType(QUrl("qrc:/qt/qml/retrovaultUI/qml/UIController.qml"),
                             "RetroVault.Signals", 1, 0, "UIController");
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
    return app.exec();
}