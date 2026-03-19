// -----------------------------------------------------------------------------
// This file is part of RetroVault
//
// Copyright (C) Dirk W. Hoffmann. www.dirkwhoffmann.de
// Licensed under the Mozilla Public License v2
//
// See https://mozilla.org/MPL/2.0 for license information
// -----------------------------------------------------------------------------

#pragma once

#include "CustomController.h"
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

class SidebarController : public CustomController
{
    Q_OBJECT

    class SidebarModel : public QAbstractItemModel
    {
        SidebarController *controller = nullptr;
        QVector<SidebarItem> items;

    public:

        SidebarModel(SidebarController* c) : controller(c)
        {
        }

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

    SidebarModel m_sidebarModel = SidebarModel(this);

public:

    // explicit SidebarController(QObject *parent = nullptr);
    using CustomController::CustomController;

    Q_PROPERTY(SidebarModel* sidebarModel READ getSidebarModel NOTIFY sidebarModelChanged)

    SidebarModel *getSidebarModel() { return &m_sidebarModel; }

signals:
    void sidebarModelChanged();

public slots:
    void refresh();
};
