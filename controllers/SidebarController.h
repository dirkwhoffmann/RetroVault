#pragma once

#include "CustomController.h"
#include "SidebarModel.h"

class SidebarController : public CustomController
{
    Q_OBJECT

    SidebarModel *m_sidebarModel = nullptr;
    int numDevices = 0;

public:

    explicit SidebarController(QObject *parent = nullptr);

    Q_PROPERTY(SidebarModel* sidebarModel READ sidebarModel NOTIFY sidebarModelChanged)
    Q_PROPERTY(int numDevices READ getNumDevices WRITE setNumDevices NOTIFY numDevicesChanged)

    SidebarModel* sidebarModel() const { return m_sidebarModel; }
    int getNumDevices() const { return numDevices; }
    void setNumDevices(int value);

signals:
    void sidebarModelChanged();
    void numDevicesChanged();

// public slots:

    // void refresh();

};
