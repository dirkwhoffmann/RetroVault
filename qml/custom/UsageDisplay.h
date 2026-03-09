#pragma once

#include "CustomComponent.h"
#include <QQuickPaintedItem>
#include <QImage>
#include <QFutureWatcher>
#include <QtConcurrent>

class UsageDisplay : public CustomComponent {

    Q_OBJECT
    QML_ELEMENT

public:

    UsageDisplay(QQuickItem *parent = nullptr);
    void paint(QPainter *painter) override;

    Q_PROPERTY(bool isProcessing READ isProcessing NOTIFY isProcessingChanged)

    // Call this from QML or C++ to start the process
    Q_INVOKABLE void refreshUsage();

    bool isProcessing() const { return m_watcher.isRunning(); }

    signals:
        void isProcessingChanged();

private:
    // Ported Palette
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

private slots:
void onImageReady();

private:
    QImage m_cachedImage;
    QFutureWatcher<QImage> m_watcher;

    // Internal thread-safe generator
    static QImage generateImageAsync(const QSize &size);

    // QImage createUsageImage(const QSize &size);
};