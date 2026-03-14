//
// Created by Dirk Hoffmann on 13.03.26.
//

#include "ColorBar.h"

ColorBar::ColorBar(QQuickItem *parent) : CustomComponent(parent) {

    printf("ColorBar created\n");
    setAntialiasing(true);

    m_cachedImage = QImage(1024, 24, QImage::Format_ARGB32);
    m_cachedImage.fill(Qt::transparent);
}

void
ColorBar::setRawData(const QByteArray &data) {

    printf("ColorBar::setRawData...\n");
    if (m_rawData != data)
    {
        printf("raw data changed...\n");
        m_rawData = data;
        updateImage();
        update();
    }
}

void
ColorBar::setPalette(const QList<QColor> &palette) {

    printf("ColorBar::setPalette...\n");
    if (m_palette != palette) {

        printf("palette changed...\n");
        m_palette = palette;
        update();
    }
}

void
ColorBar::updateImage()
{
    int w = m_rawData.size();
    int h = 24;

    printf("updateImage... %d %d\n", w, h);
    for (int x = 0; x < w; ++x) {

        uint8_t val = m_rawData[x];
        QColor color = val >= 0 && val < m_palette.size() ? m_palette[val] : QColor();

        for (int y = 0; y < h; ++y) {

            float factor = qMax(0, 255 - 2 * y) / 255.0f;

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