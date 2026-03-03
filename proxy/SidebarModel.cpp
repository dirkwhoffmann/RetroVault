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

SidebarModel::SidebarModel(QObject *parent) : QAbstractListModel(parent)
{
}

int SidebarModel::rowCount(const QModelIndex &parent) const
{
    // For a flat list, we only return the count for the root
    if (parent.isValid()) return 0;
    return m_displayList.count();
}

QVariant SidebarModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || index.row() >= m_displayList.count())
        return QVariant();

    const auto &item = m_displayList[index.row()];

    switch (role) {
        case TitleRole:      return item.title;
        case SubtitleRole:   return item.subtitle;
        case IsDeviceRole:   return item.type == ItemType::DeviceItem;
        case IsExpandedRole: return item.expanded;
        default:             return QVariant();
    }
}

QHash<int, QByteArray> SidebarModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[TitleRole] = "title";
    roles[SubtitleRole] = "subtitle";
    roles[IsDeviceRole] = "isDevice";
    roles[IsExpandedRole] = "isExpanded";
    return roles;
}

void SidebarModel::toggleExpanded(int index)
{
    if (index < 0 || index >= m_displayList.count()) return;

    // We only toggle if the item is a Device
    auto &item = m_displayList[index];
    if (item.type != ItemType::DeviceItem) return;

    if (item.expanded) {
        // --- COLLAPSE ---
        int count = item.children.size();
        if (count > 0) {
            beginRemoveRows(QModelIndex(), index + 1, index + count);
            m_displayList.remove(index + 1, count);
            endRemoveRows();
        }
        item.expanded = false;
    } else {
        // --- EXPAND ---
        int count = item.children.size();
        if (count > 0) {
            beginInsertRows(QModelIndex(), index + 1, index + count);
            for (int i = 0; i < count; ++i) {
                // Insert children immediately following the parent Device
                m_displayList.insert(index + 1 + i, item.children[i]);
            }
            endInsertRows();
        }
        item.expanded = true;
    }

    // Notify QML that the Device item's own expanded state role has changed
    emit dataChanged(createIndex(index, 0), createIndex(index, 0), {IsExpandedRole});
}

void SidebarModel::refresh(VaultProxy &backend)
{
    beginResetModel();
    m_displayList.clear();

    int devCnt = backend.deviceCount();
    for (int i = 0; i < devCnt; i++) {
        auto info = backend.deviceInfo(i);

        // Create the Device (Top-level item)
        SidebarItem dev;
        dev.type = ItemType::DeviceItem;
        dev.title = info.size() > 0 ? info[0] : "";
        dev.subtitle = info.size() > 1 ? info[1] : "";
        dev.expanded = false;
        dev.deviceId = i;

        // Populate the children (Volumes) but don't add them to m_displayList yet
        int volCnt = backend.volumeCount(i);
        for (int j = 0; j < volCnt; j++) {
            auto volInfo = backend.volumeInfo(i, j);

            SidebarItem vol;
            vol.type = ItemType::VolumeItem;
            vol.title = volInfo.size() > 0 ? volInfo[0] : "";
            vol.subtitle = volInfo.size() > 1 ? volInfo[1] : "";
            vol.deviceId = i;
            vol.expanded = false;

            dev.children.append(vol);
        }

        // Add only the device to the active display list
        m_displayList.append(dev);
    }

    qDebug() << "Refresh finished. m_displayList size:" << m_displayList.size();

    endResetModel();
}