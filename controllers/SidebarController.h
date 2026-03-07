#pragma once

#include "Controller.h"
#include "SidebarModel.h"

class SidebarController : public Controller
{
    Q_OBJECT

    SidebarModel *m_sidebarModel;

public:

    explicit SidebarController(QObject *parent = nullptr);

    Q_PROPERTY(SidebarModel* sidebarModel READ sidebarModel CONSTANT)

    SidebarModel* sidebarModel() const { return m_sidebarModel; }


    // signals:
    //     void nameChanged();


public slots:

    void refresh();

};
