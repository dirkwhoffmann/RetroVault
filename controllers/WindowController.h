#pragma once

#include "Controller.h"

class WindowController : public Controller
{
    Q_OBJECT

public:

    using Controller::Controller;

public slots:

    void addImage(const QUrl &url);
    // Q_INVOKABLE void addDevice(const QUrl &url);
};
