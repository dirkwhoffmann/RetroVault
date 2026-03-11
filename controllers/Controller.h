#pragma once

#include <QtQml>

class Controller : public QObject {

    Q_OBJECT

public:

    explicit Controller(QObject *parent = nullptr) : QObject(parent) {}

    void rethrow(std::exception& e);
};