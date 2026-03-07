#pragma once

#include "Controller.h"

class DevicePanelController : public Controller
{
    Q_OBJECT

    QString m_name = "MY_NAME";

public:

    using Controller::Controller;

    Q_PROPERTY(QString name READ name NOTIFY nameChanged)
    QString name() const { return m_name; }

    /*
    explicit Controller(QObject* parent = nullptr) : QObject(parent)
    {
    }
    */

signals:
    void nameChanged();

public slots:

    void start()
    {
        m_name = QString::fromStdString("Holla, die Waldfee");
        emit nameChanged();
        printf("start\n");
    }

    void stop()
    {
        printf("stop\n");
    }

    void reset()
    {
        printf("reset\n");
    }
};
