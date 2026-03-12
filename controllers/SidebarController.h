#pragma once

#include "Controller.h"
#include "SidebarModel.h"

class SidebarController : public Controller
{
    Q_OBJECT

    SidebarModel *m_sidebarModel = nullptr;

public:

    explicit SidebarController(QObject *parent = nullptr);
    Q_PROPERTY(SidebarModel* sidebarModel READ sidebarModel NOTIFY sidebarModelChanged)

    SidebarModel* sidebarModel() const { return m_sidebarModel; }

signals:
    void sidebarModelChanged();

public slots:
    void refresh();
    void select(int d, int v);
};
