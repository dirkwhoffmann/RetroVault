#pragma once

#include "Controller.h"

class BlockViewController : public Controller
{
    Q_OBJECT

public:

    explicit BlockViewController(QObject *parent = nullptr);

    // Q_PROPERTY(SidebarModel* sidebarModel READ sidebarModel CONSTANT)

    // SidebarModel* sidebarModel() const { return m_sidebarModel; }

    // signals:
    //     void nameChanged();


public slots:

    void refresh();

};
