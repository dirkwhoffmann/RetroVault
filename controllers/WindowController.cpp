// -----------------------------------------------------------------------------
// This file is part of RetroVault
//
// Copyright (C) Dirk W. Hoffmann. www.dirkwhoffmann.de
// Licensed under the Mozilla Public License v2
//
// See https://mozilla.org/MPL/2.0 for license information
// -----------------------------------------------------------------------------

#include "WindowController.h"
#include "Assets.h"
#include "FuseDevice.h"
#include "FuseVolume.h"
#include <QFile>

WindowController::WindowController(QObject *parent) : Controller(parent) { manager = new DeviceManager(); }

WindowController::~WindowController() { delete manager; }

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
    if (device != value) {
        device = value;
        // emit deviceChanged();
        emit selectionChanged();
        emit imageFormatChanged();
    }
}

void
WindowController::setVolume(int value)
{
    if (volume != value) {
        volume = value;
        // emit volumeChanged();
        emit selectionChanged();
    }
}

void
WindowController::setProtected(bool value)
{
    if (auto *current = currentVolume()) {
        current->writeProtect(value);
        emit isProtectedChanged();
    }
}

void
WindowController::select(int newDevice, int newVolume)
{
    if (device == newDevice && volume == newVolume) return;

    if (device != newDevice) {

        device = newDevice;
        emit imageFormatChanged();
    }

    if (volume != newVolume) {

        volume = newVolume;
    }

    emit selectionChanged();
    printf("Selection changed!!!\n");
}

FuseDevice *
WindowController::fuseDevice(isize dev) const
{
    if (dev >= 0 && manager->numDevices() > dev) return &manager->getDevice(dev);

    return nullptr;
}

FuseVolume *
WindowController::fuseVolume(isize dev, isize vol) const
{
    if (auto d = fuseDevice(dev)) {

        if (vol >= 0 && vol < d->count()) return &d->getVolume(vol);
    }
    return nullptr;
}

DiskImage *
WindowController::diskImage(isize dev) const
{
    if (auto d = fuseDevice(dev)) return d->getImage();

    return nullptr;
}

QString
WindowController::diskImageFormat(isize d) const
{
    if (auto img = diskImage(d)) return QString::fromStdString(ImageFormatEnum::key(img->format()));

    return "";
}

QString
WindowController::deviceIcon(isize d) const
{
    static const std::unordered_map<string, Assets::Icon> formatSuffixes = {
        {"ADF", Assets::Floppy35DD}, {"ADZ", Assets::Floppy35DD}, {"EADF", Assets::Floppy35DD},
        {"DMS", Assets::Floppy35DD}, {"IMG", Assets::Floppy35DD}, {"ST", Assets::Floppy35DD},
        {"D64", Assets::Floppy525DD}};

    auto url = QString();
    if (auto it = formatSuffixes.find(diskImageFormat(d).toStdString()); it != formatSuffixes.end()) {
        return Assets::getIconUrl(it->second).toString();
    }
    return "";
}

QString
WindowController::volumeIcon(isize d, isize v) const
{
    static const std::unordered_map<string, Assets::Icon> formatSuffixes = {
        {"ADF", Assets::VolumeAmiga}, {"ADZ", Assets::VolumeAmiga}, {"EADF", Assets::VolumeAmiga},
        {"DMS", Assets::VolumeAmiga}, {"IMG", Assets::VolumeDOS},   {"ST", Assets::VolumeST},
        {"D64", Assets::VolumeCBM}};

    auto url = QString();

    if (auto it = formatSuffixes.find(diskImageFormat(d).toStdString()); it != formatSuffixes.end())
        return Assets::getIconUrl(it->second).toString();

    return "";
}

bool
WindowController::writeProtection(isize d, isize v) const
{
    if (auto *volume = fuseVolume(d, v)) {
        return volume->isWriteProtected();
    }
    return false;
}

QString
WindowController::currentMountPoint() const
{
    if (auto *v = currentVolume()) return QString::fromStdString(v->getMountPoint().string());

    return "";
}

void
WindowController::addImage(const QUrl &url)
{

    QFile file(url.toLocalFile());

    try {
        printf("addImage(%s)\n", url.toLocalFile().toStdString().c_str());
        manager->add(url.toLocalFile().toStdString());
        select(getNumDevices() - 1, -1);
        emit numDevicesChanged();
    } catch (std::exception &e) {
        rethrow(e);
    }
}

void
WindowController::remove()
{

    try {
        if (volume == -1) {
            manager->remove(device);
        } else {
            manager->remove(device, volume);
        }
        device = -1;
        volume = -1;
    } catch (std::exception &e) {
        rethrow(e);
    }

    emit numDevicesChanged();
    emit selectionChanged();
}

void
WindowController::save()
{
    try {
        if (volume == -1) {
            manager->save(device);
        } else {
            manager->save(device, volume);
        }
    } catch (std::exception &e) {
        rethrow(e);
    }
}

void
WindowController::periodicRefresh()
{
    printf("periodicRefresh()\n");

    if (isDirty != manager->isDirty(device, volume)) {

        isDirty = !isDirty;
        emit isDirtyChanged();
    }

    if (auto *fv = currentVolume()) {

        auto stat = fv->stat();

        if (stat.generation != generation) {

            generation = stat.generation;
            emit generationChanged();
        }
    }
}