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

public:

    FuseDevice *fuseDevice(isize d) const;
    FuseVolume *fuseVolume(isize d, isize v) const;
    DiskImage *diskImage(isize d) const;
    QString diskImageFormat(isize d) const;
    QString deviceIcon(isize d) const;
    QString volumeIcon(isize d, isize v) const;

    FuseDevice *currentDevice() const { return fuseDevice(device); }
    FuseVolume *currentVolume() const { return fuseVolume(device, volume); }
    DiskImage *currentImage() const { return diskImage(device); }
    QString currentImageFormat() const { return diskImageFormat(device); }
    QString currentDeviceIcon() const { return deviceIcon(device); }
    QString currentVolumeIcon() const { return volumeIcon(device, volume); }

    signals:
    void modelChanged();
    // void deviceChanged();
    // void volumeChanged();
    void selectionChanged();
    void numDevicesChanged();
    void imageFormatChanged();
    void deviceIconChanged();
    void volumeIconChanged();

public slots:
    void addImage(const QUrl &url);
    // void removeDevice(isize d);
    // void removeVolume(isize d, isize v);
    void remove();

    void select(int newDevice, int newVolume);
};
