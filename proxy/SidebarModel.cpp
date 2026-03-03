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

SidebarModel::SidebarModel(QObject* parent) : QAbstractItemModel(parent)
{
}

QModelIndex SidebarModel::index(int row, int column,
                                const QModelIndex& parent) const
{
    if (!hasIndex(row, column, parent))
        return QModelIndex();

    if (!parent.isValid())
    {
        return createIndex(row, column,
                           const_cast<SidebarItem*>(&m_devices[row]));
    }

    auto* parentItem =
        static_cast<SidebarItem*>(parent.internalPointer());

    return createIndex(row, column,
                       const_cast<SidebarItem*>(
                           &parentItem->children[row]));
}

QModelIndex SidebarModel::parent(const QModelIndex& child) const
{
    if (!child.isValid())
        return QModelIndex();

    auto* childItem =
        static_cast<SidebarItem*>(child.internalPointer());

    for (int i = 0; i < m_devices.size(); ++i)
    {
        const auto& dev = m_devices[i];

        for (int j = 0; j < dev.children.size(); ++j)
        {
            if (&dev.children[j] == childItem)
                return createIndex(i, 0,
                                   const_cast<SidebarItem*>(&m_devices[i]));
        }
    }

    return QModelIndex(); // top level
}

int SidebarModel::rowCount(const QModelIndex& parent) const
{
    if (!parent.isValid())
        return m_devices.size();

    auto* item =
        static_cast<SidebarItem*>(parent.internalPointer());

    return item->children.size();
}

bool SidebarModel::hasChildren(const QModelIndex& parent) const
{
    if (!parent.isValid())
        return !m_devices.isEmpty();

    auto* item =
        static_cast<SidebarItem*>(parent.internalPointer());

    return !item->children.isEmpty();
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

QVariant SidebarModel::data(const QModelIndex& index, int role) const
{
    if (!index.isValid())
        return {};

    auto* item =
        static_cast<SidebarItem*>(index.internalPointer());

    switch (role)
    {
    case TitleRole: return item->title;
    case SubtitleRole: return item->subtitle;
    case IsDeviceRole: return item->type == ItemType::DeviceItem;
    default: return {};
    }
}

void SidebarModel::refresh(VaultProxy& backend)
{
    beginResetModel();
    m_devices.clear();

    int devCnt = backend.deviceCount();

    for (int i = 0; i < devCnt; i++)
    {
        SidebarItem dev;
        dev.type = ItemType::DeviceItem;
        auto info = backend.deviceInfo(i);
        dev.title = info.size() > 0 ? info[0] : "";
        dev.subtitle = info.size() > 1 ? info[1] : "";
        dev.deviceId = i;

        int volCnt = backend.volumeCount(i);

        for (int j = 0; j < volCnt; j++)
        {
            SidebarItem vol;
            vol.type = ItemType::VolumeItem;

            auto volInfo = backend.volumeInfo(i, j);
            vol.title = volInfo.size() > 0 ? volInfo[0] : "";
            vol.subtitle = volInfo.size() > 1 ? volInfo[1] : "";

            dev.children.append(vol);
        }

        m_devices.append(dev);
    }

    endResetModel();
}
