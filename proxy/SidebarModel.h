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

struct DeviceData {

    QString title;
    QString subtitle;
    QStringList volumes;
    bool expanded = false;
};

class SidebarModel : public QAbstractListModel
{
    Q_OBJECT

public:
    enum DeviceRoles {
        TitleRole = Qt::UserRole + 1,
        SubtitleRole,
        VolumesRole,
        ExpandedRole
    };

    explicit SidebarModel(QObject *parent = nullptr);

    // Basic functionality
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QHash<int, QByteArray> roleNames() const override;

    // Expand/Collapse logic
    Q_INVOKABLE void toggleExpanded(int index);

    // Method to add data (called from your backend logic)
    void addDevice(const QString &title, const QString &subtitle, const QStringList &volumes);

    void refresh(class VaultProxy &backend);

private:
    QVector<DeviceData> m_devices;
};
