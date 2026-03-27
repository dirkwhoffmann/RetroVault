// -----------------------------------------------------------------------------
// This file is part of RetroVault
//
// Copyright (C) Dirk W. Hoffmann. www.dirkwhoffmann.de
// Licensed under the Mozilla Public License v2
//
// See https://mozilla.org/MPL/2.0 for license information
// -----------------------------------------------------------------------------

#include "ColorBar.h"

ColorBar::ColorBar(QQuickItem *parent) : CustomComponent(parent)
{

    printf("ColorBar created\n");
    setAntialiasing(true);

    m_cachedImage = QImage(1024, 48, QImage::Format_ARGB32);
    m_cachedImage.fill(Qt::transparent);
}

void
ColorBar::setRawData(const QByteArray &data)
{

    if (m_rawData != data) {
        m_rawData = data;
        updateImage();
        update();
    }
}

void
ColorBar::setColors(const QList<QColor> &colors)
{

    if (m_palette != colors) {

        m_palette = colors;
        update();
    }
}

void
ColorBar::updateImage()
{
    const int w = m_rawData.size();
    const int h = m_cachedImage.height();
    if (w <= 0 || h <= 0) return;

    // Pre-calculate the gradient factors for the column
    QVector<float> factors(h);
    float step = 175.0f / h;
    for (int y = 0; y < h; ++y) {
        factors[y] = qBound(0.0f, (255.0f - step * y) / 255.0f, 1.0f);
    }

    // Process the image
    for (int x = 0; x < w; ++x) {

        uint8_t val = m_rawData[x];

        // Boundary check and color lookup
        QColor baseColor = (val < m_palette.size()) ? m_palette[val] : Qt::black;

        int br = baseColor.red();
        int bg = baseColor.green();
        int bb = baseColor.blue();
        int ba = baseColor.alpha();

        for (int y = 0; y < h; ++y) {
            float f = factors[y];

            QRgb pixel = qRgba(
                static_cast<int>(br * f), static_cast<int>(bg * f), static_cast<int>(bb * f), ba);

            m_cachedImage.setPixel(x, y, pixel);
        }
    }
}

void
ColorBar::paint(QPainter *painter)
{
    if (m_cachedImage.isNull()) return;

    // The target is the actual size of the component in the QML layout
    QRectF targetRect(0, 0, width(), height());

    // The source is our high-res internal buffer
    QRectF sourceRect(0, 0, m_cachedImage.width(), m_cachedImage.height());

    // Enable high-quality downscaling
    painter->setRenderHint(QPainter::SmoothPixmapTransform);
    painter->setRenderHint(QPainter::Antialiasing);

    painter->drawImage(targetRect, m_cachedImage, sourceRect);
}

void
ColorBar::geometryChange(const QRectF &newGeometry, const QRectF &oldGeometry)
{
    QQuickPaintedItem::geometryChange(newGeometry, oldGeometry);

    if (newGeometry.size() != oldGeometry.size()) {
        // Just redraw the existing m_cachedImage at the new scale
        update();
    }
}