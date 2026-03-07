#pragma once

#include "Controller.h"

class SidebarController : public Controller
{
    Q_OBJECT

    // QString m_name = "MY_NAME";

public:

    using Controller::Controller;

    // Q_PROPERTY(QString name READ name NOTIFY nameChanged)

    // QString name() const { return m_name; }

    // signals:
    //     void nameChanged();

    /*
public slots:
    void refresh(int deviceId);

    void foo()
    {

    }
    */
};
