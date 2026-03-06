// -----------------------------------------------------------------------------
// This file is part of RetroVault
//
// Copyright (C) Dirk W. Hoffmann. www.dirkwhoffmann.de
// Licensed under the Mozilla Public License v2
//
// See https://mozilla.org/MPL/2.0 for license information
// -----------------------------------------------------------------------------

#pragma once

#include <qqml.h>
#include <QAbstractTableModel>

class BlockTableModel : public QAbstractTableModel
{
    Q_OBJECT
    QML_ELEMENT

    int dev = 0;
    int blk = 0;

public:

    explicit BlockTableModel(QObject *parent = nullptr);

    int rowCount(const QModelIndex & = QModelIndex()) const override;
    int columnCount(const QModelIndex & = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    QHash<int, QByteArray> roleNames() const override;

    void refresh(class QmlAdapter &backend, int dev, int blk);
};