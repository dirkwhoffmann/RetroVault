#pragma once

#include <QObject>
#include "DeviceManager.h"

class Model : public QObject {

    Q_OBJECT

public:

    DeviceManager* manager;

    explicit Model(DeviceManager* m, QObject* parent = nullptr)
        : QObject(parent), manager(m) {}
};