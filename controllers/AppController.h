#pragma once

#include "Controller.h"
#include <QtQml>

class AppController : public Controller
{
    Q_OBJECT

public:

    static AppController* instance();
    static AppController* create(QQmlEngine *qmlEngine, QJSEngine *jsEngine);

    using Controller::Controller;

    Q_INVOKABLE bool hasFuse() const;

    void rethrow(std::exception& e);
};
