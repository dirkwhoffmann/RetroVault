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
    void setModel(Model* model) {

        printf("setModel %p\n", model);

        if (m_model != model) {

            m_model = model;
            manager = model->manager;
            emit modelChanged();
        }
    }

    signals:
        void modelChanged();
};