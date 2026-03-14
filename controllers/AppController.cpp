//
// Created by Dirk Hoffmann on 14.03.26.
//

#include "AppController.h"

AppController*
AppController::instance() {
    static AppController* inst = new AppController();
    return inst;
}


AppController*
AppController::create(QQmlEngine *qmlEngine, QJSEngine *jsEngine) {
    Q_UNUSED(qmlEngine)
    Q_UNUSED(jsEngine)
    return instance();
}

bool
AppController::hasFuse() const
{
    return false;
}