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