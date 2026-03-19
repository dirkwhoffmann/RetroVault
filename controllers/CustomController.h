// -----------------------------------------------------------------------------
// This file is part of RetroVault
//
// Copyright (C) Dirk W. Hoffmann. www.dirkwhoffmann.de
// Licensed under the Mozilla Public License v2
//
// See https://mozilla.org/MPL/2.0 for license information
// -----------------------------------------------------------------------------

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
    FuseDevice *fuseDevice(isize d) const { return wc ? wc->fuseDevice(d) : nullptr; }
    FuseVolume *fuseVolume(isize d, isize v) const { return wc ? wc->fuseVolume(d, v) : nullptr; }
    DiskImage *diskImage(isize d) const { return wc ? wc->diskImage(d) : nullptr; }
    QString imageFormat(isize d) const { return wc ? wc->diskImageFormat(d) : QString(); }
    QString deviceIcon(isize d) const { return wc ? wc->deviceIcon(d) : QString(); }
    QString volumeIcon(isize d, isize v) const { return wc ? wc->volumeIcon(d, v) : QString(); }

    FuseDevice *currentDevice() const { return wc ? wc->currentDevice() : nullptr; }
    FuseVolume *currentVolume() const { return wc ? wc->currentVolume() : nullptr; }
    DiskImage *currentImage() const { return wc ? wc->currentImage() : nullptr; }
    QString currentImageFormat() const { return wc ? wc->currentImageFormat() : QString(); }
    QString currentDeviceIcon() const { return wc ? wc->currentDeviceIcon() : QString(); }
    QString currentVolumeIcon() const { return wc ? wc->currentVolumeIcon() : QString(); }

private:
    WindowController* getWC() const { return wc; }
    void setWC(WindowController* value);

signals:
    void wcChanged();
};
