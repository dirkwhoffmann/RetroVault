#pragma once

#include <QImage>
#include <QFutureWatcher>
#include <qqmlintegration.h>

#include "Model.h"
// #include <qtconcurrentrun.h>

class BaseScanner : public QObject
{
    Q_OBJECT
    QML_ELEMENT
    QML_UNCREATABLE("Abstract base class for all scanners")

    Q_PROPERTY(Model *model READ getModel WRITE setModel NOTIFY modelChanged)
    Q_PROPERTY(QByteArray buffer READ buffer NOTIFY bufferChanged)
    Q_PROPERTY(bool isScanning READ isScanning NOTIFY isScanningChanged)

protected:

    Model *m_model = nullptr;
    QFutureWatcher<QByteArray> m_watcher;
    QByteArray m_buffer;

public:
    explicit BaseScanner(QObject* parent = nullptr);

    Model *getModel() const { return m_model; }
    void setModel(Model *model) { printf("setModel: %p\n", model); m_model = model; emit modelChanged(); }
    QByteArray buffer() const { return m_buffer; }
    bool isScanning() const { return m_watcher.isRunning(); }

    // Scan logic (subclass specific)
    Q_INVOKABLE virtual void startScan() = 0;

signals:
    void modelChanged();
    void bufferChanged();
    void isScanningChanged();

protected:
    void runTask(std::function<QByteArray()> task);

private slots:
    void onScanFinished();
};
