#pragma once

#include <QtQml>

class Controller : public QObject {

protected:

    class DeviceManager &manager;

public:
    explicit Controller(DeviceManager &manager, QObject *parent = nullptr)
        : QObject(parent), manager(manager) {}
};