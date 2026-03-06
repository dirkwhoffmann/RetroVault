//
// Created by Dirk Hoffmann on 06.03.26.
//

#include "BlockTableModel.h"
#include "QmlAdapter.h"

BlockTableModel::BlockTableModel(QObject* parent) : QAbstractTableModel(parent)
{
}

int
BlockTableModel::rowCount(const QModelIndex& index) const
{
    return bsize / 16;
}

int
BlockTableModel::columnCount(const QModelIndex& index) const
{
    return 18; // Header (1) + Hex (16) + ASCII (1)
}

QVariant
BlockTableModel::data(const QModelIndex& index, int role) const
{
    auto row = index.row();
    auto col = index.column();

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
                    auto image = backend->manager.getDevice(dev).getImage();
                    QString ascii;
                    ascii.reserve(16);

                    for (int i = 0; i < 16; ++i) {

                        auto offset = blk * bsize + row * 16 + i;
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

                auto image = backend->manager.getDevice(dev).getImage();
                auto offset = blk * bsize + row * 16 + (col - 1);
                return QString::asprintf("%02X", image->readByte(offset));
            }
        }
    default:

        return QVariant();
    }
}

QHash<int, QByteArray>
BlockTableModel::roleNames() const
{
    return {{Qt::DisplayRole, "display"}};
}

void
BlockTableModel::refresh(class QmlAdapter& backend, int dev, int blk)
{
    this->backend = &backend;
    this->dev = dev;
    this->blk = blk;
    this->bsize = backend.manager.getDevice(dev).getImage()->bsize();

    printf("BlockTableModel::refresh: %d:%d\n", dev, blk);
    beginResetModel();
    endResetModel();
}
