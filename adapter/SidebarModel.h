// -----------------------------------------------------------------------------
// This file is part of RetroVault
//
// Copyright (C) Dirk W. Hoffmann. www.dirkwhoffmann.de
// Licensed under the Mozilla Public License v2
//
// See https://mozilla.org/MPL/2.0 for license information
// -----------------------------------------------------------------------------

/*
#pragma once

#include <QAbstractListModel>
#include <QVector>

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

public:
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

    void refresh(class QmlAdapter &backend);

private:

    QVector<SidebarItem> m_devices;
};
*/