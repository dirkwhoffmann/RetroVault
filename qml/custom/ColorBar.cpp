// -----------------------------------------------------------------------------
// This file is part of RetroVault
//
// Copyright (C) Dirk W. Hoffmann. www.dirkwhoffmann.de
// Licensed under the Mozilla Public License v2
//
// See https://mozilla.org/MPL/2.0 for license information
// -----------------------------------------------------------------------------

#include "ColorBar.h"

ColorBar::ColorBar(QQuickItem *parent) : CustomComponent(parent) {

    printf("ColorBar created\n");
    setAntialiasing(true);

    m_cachedImage = QImage(1024, 48, QImage::Format_ARGB32);
    m_cachedImage.fill(Qt::transparent);
}

void
ColorBar::setRawData(const QByteArray &data) {

    if (m_rawData != data)
    {
        m_rawData = data;
        updateImage();
        update();
    }
}

void
ColorBar::setPalette(const QList<QColor> &palette) {

    if (m_palette != palette) {

        m_palette = palette;
        update();
    }
}

void
ColorBar::updateImage()
{
    int w = m_rawData.size();
    int h = m_cachedImage.height();
    float step = 175.0 / (double)h;

    for (int x = 0; x < w; ++x) {

        uint8_t val = m_rawData[x];
        QColor color = val >= 0 && val < m_palette.size() ? m_palette[val] : QColor();

        for (int y = 0; y < h; ++y) {

            float factor = qMax(0.0f, 255.0 - step * y) / 255.0f;

            int r = static_cast<int>(color.red()   * factor);
            int g = static_cast<int>(color.green() * factor);
            int b = static_cast<int>(color.blue()  * factor);
            int a = color.alpha();

            m_cachedImage.setPixelColor(x, y, QColor(r, g, b, a));
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
ColorBar::geometryChange(const QRectF &newGeometry, const QRectF &oldGeometry) {
    QQuickPaintedItem::geometryChange(newGeometry, oldGeometry);

    if (newGeometry.size() != oldGeometry.size()) {
        // Just redraw the existing m_cachedImage at the new scale
        update();
    }
}