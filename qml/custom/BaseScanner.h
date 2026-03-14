#pragma once

#include "WindowController.h"
#include <QImage>
#include <QFutureWatcher>
#include <qqmlintegration.h>

class BaseScanner : public QObject
{
    Q_OBJECT
    QML_ELEMENT
    QML_UNCREATABLE("Abstract base class for all scanners")

    Q_PROPERTY(WindowController *windowController READ getWC WRITE setWC NOTIFY wcChanged)
    Q_PROPERTY(QByteArray buffer READ buffer NOTIFY bufferChanged)
    Q_PROPERTY(bool isScanning READ isScanning NOTIFY isScanningChanged)

protected:

    WindowController *wc = nullptr;
    QFutureWatcher<QByteArray> m_watcher;
    QByteArray m_buffer;

public:
    explicit BaseScanner(QObject* parent = nullptr);

    WindowController *getWC() const { return wc; }
    void setWC(WindowController *value) { wc = value; emit wcChanged(); }
    QByteArray buffer() const { return m_buffer; }
    bool isScanning() const { return m_watcher.isRunning(); }

    // Scan logic (subclass specific)
    Q_INVOKABLE virtual void startScan() = 0;

signals:
    void wcChanged();
    void bufferChanged();
    void isScanningChanged();

protected:
    void runTask(std::function<QByteArray()> task);

private slots:
    void onScanFinished();
};
