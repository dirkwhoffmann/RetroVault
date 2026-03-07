#pragma once

#include "Controller.h"

class WindowController : public Controller
{
    Q_OBJECT

    int m_numDevices = 0;

public:

    using Controller::Controller;

    Q_PROPERTY(int numDevices READ numDevices NOTIFY numDevicesChanged)

    int numDevices() { return m_numDevices; }

signals:
    void numDevicesChanged();


public slots:
    void addImage(const QUrl &url);
};
