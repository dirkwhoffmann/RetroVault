// -----------------------------------------------------------------------------
// This file is part of RetroVault
//
// Copyright (C) Dirk W. Hoffmann. www.dirkwhoffmann.de
// Licensed under the Mozilla Public License v2
//
// See https://mozilla.org/MPL/2.0 for license information
// -----------------------------------------------------------------------------

#include "CustomComponent.h"
#include "FuseDevice.h"
#include "FuseVolume.h"
#include <QQmlEngine>

void
CustomComponent::setWC(WindowController* value)
{
    if (wc != value)
    {
        wc = value;
        emit wcChanged();
    }
}

/*
void
CustomComponent::setModel(Model* model)
{
    m_model = model;
    m_manager = model->manager;
}

FuseDevice *
CustomComponent::fuseDevice(isize dev) const
{
    if (m_manager && dev >= 0 && m_manager->numDevices() > dev)
        return &m_manager->getDevice(dev);

    return nullptr;
}

FuseVolume *
CustomComponent::fuseVolume(isize dev, isize vol) const
{
    if (auto d = fuseDevice(dev)) {

        if (vol >= 0 && vol < d->count())
            return &d->getVolume(vol);
    }
    return nullptr;
}

DiskImage *
CustomComponent::image(isize dev) const
{
    if (auto d = fuseDevice(dev))
        return d->getImage();

    return nullptr;
}
*/