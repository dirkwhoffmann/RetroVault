// -----------------------------------------------------------------------------
// This file is part of RetroVault
//
// Copyright (C) Dirk W. Hoffmann. www.dirkwhoffmann.de
// Licensed under the Mozilla Public License v2
//
// See https://mozilla.org/MPL/2.0 for license information
// -----------------------------------------------------------------------------

#pragma once

#include "QmlAdapterTypes.h"
#include "DeviceManager.h"
#include "FuseDevice.h"
#include "SidebarModel.h"
#include "BlockTableModel.h"

#include <QObject>
#include <QStringList>

class QmlAdapter : public QObject {

    Q_OBJECT

    SidebarModel *m_sidebarModel;
    BlockTableModel *m_blockTableModel;
    DeviceInfo *m_deviceInfo;

    Q_PROPERTY(SidebarModel* sidebarModel READ sidebarModel CONSTANT)
    Q_PROPERTY(BlockTableModel* blockTableModel READ blockTableModel CONSTANT)
    Q_PROPERTY(DeviceInfo* deviceInfo READ deviceInfo CONSTANT)

    signals:
    void updateSidebar() const;
    void updateCanvas() const;
    void deviceInfoChanged();

public:

    // Gateway to the C++ code
    DeviceManager manager;

    explicit QmlAdapter(QObject *parent = nullptr);

private:

    SidebarModel* sidebarModel() const { return m_sidebarModel; }
    BlockTableModel* blockTableModel() const { return m_blockTableModel; }
    DeviceInfo* deviceInfo() const { return m_deviceInfo; }

    void processMsg(int value);

public:

    Q_INVOKABLE void refreshSidebar() { m_sidebarModel->refresh(*this); }
    Q_INVOKABLE void refreshBlockView(int dev, int blk) { m_blockTableModel->refresh(*this, dev, blk); }

    // Q_INVOKABLE void selectDevice(int deviceNr);
    Q_INVOKABLE DeviceInfo *getDeviceInfo(int deviceNr);

    // Converts a C++ exception to a JS exception
    void rethrow(std::exception &e);

    //
    // API
    //

public:

    // General
    Q_INVOKABLE bool hasFuse() const { return false; } // CHANGE BACK ASAP return DeviceManager::hasFuse(); }

    // Adding and removing devices
    Q_INVOKABLE void add(const QUrl &imageFile);
    Q_INVOKABLE void remove(int deviceNr) { manager.remove(deviceNr); }
    Q_INVOKABLE void removeAll() { manager.removeAll(); }

    // Querying properties
    // Q_INVOKABLE DeviceInfo *getInfo(int deviceNr);

    //
    // Block Table
    //

    int tmp = 0;
    Q_INVOKABLE void updateBlockTableModel()
    {
        tmp++;
    }

    //
    // Devices and Volumes
    //

    Q_INVOKABLE int deviceCount() { return manager.numDevices(); }
    Q_INVOKABLE int volumeCount(int devNr) { return manager.getDevice(devNr).count(); }

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