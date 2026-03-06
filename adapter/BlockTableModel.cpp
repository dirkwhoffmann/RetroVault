// -----------------------------------------------------------------------------
// This file is part of RetroVault
//
// Copyright (C) Dirk W. Hoffmann. www.dirkwhoffmann.de
// Licensed under the Mozilla Public License v2
//
// See https://mozilla.org/MPL/2.0 for license information
// -----------------------------------------------------------------------------

#include "BlockTableModel.h"
#include "VaultProxy.h"

BlockTableModel::BlockTableModel(QObject* parent) : QAbstractTableModel(parent)
{

}

int
BlockTableModel::rowCount(const QModelIndex &index) const
{
    return 200;
}

int
BlockTableModel::columnCount(const QModelIndex &index) const
{
    return 18;
}

QVariant
BlockTableModel::data(const QModelIndex &index, int role) const
{
    switch (role) {
    case Qt::DisplayRole:
        // return QString::asprintf("%02X", index.column() + index.row());
        return QString::asprintf("%d:%d", dev, blk);
    default:
        break;
    }

    return QVariant();
}

QHash<int, QByteArray>
BlockTableModel::roleNames() const
{
    return { {Qt::DisplayRole, "display"} };
}

void
BlockTableModel::refresh(class VaultProxy &backend, int dev, int blk)
{
    this->dev = dev;
    this->blk = blk;
    printf("BlockTableModel::refresh: %d:%d\n", dev, blk);
    beginResetModel();
    endResetModel();
}