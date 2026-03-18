#pragma once

#include "WindowController.h"
#include <QImage>
#include <QFutureWatcher>
#include <qqmlintegration.h>

struct ScanResult {
    QByteArray usageMap;
    QByteArray allocMap;
    QByteArray healthMap;
};

class Scanner : public QObject
{
    Q_OBJECT
    QML_ELEMENT

    WindowController *wc = nullptr;
    QFutureWatcher<ScanResult> watcher;
    QByteArray usageMap;
    QByteArray allocMap;
    QByteArray healthMap;

public:

    Q_PROPERTY(WindowController *windowController READ getWC WRITE setWC NOTIFY wcChanged)
    Q_PROPERTY(QByteArray usageMap READ getUsageMap NOTIFY usageMapChanged)
    Q_PROPERTY(QByteArray allocMap READ getAllocMap NOTIFY allocMapChanged)
    Q_PROPERTY(QByteArray healthMap READ getHealthMap NOTIFY healthMapChanged)
    Q_PROPERTY(bool isScanning READ isScanning NOTIFY isScanningChanged)

    explicit Scanner(QObject* parent = nullptr);

    WindowController *getWC() const { return wc; }
    void setWC(WindowController *value) { wc = value; emit wcChanged(); }

    QByteArray getUsageMap() const { return usageMap; }
    QByteArray getAllocMap() const { return allocMap; }
    QByteArray getHealthMap() const { return healthMap; }
    bool isScanning() const { return watcher.isRunning(); }

    // Scans the current volume
    Q_INVOKABLE virtual void startScan(bool strict);

signals:
    void wcChanged();
    void usageMapChanged();
    void allocMapChanged();
    void healthMapChanged();
    void isScanningChanged();

protected:
    void runTask(std::function<ScanResult()> task);

private slots:
    void onScanFinished();
};
