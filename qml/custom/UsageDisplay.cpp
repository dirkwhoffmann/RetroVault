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
    auto future = QtConcurrent::run(&UsageDisplay::generateImageAsync, v, currentSize, m_type, m_palette);
    m_watcher.setFuture(future);
    emit isProcessingChanged();
}

QImage
UsageDisplay::generateImageAsync(FuseVolume *fv, const QSize &size, int type, const QList<QColor> &colors) {

    // Note: This code runs in a background thread...

    QElapsedTimer timer;
    timer.start();

    int w = size.width();
    int h = size.height();

    // Generate Image
    QImage image(w, h, QImage::Format_ARGB32);

    // Heavy backend call
    switch (type)
    {
    case 0:
        generateUsageImage(fv, image);
        break;
    case 1:
        generateAllocImage(fv, image);
        break;
    case 2:
        generateCheckImage(fv, image);
        break;
    default:
        fatalError;
    }

    // For debugging: Ensure at least 2000ms have passed
    int64_t elapsed = timer.elapsed();
    if (elapsed < 2000) {
        QThread::msleep(2000 - elapsed);
    }

    return image;
}

void
UsageDisplay::generateUsageImage(FuseVolume *fv, QImage &image)
{
    std::vector<u8> buffer(image.width());
    fv->createUsageMap(buffer.data(), image.width());
    generateImage(image, buffer.data(), [](int val) -> QColor {

        switch (val) {
        case 0:  return QColor("#ffffff"); // white
        case 1:  return QColor("#808080"); // gray
        case 2:  return QColor("#ffb266"); // orange
        case 3:  return QColor("#ff6666"); // red
        case 4:  return QColor("#b266ff"); // purple
        case 5:  return QColor("#ff66ff"); // pink
        case 6:  return QColor("#ffff66"); // yellow
        case 7:  return QColor("#66b2ff"); // blue
        case 8:  return QColor("#009900"); // dgreen
        case 9:  return QColor("#66ff66"); // green
        case 10: return QColor("#66ff66"); // green
        default: return QColor("#000000"); // Fallback
        }
    });
}

void
UsageDisplay::generateAllocImage(FuseVolume *fv, QImage &image)
{
    std::vector<u8> buffer(image.width());
    fv->createAllocationMap(buffer.data(), image.width());
    generateImage(image, buffer.data(), [](int val) -> QColor {

        switch (val) {
        case 0:  return QColor("#808080"); // gray
        case 1:  return QColor("#66ff66"); // green
        case 2:  return QColor("#ffff66"); // yellow
        case 3:  return QColor("#ff6666"); // red
        default: return QColor("#000000"); // Fallback
        }
    });
}

void
UsageDisplay::generateCheckImage(FuseVolume *fv, QImage &image)
{
    std::vector<u8> buffer(image.width());
    fv->createHealthMap(buffer.data(), image.width());
    generateImage(image, buffer.data(), [](int val) -> QColor {

         switch (val) {
         case 0:  return QColor("#808080"); // gray
         case 1:  return QColor("#66ff66"); // green
         case 2:  return QColor("#ff6666"); // red
         default: return QColor("#000000"); // Fallback
         }
     });
}

void
UsageDisplay::generateImage(QImage &image, u8 *data, std::function<QColor(int)> func)
{
    auto w = image.width();
    auto h = image.height();

    for (int x = 0; x < w; ++x) {

        uint8_t val = data[x];
        QColor color = func(val);

        for (int y = 0; y < h; ++y) {

            float factor = qMax(0, 255 - 2 * y) / 255.0f;

            int r = static_cast<int>(color.red()   * factor);
            int g = static_cast<int>(color.green() * factor);
            int b = static_cast<int>(color.blue()  * factor);
            int a = color.alpha();

            image.setPixelColor(x, y, QColor(r, g, b, a));
        }
    }
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
