// -----------------------------------------------------------------------------
// This file is part of RetroVault
//
// Copyright (C) Dirk W. Hoffmann. www.dirkwhoffmann.de
// Licensed under the Mozilla Public License v2
//
// See https://mozilla.org/MPL/2.0 for license information
// -----------------------------------------------------------------------------

#include "AppController.h"
#include "DeviceManager.h"
#include <QGuiApplication>
#include <QStyleHints>

AppController::AppController() : Controller()
{
    auto *hints = QGuiApplication::styleHints();
    m_darkMode = hints->colorScheme() == Qt::ColorScheme::Dark;
    printf("Dark mode = %d\n", m_darkMode);

    connect(hints, &QStyleHints::colorSchemeChanged, this, [this](Qt::ColorScheme scheme) {

        setDarkMode(scheme == Qt::ColorScheme::Dark);
        printf("Dark mode changed to %d %d\n", scheme, m_darkMode);
    });
}

AppController *
AppController::instance()
{
    static AppController *inst = new AppController();
    return inst;
}

AppController *
AppController::create(QQmlEngine *qmlEngine, QJSEngine *jsEngine)
{
    Q_UNUSED(qmlEngine)
    Q_UNUSED(jsEngine)
    return instance();
}

bool
AppController::hasFuse() const
{
    // return false;
    return DeviceManager::hasFuse();
}

void
AppController::showError(const QString &message)
{
    emit requestErrorDialog(message);
}

void
AppController::showNotification(const QString &message)
{
    emit requestNotificationDialog(message);
}