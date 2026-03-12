#pragma once

#include "DeviceManager.h"
#include <QObject>
#include <QUrl>

class Model : public QObject {

    Q_OBJECT

public:

    // Gateway to devices and volumes
    DeviceManager* manager;

    // Current selection
    int device = -1;
    int volume = -1;

    Q_PROPERTY(int device READ getDevice WRITE setDevice NOTIFY deviceChanged)
    Q_PROPERTY(int volume READ getVolume WRITE setVolume NOTIFY volumeChanged)
    Q_PROPERTY(int numDevices READ getNumDevices NOTIFY numDevicesChanged)

    explicit Model(DeviceManager* m, QObject* parent = nullptr)
        : QObject(parent), manager(m) {}

    int getDevice() const { return device; }
    int getVolume() const { return volume; }
    int getNumDevices() { return manager ? manager->numDevices() : 0; }

    void setDevice(int value);
    void setVolume(int value);

    Q_INVOKABLE void select(int newDevice, int newVolume = -1);

    FuseDevice *fuseDevice(isize d) const;
    FuseVolume *fuseVolume(isize d, isize v) const;
    DiskImage *diskImage(isize d) const;

    FuseDevice *currentDevice() const { return fuseDevice(device); }
    FuseVolume *currentVolume() const { return fuseVolume(device, volume); }
    DiskImage *currentImage() const { return diskImage(device); }

    signals:
    void deviceChanged();
    void volumeChanged();
    void numDevicesChanged();

public slots:
    // void addImage(const QUrl &url);
};