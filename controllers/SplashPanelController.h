#pragma once

#include "Controller.h"

class SplashPanelController : public Controller
{
    Q_OBJECT

public:

    using Controller::Controller;

    Q_INVOKABLE bool hasFuse() const { return false; } // CHANGE BACK ASAP return DeviceManager::hasFuse(); }
};