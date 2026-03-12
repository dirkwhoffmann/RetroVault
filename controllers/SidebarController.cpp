//
// Created by Dirk Hoffmann on 07.03.26.
//

#include "SidebarController.h"

#include "Model.h"

SidebarController::SidebarController(QObject* parent) : Controller(parent)
{
    m_sidebarModel = new SidebarModel(this);
    m_sidebarModel->controller = this;
}

void
SidebarController::refresh()
{
    m_sidebarModel->refresh();
}

void
SidebarController::select(int d, int v)
{
    model->select(d, v);
}