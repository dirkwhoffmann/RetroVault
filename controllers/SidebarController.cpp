//
// Created by Dirk Hoffmann on 07.03.26.
//

#include "SidebarController.h"

SidebarController::SidebarController(QObject* parent) : CustomController(parent)
{
    m_sidebarModel = new SidebarModel(this);
}

void
SidebarController::setNumDevices(int value)
{
    printf("SidebarController::setNumDevices(%d) %p\n", value, getManager());
    numDevices = value;

    if (auto *manager = getManager())
        m_sidebarModel->refresh(*manager);

    emit numDevicesChanged();
    emit sidebarModelChanged();
}

/*
void
SidebarController::refresh()
{
    if (manager)
    {
        m_sidebarModel->refresh(*manager);
    }
}
*/