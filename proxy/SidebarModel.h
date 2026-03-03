// -----------------------------------------------------------------------------
// This file is part of RetroVault
//
// Copyright (C) Dirk W. Hoffmann. www.dirkwhoffmann.de
// Licensed under the Mozilla Public License v2
//
// See https://mozilla.org/MPL/2.0 for license information
// -----------------------------------------------------------------------------

#pragma once

#include <QAbstractListModel>
#include <QStringList>
#include <QVector>

// Forward declaration of the backend proxy
class VaultProxy;

enum class ItemType {
    DeviceItem,
    VolumeItem
};

struct SidebarItem {
    ItemType type;
    QString title;
    QString subtitle;
    bool expanded = false;
    int deviceId;
    QVector<SidebarItem> children; // Holds volumes for devices
};

class SidebarModel : public QAbstractListModel
{
    Q_OBJECT

public:
    enum DeviceRoles {
        TitleRole = Qt::UserRole + 1,
        SubtitleRole,
        IsDeviceRole,
        IsExpandedRole
    };

    explicit SidebarModel(QObject *parent = nullptr);

    // QAbstractListModel interface overrides
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QHash<int, QByteArray> roleNames() const override;

    // Logic for the View
    Q_INVOKABLE void toggleExpanded(int index);

    // Business logic to update the data
    void refresh(VaultProxy &backend);

private:
    // This holds the currently visible items (Devices + Expanded Volumes)
    QVector<SidebarItem> m_displayList;
};