#pragma once
#include "Model.h"
#include <QObject>


class Controller : public QObject {

    Q_OBJECT

public:
    explicit Controller(QObject *parent = nullptr) : QObject(parent) {}
};