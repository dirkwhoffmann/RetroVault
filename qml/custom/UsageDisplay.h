#pragma once

#include "CustomComponent.h"
#include <QQuickPaintedItem>
#include <QImage>
#include <QFutureWatcher>

class UsageDisplay : public CustomComponent {

    Q_OBJECT
    QML_ELEMENT

    QList<QColor> m_palette;
    QImage m_cachedImage;
    QFutureWatcher<QImage> m_watcher;

public:

    UsageDisplay(QQuickItem *parent = nullptr);

    // The color palette
    Q_PROPERTY(QList<QColor> palette READ palette WRITE setPalette NOTIFY paletteChanged)

    // Indicates whether image creation is in progress
    Q_PROPERTY(bool isProcessing READ isProcessing NOTIFY isProcessingChanged)

    // Starts the asynchroneous creation of the displayed image
    Q_INVOKABLE void refreshImage();

private:

    QList<QColor> palette() const { return m_palette; }
    void setPalette(const QList<QColor> &palette);

    bool isProcessing() const { return m_watcher.isRunning(); }

signals:
    void isProcessingChanged();

private slots:
    void onImageReady();

private:

    // Internal paint routine
    void paint(QPainter *painter) override;

    // Internal thread-safe generator
    static QImage generateImageAsync(FuseVolume *fv, const QSize &size, const QList<QColor> &colors);
};