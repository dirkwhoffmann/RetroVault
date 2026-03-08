//
// Created by Dirk Hoffmann on 07.03.26.
//

#include "SidebarController.h"

SidebarController::SidebarController(QObject *parent) : Controller(parent)
{
    m_sidebarModel = new SidebarModel(this);
}

void
SidebarController::refresh()
{
    if (m_manager)
        m_sidebarModel->refresh(*m_manager);
}
