#pragma once

#include "Controller.h"
#include "Model.h"

class WindowController : public Controller
{
    Q_OBJECT

    int m_numDevices = 0; /// ???

    // Current selection
    int device = -1;
    int volume = -1;

protected:

    Model *model = nullptr;
    DeviceManager *manager = nullptr;

public:

    using Controller::Controller;

    Q_PROPERTY(Model* model READ getModel WRITE setModel)
    Q_PROPERTY(int numDevices READ numDevices NOTIFY numDevicesChanged)
    Q_PROPERTY(int device READ getDevice WRITE setDevice NOTIFY deviceChanged)
    Q_PROPERTY(int volume READ getVolume WRITE setVolume NOTIFY volumeChanged)

    //
    // Getter
    //

public:

    Model* getModel() const { return model; }
    DeviceManager* getManager() const { return manager; }

    int numDevices() { return m_numDevices; }
    int getDevice() const { return device; }
    int getVolume() const { return volume; }

    //
    // Setter
    //

    void setModel(Model* value);
    void setDevice(int value);
    void setVolume(int value);

    Q_INVOKABLE void select(int newDevice, int newVolume = -1);

public:

    // Convenience wrappers
    FuseDevice *fuseDevice(isize dev) const;
    FuseVolume *fuseVolume(isize dev, isize vol) const;
    DiskImage *image(isize dev) const;


signals:
    void numDevicesChanged();
    void deviceChanged();
    void volumeChanged();

public slots:
    void addImage(const QUrl &url);
};
