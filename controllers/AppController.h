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

    bool m_darkMode = false;

  public:

    static AppController *instance();
    static AppController *create(QQmlEngine *qmlEngine, QJSEngine *jsEngine);

    AppController();

    Q_PROPERTY(bool darkMode READ getDarkMode NOTIFY darkModeChanged FINAL)

    Q_INVOKABLE bool hasFuse() const;
    Q_INVOKABLE void showError(const QString &message);
    Q_INVOKABLE void showNotification(const QString &message);

    bool getDarkMode() const { return m_darkMode; }
    void setDarkMode(bool value) { m_darkMode = value; emit darkModeChanged(); }

    void rethrow(std::exception &e);

  signals:

    void darkModeChanged();
    void requestErrorDialog(const QString &message);
    void requestNotificationDialog(const QString &message);
};
