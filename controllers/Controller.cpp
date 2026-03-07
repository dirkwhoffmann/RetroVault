//
// Created by Dirk Hoffmann on 06.03.26.
//

#include "Controller.h"

void
Controller::setModel(Model* model) {

    qDebug() << "setModel - Old:" << m_model << "New:" << model;

    if (m_model != model) {

        m_model = model;
        manager = model->manager;
        printf("manager %p\n", manager);
        emit modelChanged();
    }
}