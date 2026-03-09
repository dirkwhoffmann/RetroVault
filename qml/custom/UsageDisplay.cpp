#include "UsageDisplay.h"
#include <QElapsedTimer>
#include <QtConcurrent>

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

UsageDisplay::UsageDisplay(QQuickItem *parent) : CustomComponent(parent) {

    setAntialiasing(true);

    connect(&m_watcher, &QFutureWatcher<QImage>::finished, this, [this]
    {
        m_cachedImage = m_watcher.result();
        emit isProcessingChanged();
        update();
    });
}

void UsageDisplay::refreshImage()
{
    // Only proceed if no image creation is in progress
    if (m_watcher.isRunning()) return;

    // Only procees if the image has non-zero dimensions
    QSize currentSize(width(), height());
    if (currentSize.isEmpty()) return;

    auto v = fuseVolume(0, 0);

    // Start background thread
    auto future = QtConcurrent::run(&UsageDisplay::generateImageAsync, currentSize, v);
    m_watcher.setFuture(future);
    emit isProcessingChanged();
}

QImage UsageDisplay::generateImageAsync(const QSize &size, FuseVolume *fv) {

    // Note: This code runs in a background thread...

    QElapsedTimer timer;
    timer.start();

    int w = size.width();
    int h = size.height();

    // 1. Heavy backend call
    std::vector<uint8_t> buffer(w);
    fv->createUsageMap(buffer.data(), w); // TODO: GET THE IMAGE FROM THE PROPER DEV AND VOL

    // 2. Generate Image
    QImage image(w, h, QImage::Format_ARGB32);

    for (int x = 0; x < w; ++x) {
        // Ported 'colorize' logic (example using Allocation Map logic)
        QColor baseColor;
        uint8_t val = buffer[x];

        // This switch mimics your 'allocImage' or 'diagnoseImage' logic
        switch (val) {
        case 0:  baseColor = Palette::gray;   break;
        case 1:  baseColor = Palette::green;  break;
        case 2:  baseColor = Palette::yellow; break;
        case 3:  baseColor = Palette::red;    break;
        default: baseColor = Palette::white;  break;
        }

        for (int y = 0; y < h; ++y) {
            // Ported gradient logic: (255 - 2*y)
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

/*
void UsageDisplay::paint(QPainter *painter) {

    printf("paint...\n");
    // Generate the image based on current item size
    QImage img = createUsageImage(QSize(width(), height()));

    if (!img.isNull()) {
        painter->drawImage(0, 0, img);
    }
}
*/

/*
#include "UsageDisplay.h"

void
UsageDisplay::paint(QPainter *painter)  {

    printf("UsageDisplay::paint\n");

    painter->setBrush(QColor("#27ae60"));
    painter->drawRoundedRect(0, 0, width() * 1.0, height(), 5, 5);
}
*/