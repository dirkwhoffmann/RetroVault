// -----------------------------------------------------------------------------
// This file is part of RetroVault
//
// Copyright (C) Dirk W. Hoffmann. www.dirkwhoffmann.de
// Licensed under the Mozilla Public License v2
//
// See https://mozilla.org/MPL/2.0 for license information
// -----------------------------------------------------------------------------

#pragma once

#include "Controller.h"
#include <QtQml>

class AppController : public Controller {
    Q_OBJECT

  public:

    static AppController *instance();
    static AppController *create(QQmlEngine *qmlEngine, QJSEngine *jsEngine);

    using Controller::Controller;

    Q_INVOKABLE bool hasFuse() const;
    Q_INVOKABLE void showError(const QString &message);
    Q_INVOKABLE void showNotification(const QString &message);

    void rethrow(std::exception &e);

  signals:

    void requestErrorDialog(const QString &message);
    void requestNotificationDialog(const QString &message);
};
