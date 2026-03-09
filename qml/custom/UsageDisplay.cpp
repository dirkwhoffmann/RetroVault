#include "UsageDisplay.h"
// #include <QElapsedTimer>
#include <QtConcurrent>

/*
QColor UsageDisplay::Palette::white  = QColor(255, 255, 255);
QColor UsageDisplay::Palette::gray   = QColor(128, 128, 128);
QColor UsageDisplay::Palette::black  = QColor(0, 0, 0);
QColor UsageDisplay::Palette::red    = QColor(0xff, 0x66, 0x66);
QColor UsageDisplay::Palette::orange = QColor(0xff, 0xb2, 0x66);
QColor UsageDisplay::Palette::yellow = QColor(0xff, 0xff, 0x66);
QColor UsageDisplay::Palette::green  = QColor(0x66, 0xff, 0x66);
QColor UsageDisplay::Palette::dgreen = QColor(0x00, 0x99, 0x00);
QColor UsageDisplay::Palette::cyan   = QColor(0x66, 0xff, 0xff);
QColor UsageDisplay::Palette::blue   = QColor(0x66, 0xb2, 0xff);
QColor UsageDisplay::Palette::purple = QColor(0xb2, 0x66, 0xff);
QColor UsageDisplay::Palette::pink   = QColor(0xff, 0x66, 0xff);

QColor UsageDisplay::Palette::getByIndex(int index) {

    static const QColor list[] = { red, orange, yellow, green, dgreen, cyan, blue, purple, pink };
    if (index < 0 || index >= 9) return white;
    return list[index];
}
*/

UsageDisplay::UsageDisplay(QQuickItem *parent) : CustomComponent(parent) {

    setAntialiasing(true);

    connect(&m_watcher, &QFutureWatcher<QImage>::finished, this, [this]
    {
        m_cachedImage = m_watcher.result();
        emit isProcessingChanged();
        update();
    });
}

void
UsageDisplay::setPalette(const QList<QColor> &palette) {

    if (m_palette != palette) {

        m_palette = palette;
        emit paletteChanged();
        update();
    }
}

void
UsageDisplay::refreshImage()
{
    // Only proceed if no image creation is in progress
    if (m_watcher.isRunning()) return;

    // Only procees if the image has non-zero dimensions
    QSize currentSize(width(), height());
    if (currentSize.isEmpty()) return;

    auto v = fuseVolume(0, 0);

    // Start background thread
    auto future = QtConcurrent::run(&UsageDisplay::generateImageAsync, v, currentSize, m_palette);
    m_watcher.setFuture(future);
    emit isProcessingChanged();
}

QImage UsageDisplay::generateImageAsync(FuseVolume *fv, const QSize &size, const QList<QColor> &colors) {

    // Note: This code runs in a background thread...

    QElapsedTimer timer;
    timer.start();

    int w = size.width();
    int h = size.height();

    // Heavy backend call
    std::vector<uint8_t> buffer(w);
    fv->createUsageMap(buffer.data(), w);

    // Generate Image
    QImage image(w, h, QImage::Format_ARGB32);

    for (int x = 0; x < w; ++x) {
        // Ported 'colorize' logic (example using Allocation Map logic)
        QColor baseColor = Qt::white;;
        uint8_t val = buffer[x];

        if (val < colors.size()) {
            baseColor = colors.at(val);
        }

        // This switch mimics your 'allocImage' or 'diagnoseImage' logic

        for (int y = 0; y < h; ++y) {

            float factor = qMax(0, 255 - 2 * y) / 255.0f;

            int r = static_cast<int>(baseColor.red()   * factor);
            int g = static_cast<int>(baseColor.green() * factor);
            int b = static_cast<int>(baseColor.blue()  * factor);
            int a = baseColor.alpha();

            image.setPixelColor(x, y, QColor(r, g, b, a));
        }
    }

    // For debugging: Ensure at least 2000ms have passed
    int64_t elapsed = timer.elapsed();
    if (elapsed < 2000) {
        QThread::msleep(2000 - elapsed);
    }

    return image;
}

// This runs back on the MAIN THREAD
void UsageDisplay::onImageReady() {
    m_cachedImage = m_watcher.result();
    update(); // Triggers paint()
}

void UsageDisplay::paint(QPainter *painter) {

    printf("paint...\n");

    if (m_cachedImage.isNull()) {
        // Optional: Draw a loading state/placeholder
        painter->setPen(Qt::gray);
        painter->drawText(boundingRect(), Qt::AlignCenter, "Loading Map...");
        return;
    }

    painter->drawImage(0, 0, m_cachedImage);
}
