#pragma once

#include "Controller.h"

class EmulatorController : public Controller
{
    Q_OBJECT

public:

    using Controller::Controller;

public slots:

    void start() {
        printf("start\n");
    }

    void stop() {
        printf("stop\n");
    }

    void reset() {
        printf("reset\n");
    }

};