#pragma once

#include "CustomComponent.h"
#include <QQuickPaintedItem>
#include <QImage>
#include <QFutureWatcher>

class UsageDisplay : public CustomComponent {

    Q_OBJECT
    QML_ELEMENT

    QByteArray m_rawData;
    QList<QColor> m_palette;
    int m_type = 0;
    QImage m_cachedImage;
    QFutureWatcher<QImage> m_watcher;

public:

    UsageDisplay(QQuickItem *parent = nullptr);

    // Image data
    Q_PROPERTY(QByteArray rawData READ rawData WRITE setRawData NOTIFY rawDataChanged)

    // The color palette (DEPRECATED)
    Q_PROPERTY(QList<QColor> palette READ palette WRITE setPalette NOTIFY paletteChanged)

    // The image type (0 = block usage, 1 = allocation, 2 = diagnose) (DEPRECATED)
    Q_PROPERTY(int type READ getType WRITE setType NOTIFY typeChanged)

    // Indicates whether image creation is in progress
    Q_PROPERTY(bool isProcessing READ isProcessing NOTIFY isProcessingChanged)

    // Starts the asynchroneous creation of the displayed image
    Q_INVOKABLE void refreshImage();

private:

    QByteArray rawData() const { return m_rawData; }
    void setRawData(const QByteArray &data);

    QList<QColor> palette() const { return m_palette; }
    void setPalette(const QList<QColor> &palette);

    int getType() const { return m_type; }
    void setType(int value) { m_type = value; emit typeChanged(); }

    bool isProcessing() const { return m_watcher.isRunning(); }

signals:
    void rawDataChanged();
    void typeChanged();
    void isProcessingChanged();

private slots:
    void onImageReady();

private:

    // Internal paint routine
    void paint(QPainter *painter) override;

    void geometryChange(const QRectF &newGeometry, const QRectF &oldGeometry) override;

    // Internal thread-safe generator
    static QImage generateImageAsync(FuseVolume *fv, const QSize &size, int type, const QList<QColor> &colors);

    static void generateUsageImage(FuseVolume *fv, QImage &image);
    static void generateAllocImage(FuseVolume *fv, QImage &image);
    static void generateCheckImage(FuseVolume *fv, QImage &image);

    static void generateImage(QImage &image, u8 *data, std::function<QColor(int)> func);

};