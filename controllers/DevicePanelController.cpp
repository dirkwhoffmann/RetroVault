//
// Created by Dirk Hoffmann on 06.03.26.
//

#include "DevicePanelController.h"
#include "QmlAdapterTypes.h"

//
// Table View
//

int
DeviceBlockViewModel::rowCount(const QModelIndex &) const
{
    if (m_dev && controller)
      if (auto *dev = controller->fuseDevice(*m_dev))
            return dev->bsize() / 16;

    return 0;
}

int
DeviceBlockViewModel::columnCount(const QModelIndex &) const
{
    return 18;
}

QVariant
DeviceBlockViewModel::data(const QModelIndex& index, int role) const
{
    auto row = index.row();
    auto col = index.column();

    auto image = controller->fuseDevice(*m_dev)->getImage();

    switch (role)
    {
    case Qt::DisplayRole:
        {
            switch (col)
            {
            case 0:

                return QString::asprintf("%02X", row);

            case 17:
                {
                    QString ascii;
                    ascii.reserve(16);

                    for (int i = 0; i < 16; ++i) {

                        auto offset = *m_blk * image->bsize() + row * 16 + i;
                        unsigned char byte = image->readByte(offset);

                        // isprint() requires <cctype> or <ctype.h>
                        if (isprint(byte)) {
                            ascii.append(QChar(byte));
                        } else {
                            ascii.append('.');
                        }
                    }
                    return ascii;
                }

            default:

                auto offset = (*m_blk) * image->bsize() + row * 16 + (col - 1);
                return QString::asprintf("%02X", image->readByte(offset));
            }
        }
    default:

        return QVariant();
    }
}

void
DeviceBlockViewModel::refresh(int dev, int blk)
{
    m_dev = dev;
    m_blk = blk;

    printf("BlockTableModel::refresh: %d:%d\n", dev, blk);
    beginResetModel();
    endResetModel();
}


//
// Controller
//

void
DevicePanelController::setDevice(int device)
{
    m_device = device;
    refresh();
    emit deviceChanged();
}
void
DevicePanelController::setCylinder(int cylinder)
{
    printf("setCylinder(%d)\n", cylinder);
    m_cylinder = cylinder;
    emit cylinderChanged();
}

void
DevicePanelController::setHead(int head)
{
    m_head = head;
    emit headChanged();
}

void
DevicePanelController::setTrack(int track)
{
    m_track = track;
    emit trackChanged();
}

void
DevicePanelController::setSector(int sector)
{
    m_sector = sector;
    emit sectorChanged();
}

void
DevicePanelController::setBlock(int block)
{
    printf("setBlock %d\n", block);
    if (m_block != block)
    {
        m_block = block;
        emit blockChanged();
        refresh();
    }
}

void
DevicePanelController::refresh()
{
    printf("DevicePanelController::refresh device: %d block: %d\n", m_device, m_block);

    QVariantList list;

    if (auto *device = fuseDevice(m_device))
    {
        auto *image = device->getImage();
        auto &path = image->path;

        auto name = QString::fromStdString(path.string());
        auto numBlocks = int(image->numBlocks());
        auto bsize = int(image->bsize());
        auto numCyls = int(image->numCyls());
        auto numHeads = int(image->numHeads());
        // auto format = DeviceInfo::Format(image->format());

        list << name << "Cylinders:" << numCyls << "     Blocks:" << numBlocks;
        list << "" << "Heads:" << numHeads << "      Block size:" << bsize;
        list << "" << "Sectors:" << "TODO" << "" << "";

        m_tableModel.refresh(m_device, m_block);
    }

    if (m_deviceInfo != list)
    {
        m_deviceInfo = list;
        emit deviceInfoChanged();
    }
}
