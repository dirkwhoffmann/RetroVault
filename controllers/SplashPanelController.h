#pragma once

#include "CustomController.h"

class SplashPanelController : public CustomController
{
    Q_OBJECT

public:

    using CustomController::CustomController;

    Q_INVOKABLE bool hasFuse() const { return false; } // CHANGE BACK ASAP return DeviceManager::hasFuse(); }
};