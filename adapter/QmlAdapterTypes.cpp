#include "QmlAdapterTypes.h"
#include "QmlAdapter.h"

//
// Block table
//

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
BlockTableModel::refresh(class QmlAdapter &backend, int dev, int blk)
{
    this->dev = dev;
    this->blk = blk;
    printf("BlockTableModel::refresh: %d:%d\n", dev, blk);
    beginResetModel();
    endResetModel();
}



