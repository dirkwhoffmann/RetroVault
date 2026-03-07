#pragma once

#include <QtQml>
#include "Model.h"

class Controller : public QObject {

    Q_OBJECT

protected:

    Model *m_model = nullptr;
    DeviceManager *manager = nullptr;

public:

    Q_PROPERTY(Model* model READ model WRITE setModel NOTIFY modelChanged)

    explicit Controller(QObject *parent = nullptr) : QObject(parent) {}

    Model* model() const { return m_model; }
    void setModel(Model* model);

    signals:
        void modelChanged();
};