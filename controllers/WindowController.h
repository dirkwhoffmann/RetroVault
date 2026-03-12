#pragma once

#include "Controller.h"
#include "Model.h"

class WindowController : public Controller
{
    Q_OBJECT

public:

    using Controller::Controller;


    //
    // Getter
    //

public:

    int getNumDevices() { return model ? model->manager->numDevices() : 0; }

signals:
    void numDevicesChanged();

public slots:
    void addImage(const QUrl &url);
};
