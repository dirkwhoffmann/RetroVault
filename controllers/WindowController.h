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
    // Model *model = nullptr;
    DeviceManager *manager = nullptr;

    // Current selection
    int device = -1;
    int volume = -1;

public:
    Q_PROPERTY(int device READ getDevice WRITE setDevice NOTIFY deviceChanged)
    Q_PROPERTY(int volume READ getVolume WRITE setVolume NOTIFY volumeChanged)
    Q_PROPERTY(int numDevices READ getNumDevices NOTIFY numDevicesChanged)
    Q_PROPERTY(QString imageFormat READ getImageFormat NOTIFY imageFormatChanged)

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
    QString getImageFormat() const { return diskImageFormat(device); }

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

    FuseDevice *currentDevice() const { return fuseDevice(device); }
    FuseVolume *currentVolume() const { return fuseVolume(device, volume); }
    DiskImage *currentImage() const { return diskImage(device); }
    QString currentImageFormat() const { return diskImageFormat(device); }

    void rethrow(std::exception& e);

    signals:
    void modelChanged();
    void deviceChanged();
    void volumeChanged();
    void selectionChanged();
    void numDevicesChanged();
    void imageFormatChanged();

public slots:
    void addImage(const QUrl &url);
    void select(int newDevice, int newVolume);
};
