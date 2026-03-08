//
// Created by Dirk Hoffmann on 06.03.26.
//

#include "Controller.h"
#include "FuseDevice.h"
#include "FuseVolume.h"

void
Controller::setModel(Model* model) {

    qDebug() << "setModel - Old:" << m_model << "New:" << model;

    if (m_model != model) {

        m_model = model;
        m_manager = model->manager;
        emit modelChanged();
    }
}

FuseDevice *
Controller::fuseDevice(isize dev) const
{
    if (m_manager && dev >= 0 && m_manager->numDevices() > dev)
        return &m_manager->getDevice(dev);

    return nullptr;
}

FuseVolume *
Controller::fuseVolume(isize dev, isize vol) const
{
    if (auto d = fuseDevice(dev)) {

        if (vol >= 0 && vol < d->count())
            return &d->getVolume(vol);
    }
    return nullptr;
}
