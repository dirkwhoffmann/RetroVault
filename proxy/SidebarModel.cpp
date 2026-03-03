// -----------------------------------------------------------------------------
// This file is part of RetroVault
//
// Copyright (C) Dirk W. Hoffmann. www.dirkwhoffmann.de
// Licensed under the Mozilla Public License v2
//
// See https://mozilla.org/MPL/2.0 for license information
// -----------------------------------------------------------------------------

#include "SidebarModel.h"
#include "VaultProxy.h"

SidebarModel::SidebarModel(QObject *parent) : QAbstractListModel(parent) {}

int SidebarModel::rowCount(const QModelIndex &parent) const {
    if (parent.isValid()) return 0;
    return m_devices.count();
}

QVariant SidebarModel::data(const QModelIndex &index, int role) const {
    if (!index.isValid() || index.row() >= m_devices.count())
        return QVariant();

    const DeviceData &device = m_devices[index.row()];
    if (role == TitleRole) return device.title;
    if (role == SubtitleRole) return device.subtitle;
    if (role == VolumesRole) return device.volumes;
    if (role == ExpandedRole) return device.expanded;

    return QVariant();
}

QHash<int, QByteArray> SidebarModel::roleNames() const {
    QHash<int, QByteArray> roles;
    roles[TitleRole] = "title";
    roles[SubtitleRole] = "subtitle";
    roles[VolumesRole] = "volumes";
    roles[ExpandedRole] = "expanded";
    return roles;
}

void SidebarModel::toggleExpanded(int index) {
    if (index < 0 || index >= m_devices.count()) return;
    
    m_devices[index].expanded = !m_devices[index].expanded;
    
    // Notify the View to update only this row
    QModelIndex modelIndex = createIndex(index, 0);
    emit dataChanged(modelIndex, modelIndex, {ExpandedRole});
}

void SidebarModel::addDevice(const QString &title, const QString &subtitle, const QStringList &volumes) {
    beginInsertRows(QModelIndex(), m_devices.count(), m_devices.count());
    m_devices.append({title, subtitle, volumes, false});
    endInsertRows();
}

void SidebarModel::refresh(VaultProxy &backend)
{
    // auto &manager = backend.getManager();

    // 1. Tell QML we are about to reset the model entirely
    beginResetModel();

    // 2. Clear internal storage
    m_devices.clear();

    // 3. Loop through your backend functions
    int devCnt = backend.deviceCount();
    for (isize i = 0; i < devCnt; i++) {

        auto info = backend.deviceInfo(i);

        DeviceData dev;
        if (info.size() >= 2) {
            dev.title = info.size() > 0 ? info[0] : "";
            dev.subtitle = info.size() > 1 ? info[1] : "";
        }

        int volCnt = backend.volumeCount(i);
        for (isize j = 0; j < volCnt; j++) {

            auto volInfo = backend.volumeInfo(i, j);
            dev.volumes << volInfo[0];
        }

        m_devices.append(dev);
    }

    // 4. Tell QML the reset is finished
    endResetModel();
}