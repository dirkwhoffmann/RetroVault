// -----------------------------------------------------------------------------
// This file is part of RetroVault
//
// Copyright (C) Dirk W. Hoffmann. www.dirkwhoffmann.de
// Licensed under the Mozilla Public License v2
//
// See https://mozilla.org/MPL/2.0 for license information
// -----------------------------------------------------------------------------

#include <QObject>
#include <QStringList>
#include <QUrl>

#include "DeviceManager.h"
#include "FuseDevice.h"

#pragma once

class VaultProxy : public QObject {

    Q_OBJECT

    DeviceManager manager;

public:

    explicit VaultProxy(QObject *parent = nullptr) : QObject(parent) {}

private:

    // Converts a C++ exception to a JS exception
    void rethrow(std::exception &e);

    //
    // API
    //

public:

    // void open(const fs::path &url);
    Q_INVOKABLE void add(const QUrl &imageFile);

    Q_INVOKABLE void remove(int deviceNr) { manager.remove(deviceNr); }
    Q_INVOKABLE void removeAll() { manager.removeAll(); }


    //
    // Experimental
    //

    Q_INVOKABLE int deviceCount() {
        return 4;
        // return Backend::instance()->numberOfDevices();
    }

    Q_INVOKABLE QString deviceTitle(int deviceIdx)
    {
        switch (deviceIdx)
        {
        case 0: return QStringLiteral("Batman");
        case 1: return QStringLiteral("Return of the Mutan Camals");
        case 2: return QStringLiteral("Popeye's adventure");
        case 3: return QStringLiteral("Summer games");
        default: return QStringLiteral("Unknown");
        }
        // auto* dev = Backend::instance()->getDevice(deviceIdx);
        // return dev ? QString::fromStdString(dev->imageInfo().filename) : "";
    }

    Q_INVOKABLE QStringList volumeNames(int deviceIdx) {
        QStringList list;

        list << QStringLiteral("Partion 1");
        if (deviceIdx >= 2) list << QStringLiteral("Partion 2");
        if (deviceIdx >= 3) list << QStringLiteral("Partion 3");
        /*
        auto* dev = Backend::instance()->getDevice(deviceIdx);
        if (dev) {
            for (int i = 0; i < dev->count(); ++i) {
                // Here is your type conversion: std::string -> QString
                list << QString::fromStdString(dev->getVolume(i).getName());
            }
        }
        */
        return list;
    }

    // --- The "Action" API ---

    Q_INVOKABLE void addDevice(const QUrl &url) {
        /*
        std::string path = url.toLocalFile().toStdString();
        Backend::instance()->loadDevice(path);
        */
        emit dataChanged(); // Notify UI to refresh
    }

    Q_INVOKABLE void mount(int devIdx, int volIdx) {
        /*
        auto* dev = Backend::instance()->getDevice(devIdx);
        if (dev) dev->mount(volIdx);
        */
        emit dataChanged();
    }

    signals:
        void dataChanged(); // The "Bat-Signal" for the UI
};