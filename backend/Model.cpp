//
// Created by Dirk Hoffmann on 07.03.26.
//

#include "Model.h"
#include <QFile>

void
Model::setDevice(int value)
{
    if (device != value)
    {
        device = value;
        emit deviceChanged();
    }
}

void
Model::setVolume(int value)
{
    if (volume != value)
    {
        volume = value;
        emit volumeChanged();
    }
}

void
Model::select(int newDevice, int newVolume)
{
    if ( device != newDevice || volume != newVolume)
    {
        device = newDevice;
        volume = newVolume;
        emit deviceChanged();
        emit volumeChanged();
    }
}

FuseDevice *
Model::fuseDevice(isize dev) const
{
    if (manager && dev >= 0 && manager->numDevices() > dev)
        return &manager->getDevice(dev);

    return nullptr;
}

FuseVolume *
Model::fuseVolume(isize dev, isize vol) const
{
    if (auto d = fuseDevice(dev)) {

        if (vol >= 0 && vol < d->count())
            return &d->getVolume(vol);
    }
    return nullptr;
}

DiskImage *
Model::diskImage(isize dev) const
{
    if (auto d = fuseDevice(dev))
        return d->getImage();

    return nullptr;
}

/*
void
Model::addImage(const QUrl &url) {

    QFile file(url.toLocalFile());

    try
    {
        printf("addImage(%s)\n", url.toLocalFile().toStdString().c_str());
        manager->add(url.toLocalFile().toStdString());
        select(manager->numDevices() - 1);
        emit numDevicesChanged();
    }
    catch (std::exception& e)
    {
        rethrow(e);
    }
}
*/