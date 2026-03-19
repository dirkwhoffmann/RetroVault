// -----------------------------------------------------------------------------
// This file is part of RetroVault
//
// Copyright (C) Dirk W. Hoffmann. www.dirkwhoffmann.de
// Licensed under the Mozilla Public License v2
//
// See https://mozilla.org/MPL/2.0 for license information
// -----------------------------------------------------------------------------

#pragma once

#include "CustomComponent.h"

class ColorBar : public CustomComponent {

    Q_OBJECT
    QML_ELEMENT

    QByteArray m_rawData;
    QList<QColor> m_palette;
    QImage m_cachedImage;

public:

    ColorBar(QQuickItem *parent = nullptr);

    // Image data
    Q_PROPERTY(QByteArray rawData READ rawData WRITE setRawData)

    // The color palette
    Q_PROPERTY(QList<QColor> palette READ palette WRITE setPalette)

private:

    QByteArray rawData() const { return m_rawData; }
    void setRawData(const QByteArray &data);

    QList<QColor> palette() const { return m_palette; }
    void setPalette(const QList<QColor> &palette);

signals:
    // void rawDataChanged();

private:

    // Update the cached image
    void updateImage();

    // Internal paint routine
    void paint(QPainter *painter) override;

    // Size change handler
    void geometryChange(const QRectF &newGeometry, const QRectF &oldGeometry) override;
};