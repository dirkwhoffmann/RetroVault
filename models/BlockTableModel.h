//
// Created by Dirk Hoffmann on 06.03.26.
//

#pragma once

#include <QtQml>
#include <QAbstractItemModel>

class BlockTableModel : public QAbstractTableModel
{
    Q_OBJECT
    QML_ELEMENT

    class QmlAdapter *backend = nullptr;
    int dev = 0;
    int blk = 0;
    int bsize = 0;

public:

    explicit BlockTableModel(QObject *parent = nullptr);

    int rowCount(const QModelIndex & = QModelIndex()) const override;
    int columnCount(const QModelIndex & = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    QHash<int, QByteArray> roleNames() const override;

    void refresh(QmlAdapter &backend, int dev, int blk);
};
