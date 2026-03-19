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
#include "DeviceManager.h"
#include <QObject>
#include <QUrl>

class WindowController : public Controller
{
    Q_OBJECT

protected:

    // Gateway to the device manager
    DeviceManager *manager = nullptr;

    // Current selection
    int device = -1;
    int volume = -1;

public:
    Q_PROPERTY(int device READ getDevice WRITE setDevice NOTIFY selectionChanged)
    Q_PROPERTY(int volume READ getVolume WRITE setVolume NOTIFY selectionChanged)
    Q_PROPERTY(int numDevices READ getNumDevices NOTIFY numDevicesChanged)
    Q_PROPERTY(QString imageFormat READ currentImageFormat NOTIFY imageFormatChanged)
    Q_PROPERTY(QString deviceIcon READ currentDeviceIcon NOTIFY deviceIconChanged)
    Q_PROPERTY(QString volumeIcon READ currentVolumeIcon NOTIFY volumeIconChanged)
    Q_PROPERTY(bool isProtected READ currentWriteProtection WRITE setProtected NOTIFY isProtectedChanged)
    Q_PROPERTY(QString mountPoint READ currentMountPoint NOTIFY mountPointChanged)

    WindowController(QObject *parent = nullptr);
    ~WindowController() override;

    //
    // Getter
    //

public:

    DeviceManager* getManager() const { return manager; }
    int getDevice() const { return device; }
    int getVolume() const { return volume; }
    int getNumDevices() const { return manager->numDevices(); }

    //
    // Setter
    //

protected:

    void setDevice(int value);
    void setVolume(int value);
    void setProtected(bool value);

public:

    FuseDevice *fuseDevice(isize d) const;
    FuseVolume *fuseVolume(isize d, isize v) const;
    DiskImage *diskImage(isize d) const;
    QString diskImageFormat(isize d) const;
    QString deviceIcon(isize d) const;
    QString volumeIcon(isize d, isize v) const;
    bool writeProtection(isize d, isize v) const;

    FuseDevice *currentDevice() const { return fuseDevice(device); }
    FuseVolume *currentVolume() const { return fuseVolume(device, volume); }
    DiskImage *currentImage() const { return diskImage(device); }
    QString currentImageFormat() const { return diskImageFormat(device); }
    QString currentDeviceIcon() const { return deviceIcon(device); }
    QString currentVolumeIcon() const { return volumeIcon(device, volume); }
    bool currentWriteProtection() const  { return writeProtection(device, volume); }
    QString currentMountPoint() const;

    signals:
    void modelChanged();
    void selectionChanged();
    void numDevicesChanged();
    void imageFormatChanged();
    void deviceIconChanged();
    void volumeIconChanged();
    void isProtectedChanged();
    void mountPointChanged();

public slots:
    void addImage(const QUrl &url);
    void remove();
    void save();

    void select(int newDevice, int newVolume);
};
