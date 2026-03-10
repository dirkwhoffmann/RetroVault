#pragma once

#include "CustomComponent.h"
#include <QQuickPaintedItem>
#include <QImage>
#include <QFutureWatcher>

class UsageDisplay : public CustomComponent {

    Q_OBJECT
    QML_ELEMENT

    QList<QColor> m_palette;
    int m_type = 0;
    QImage m_cachedImage;
    QFutureWatcher<QImage> m_watcher;

public:

    UsageDisplay(QQuickItem *parent = nullptr);

    // The color palette
    Q_PROPERTY(QList<QColor> palette READ palette WRITE setPalette NOTIFY paletteChanged)

    // The image type (0 = block usage, 1 = allocation, 2 = diagnose)
    Q_PROPERTY(int type READ getType WRITE setType NOTIFY typeChanged)

    // Indicates whether image creation is in progress
    Q_PROPERTY(bool isProcessing READ isProcessing NOTIFY isProcessingChanged)

    // Starts the asynchroneous creation of the displayed image
    Q_INVOKABLE void refreshImage();

private:

    QList<QColor> palette() const { return m_palette; }
    void setPalette(const QList<QColor> &palette);

    int getType() const { return m_type; }
    void setType(int value) { m_type = value; emit typeChanged(); }

    bool isProcessing() const { return m_watcher.isRunning(); }

signals:
    void typeChanged();
    void isProcessingChanged();

private slots:
    void onImageReady();

private:

    // Internal paint routine
    void paint(QPainter *painter) override;

    // Internal thread-safe generator
    static QImage generateImageAsync(FuseVolume *fv, const QSize &size, int type, const QList<QColor> &colors);

    static void generateUsageImage(FuseVolume *fv, QImage &image);
    static void generateAllocImage(FuseVolume *fv, QImage &image);
    static void generateCheckImage(FuseVolume *fv, QImage &image);

    static void generateImage(QImage &image, u8 *data, std::function<QColor(int)> func);

};