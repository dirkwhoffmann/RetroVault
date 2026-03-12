#pragma once

#include <qqml.h>
#include <QObject>
#include <QString>
#include <QAbstractTableModel>
#include "Controller.h"
#include "DeviceManager.h"

enum ItemType { DeviceItem, VolumeItem };

// Tree node for the sidebar
struct SidebarItem {
    ItemType type;                  // Device or Volume
    QString iconSource;             // Image name
    QString title;                  // Display name
    QString subtitle;               // Optional extra info
    int deviceId;                   // Device number
    int volumeId;                   // Volume number
    QVector<SidebarItem> children;  // Holds volumes for devices

    // Optional: default constructor
    SidebarItem() = default;
};

class SidebarModel : public QAbstractItemModel
{
    Q_OBJECT

    QVector<SidebarItem> m_devices;

public:

    Controller *controller = nullptr;

    enum DeviceRoles {

        IconSourceRole = Qt::UserRole + 1,
        TitleRole,
        SubtitleRole,
        DeviceIdRole,
        VolumeIdRole,
        IsDeviceRole
    };

    explicit SidebarModel(QObject *parent = nullptr);

    QModelIndex index(int row, int column,  const QModelIndex &parent = QModelIndex()) const override;
    QModelIndex parent(const QModelIndex &child) const override;
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &) const override { return 1; }
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QHash<int, QByteArray> roleNames() const override;
    bool hasChildren(const QModelIndex &parent) const override;

    public slots:
    void refresh();
};
