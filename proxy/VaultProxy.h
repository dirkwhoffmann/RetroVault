// -----------------------------------------------------------------------------
// This file is part of RetroVault
//
// Copyright (C) Dirk W. Hoffmann. www.dirkwhoffmann.de
// Licensed under the Mozilla Public License v2
//
// See https://mozilla.org/MPL/2.0 for license information
// -----------------------------------------------------------------------------

#pragma once

#include <QObject>
#include <QStringList>
#include <QUrl>

#include "DeviceManager.h"
#include "FuseDevice.h"
#include "SidebarModel.h"
#include "BlockTableModel.h"

class VaultProxy : public QObject {

    Q_OBJECT

    // This makes the model accessible as 'Backend.deviceModel' in QML
    Q_PROPERTY(SidebarModel* sidebarModel READ sidebarModel CONSTANT)
    Q_PROPERTY(BlockTableModel* blockTableModel READ blockTableModel CONSTANT)

    DeviceManager manager;

    SidebarModel *m_sidebarModel;
    BlockTableModel *m_blockTableModel;

    signals:
    void updateSidebar() const;
    void updateCanvas() const;

public:

    explicit VaultProxy(QObject *parent = nullptr);

    SidebarModel* sidebarModel() const { return m_sidebarModel; }
    BlockTableModel* blockTableModel() const { return m_blockTableModel; }

//    Q_INVOKABLE void init();

private:

    void processMsg(int value) const;

public:

    void refreshSidebar() { m_sidebarModel->refresh(*this); }
    void refreshBlockView() { m_blockTableModel->refresh(*this); }

    // Converts a C++ exception to a JS exception
    void rethrow(std::exception &e);

    //
    // API
    //

public:

    Q_INVOKABLE bool hasFuse() const { return DeviceManager::hasFuse(); }

    Q_INVOKABLE void add(const QUrl &imageFile);
    Q_INVOKABLE void remove(int deviceNr) { manager.remove(deviceNr); }
    Q_INVOKABLE void removeAll() { manager.removeAll(); }


    //
    // Experimental
    //

    Q_INVOKABLE int deviceCount() { return 4; }
    Q_INVOKABLE int volumeCount(int devNr) { return devNr + 1; }
    Q_INVOKABLE QStringList deviceInfo(int devNr)
    {
        QStringList list;

        switch (devNr)
        {
        case 0: list << QStringLiteral("Boulder Dash") << QStringLiteral("C64 Floppy Disk"); break;
        case 1: list << QStringLiteral("Return of the Camels") << QStringLiteral("Amiga Floppy Disk"); break;
        case 2: list << QStringLiteral("Batman Returns") << QStringLiteral("Atari ST Floppy Disk"); break;
        case 3: list << QStringLiteral("Summer Games") << QStringLiteral("C64 Floppy Disk"); break;
        default: list << QStringLiteral("???"); break;
        }

        return list;
    }

    Q_INVOKABLE QStringList volumeInfo(int devNr, int volNr)
    {
        QStringList list;

        switch (volNr)
        {
        case 0: list << QStringLiteral("/Volumes/BoulderDash") << QStringLiteral("Amiga FFS"); break;
        case 1: list << QStringLiteral("/Volumes/EvilCamels") << QStringLiteral("Amiga OFS"); break;
        case 2: list << QStringLiteral("/Volumes/Batman") << QStringLiteral("Amiga FFS"); break;
        case 3: list << QStringLiteral("/Volumes/EvilCamels") << QStringLiteral("Commodore CBM"); break;
        default: list << QStringLiteral("???"); break;
        }

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