//
// Created by Dirk Hoffmann on 07.03.26.
//

#include "SidebarController.h"

#include "Model.h"

SidebarController::SidebarController(QObject* parent) : Controller(parent)
{
    m_sidebarModel = new SidebarModel(this);
    m_sidebarModel->controller = this;
}

void
SidebarController::refresh()
{
    m_sidebarModel->refresh();
}

void
SidebarController::select(int d, int v)
{
    model->select(d, v);
}

//
// Sidebar model
//

SidebarController::SidebarModel::SidebarModel(QObject* parent) : QAbstractItemModel(parent)
{
}

QModelIndex
SidebarController::SidebarModel::index(int row, int column, const QModelIndex& parent) const
{
    if (!hasIndex(row, column, parent))
        return QModelIndex();

    if (!parent.isValid())
        return createIndex(row, column, &items[row]);

    auto *parentItem = (SidebarItem *)parent.internalPointer();
    return createIndex(row, column, &parentItem->children[row]);
}

QModelIndex
SidebarController::SidebarModel::parent(const QModelIndex& child) const
{
    if (!child.isValid())
        return QModelIndex();

    auto* childItem = (SidebarItem *)child.internalPointer();

    for (int i = 0; i < items.size(); ++i)
    {
        const auto& dev = items[i];

        for (int j = 0; j < dev.children.size(); ++j)
        {
            if (&dev.children[j] == childItem)
                return createIndex(i, 0, &items[i]);
        }
    }

    return QModelIndex(); // Top level
}

int
SidebarController::SidebarModel::rowCount(const QModelIndex& parent) const
{
    if (!parent.isValid())
        return items.size();

    auto *item = (SidebarItem *)parent.internalPointer();
    return item->children.size();
}

bool
SidebarController::SidebarModel::hasChildren(const QModelIndex& parent) const
{
    if (!parent.isValid())
        return !items.isEmpty();

    auto* item = (SidebarItem *)parent.internalPointer();
    return !item->children.isEmpty();
}

QHash<int, QByteArray>
SidebarController::SidebarModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[IconSourceRole] = "iconSource";
    roles[TitleRole] = "title";
    roles[SubtitleRole] = "subtitle";
    roles[DeviceIdRole] = "deviceId";
    roles[VolumeIdRole] = "volumeId";
    roles[IsDeviceRole] = "isDevice";
    return roles;
}

QVariant
SidebarController::SidebarModel::data(const QModelIndex& index, int role) const
{
    if (!index.isValid())
        return {};

    auto *item = (SidebarItem *)index.internalPointer();

    switch (role)
    {
    case IconSourceRole: return item->iconSource;
    case TitleRole: return item->title;
    case SubtitleRole: return item->subtitle;
    case DeviceIdRole: return item->deviceId;
    case VolumeIdRole: return item->volumeId;
    case IsDeviceRole: return item->type == ItemType::DeviceItem;
    default: return {};
    }
}

void
SidebarController::SidebarModel::refresh()
{
    auto *manager = controller->model->manager;

    beginResetModel();
    items.clear();

    int devCnt = manager->numDevices();

    for (int i = 0; i < devCnt; i++)
    {
        auto &device = manager->getDevice(i);
        auto ddescr = device.describe();
        auto filename = device.getImage()->path.filename().string();
        SidebarItem dev;
        dev.type = ItemType::DeviceItem;
        dev.iconSource = "floppy35_dd.png";
        dev.title = QString::fromStdString(filename);
        dev.subtitle = QString::fromStdString(ddescr.size() > 1 ? ddescr[0] : "");
        dev.deviceId = i;
        dev.volumeId = -1;

        int volCnt = device.count();

        for (int j = 0; j < volCnt; j++)
        {
            auto &volume = device.getVolume(i);
            auto vdescr = volume.describe();

            SidebarItem vol;
            vol.type = ItemType::VolumeItem;
            vol.iconSource = "volume_amiga";
            vol.title = QString::fromStdString(vdescr.size() > 0 ? vdescr[0] : "");
            vol.subtitle = QString::fromStdString(vdescr.size() > 1 ? vdescr[1] : "");
            vol.deviceId = i;
            vol.volumeId = j;
            dev.children.append(vol);
        }

        items.append(dev);
    }

    endResetModel();
}