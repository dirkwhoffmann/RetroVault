#pragma once
#include "Model.h"
#include <QObject>


class Controller : public QObject {

    Q_OBJECT

public:

    Model *model = nullptr;

    Q_PROPERTY(Model* model READ getModel WRITE setModel NOTIFY modelChanged)

protected:

    explicit Controller(QObject *parent = nullptr) : QObject(parent) {}

public:

    Model* getModel() const { return model; }
    void setModel(Model* value);

    void rethrow(std::exception& e);

signals:
    void modelChanged();
};