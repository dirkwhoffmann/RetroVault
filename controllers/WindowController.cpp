//
// Created by Dirk Hoffmann on 07.03.26.
//

#include "WindowController.h"
#include "FuseDevice.h"
#include "FuseVolume.h"

void
WindowController::setModel(Model *value)
{
    printf("WindowController::setModel(%p) %p", value, value ? value->manager : nullptr);
    if (model != value)
    {
        model = value;
        manager = value->manager;
    }
}

void
WindowController::setDevice(int value)
{
    if (device != value)
    {
        device = value;
        emit deviceChanged();
    }
}

void
WindowController::setVolume(int value)
{
    if (volume != value)
    {
        volume = value;
        emit volumeChanged();
    }
}

void
WindowController::select(int newDevice, int newVolume)
{
    if (device != newDevice || volume != newVolume)
    {
        device = newDevice;
        volume = newVolume;
        emit deviceChanged();
        emit volumeChanged();
    }
}

void
WindowController::addImage(const QUrl &url) {

    QFile file(url.toLocalFile());

    if (!file.open(QIODevice::ReadOnly)) {
        qDebug() << "Error Code:" << file.error();
        qDebug() << "Error String:" << file.errorString();
    }

    try
    {
        printf("addImage(%s)\n", url.toLocalFile().toStdString().c_str());
        manager->add(url.toLocalFile().toStdString());
        m_numDevices = manager->numDevices();
        select(m_numDevices - 1);
        emit numDevicesChanged();
    }
    catch (std::exception& e)
    {
        rethrow(e);
    }
}

FuseDevice *
WindowController::fuseDevice(isize dev) const
{
    if (manager && dev >= 0 && manager->numDevices() > dev)
        return &manager->getDevice(dev);

    return nullptr;
}

FuseVolume *
WindowController::fuseVolume(isize dev, isize vol) const
{
    if (auto d = fuseDevice(dev)) {

        if (vol >= 0 && vol < d->count())
            return &d->getVolume(vol);
    }
    return nullptr;
}

DiskImage *
WindowController::image(isize dev) const
{
    if (auto d = fuseDevice(dev))
        return d->getImage();

    return nullptr;
}
