#pragma once

#include "Controller.h"
#include <QAbstractTableModel>

enum ItemType { DeviceItem, VolumeItem };

struct SidebarItem {

    ItemType type;                  // Device or Volume
    QString iconSource;             // Image name
    QString title;                  // Display name
    QString subtitle;               // Optional extra info
    int deviceId;                   // Device number
    int volumeId;                   // Volume number
    QVector<SidebarItem> children;  // Holds volumes for devices
};

class SidebarController : public Controller
{
    Q_OBJECT

    class SidebarModel : public QAbstractItemModel
    {
        // Q_OBJECT

        QVector<SidebarItem> items;

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

        void refresh();
    };

    SidebarModel *m_sidebarModel = nullptr;

public:

    explicit SidebarController(QObject *parent = nullptr);
    Q_PROPERTY(SidebarModel* sidebarModel READ sidebarModel NOTIFY sidebarModelChanged)

    SidebarModel* sidebarModel() const { return m_sidebarModel; }

signals:
    void sidebarModelChanged();

public slots:
    void refresh();
    void select(int d, int v);
};
