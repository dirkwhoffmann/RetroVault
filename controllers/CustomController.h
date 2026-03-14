//
// Created by Dirk Hoffmann on 14.03.26.
//

#pragma once

#include "WindowController.h"

class CustomController : public Controller
{
    Q_OBJECT

protected:
    WindowController* wc = nullptr;

public:

    using Controller::Controller;

    Q_PROPERTY(WindowController* windowController READ getWC WRITE setWC NOTIFY wcChanged)

    // Wrappers
    DeviceManager* manager() const { return wc ? wc->getManager() : nullptr; }
    FuseDevice *fuseDevice(isize dev) const { return wc ? wc->fuseDevice(dev) : nullptr; }
    FuseVolume *fuseVolume(isize dev, isize vol) const { return wc ? wc->fuseVolume(dev, vol) : nullptr; }
    DiskImage *diskImage(isize dev) const { return wc ? wc->diskImage(dev) : nullptr; }
    FuseDevice *currentDevice() const { return wc ? wc->currentDevice() : nullptr; }
    FuseVolume *currentVolume() const { return wc ? wc->currentVolume() : nullptr; }
    DiskImage *currentImage() const { return wc ? wc->currentImage() : nullptr; }
    QString currentImageFormat() const { return wc ? wc->currentImageFormat() : QString(); }
private:
    WindowController* getWC() const { return wc; }
    void setWC(WindowController* value);

signals:
    void wcChanged();
};
