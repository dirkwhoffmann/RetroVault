//
// Created by Dirk Hoffmann on 06.03.26.
//

#include "Controller.h"
#include <QQmlEngine>

void
Controller::rethrow(std::exception& e)
{
    assert(qmlEngine(this));

    QString errorMsg = QString::fromStdString(e.what());
    printf("%s\n", errorMsg.toStdString().c_str());
    qmlEngine(this)->throwError(errorMsg);
}