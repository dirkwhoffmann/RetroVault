#pragma once

#include "Controller.h"

class DevicePanelController : public Controller
{
    Q_OBJECT

    QString m_name = "MY_NAME";
    QVariantList m_deviceInfo;

public:
    // using Controller::Controller;
    DevicePanelController() : Controller()
    {
        printf("DevicePanelController\n");
    }

    Q_PROPERTY(QString name READ name NOTIFY nameChanged)
    Q_PROPERTY(QVariantList deviceInfo READ deviceInfo NOTIFY deviceInfoChanged)

    QString name() const { return m_name; }
    QVariantList deviceInfo() const { return m_deviceInfo; }

signals:
    void nameChanged();
    void deviceInfoChanged();

public slots:
    void refresh(int deviceId);

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
