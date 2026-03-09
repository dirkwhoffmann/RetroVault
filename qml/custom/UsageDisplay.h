#pragma once

#include "CustomComponent.h"
#include <QQuickPaintedItem>
#include <QImage>
#include <QFutureWatcher>

class UsageDisplay : public CustomComponent {

    Q_OBJECT
    QML_ELEMENT

    QImage m_cachedImage;
    QFutureWatcher<QImage> m_watcher;

public:

    UsageDisplay(QQuickItem *parent = nullptr);

    // Indicates whether image creation is in progress
    Q_PROPERTY(bool isProcessing READ isProcessing NOTIFY isProcessingChanged)

    // Starts the asynchroneous creation of the displayed image
    Q_INVOKABLE void refreshImage();

private:

    bool isProcessing() const { return m_watcher.isRunning(); }

    struct Palette {
        static QColor white;
        static QColor gray;
        static QColor black;
        static QColor red;
        static QColor orange;
        static QColor yellow;
        static QColor green;
        static QColor dgreen;
        static QColor cyan;
        static QColor blue;
        static QColor purple;
        static QColor pink;

        static QColor getByIndex(int index);
    };

signals:
    void isProcessingChanged();

private slots:
    void onImageReady();

private:

    // Internal paint routine
    void paint(QPainter *painter) override;

    // Internal thread-safe generator
    // static QImage generateImageAsync(const QSize &size, FuseVolume *volume);
    static QImage generateImageAsync(const QSize &size, FuseVolume *fv);
};