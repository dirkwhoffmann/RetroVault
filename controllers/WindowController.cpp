//
// Created by Dirk Hoffmann on 07.03.26.
//

#include "WindowController.h"
#include "FuseDevice.h"
#include "FuseVolume.h"
#include <QFile>
#include <QQmlEngine>

WindowController::WindowController(QObject *parent) : Controller(parent)
{
   manager = new DeviceManager();
}

WindowController::~WindowController()
{
    delete manager;
}

/*
QString
WindowController::getImageFormat() const
{
    if (const auto *img = currentImage())
        return QString::fromStdString(ImageFormatEnum::key(img->format()));

    return "";
}
*/

void
WindowController::setDevice(int value)
{
    if (device != value)
    {
        device = value;
        emit deviceChanged();
        emit selectionChanged();
        emit imageFormatChanged();
    }
}

void
WindowController::setVolume(int value)
{
    if (volume != value)
    {
        volume = value;
        emit volumeChanged();
        emit selectionChanged();
    }
}

void
WindowController::select(int newDevice, int newVolume)
{
    if (device == newDevice && volume == newVolume) return;

    if (device != newDevice)
    {
        device = newDevice;
        emit deviceChanged();
        emit imageFormatChanged();
    }
    if (volume != newVolume)
    {
        volume = newVolume;
        emit volumeChanged();
    }

    emit selectionChanged();
}

FuseDevice *
WindowController::fuseDevice(isize dev) const
{
    if (dev >= 0 && manager->numDevices() > dev)
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
WindowController::diskImage(isize dev) const
{
    if (auto d = fuseDevice(dev))
        return d->getImage();

    return nullptr;
}

QString
WindowController::diskImageFormat(isize d) const
{
   if (auto img = diskImage(d))
       return QString::fromStdString(ImageFormatEnum::key(img->format()));

    return "";
}

void
WindowController::rethrow(std::exception& e)
{
    assert(qmlEngine(this));

    QString errorMsg = QString::fromStdString(e.what());
    printf("%s\n", errorMsg.toStdString().c_str());
    qmlEngine(this)->throwError(errorMsg);
}

void
WindowController::addImage(const QUrl &url) {

    QFile file(url.toLocalFile());

    try
    {
        printf("addImage(%s)\n", url.toLocalFile().toStdString().c_str());
        manager->add(url.toLocalFile().toStdString());
        select(getNumDevices() - 1, -1);
        emit numDevicesChanged();
    }
    catch (std::exception& e)
    {
        rethrow(e);
    }
}
