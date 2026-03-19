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
    bool strict = false;
    QFutureWatcher<ScanResult> watcher;
    QByteArray usageMap;
    QByteArray allocMap;
    QByteArray healthMap;

public:

    Q_PROPERTY(WindowController *windowController READ getWC WRITE setWC NOTIFY wcChanged)
    Q_PROPERTY(int strict READ getStrict WRITE setStrict NOTIFY strictChanged)
    Q_PROPERTY(QByteArray usageMap READ getUsageMap NOTIFY usageMapChanged)
    Q_PROPERTY(QByteArray allocMap READ getAllocMap NOTIFY allocMapChanged)
    Q_PROPERTY(QByteArray healthMap READ getHealthMap NOTIFY healthMapChanged)
    Q_PROPERTY(QString allocInfo READ getAllocInfo NOTIFY allocInfoChanged)
    Q_PROPERTY(QString healthInfo READ getHealthInfo NOTIFY healthInfoChanged)
    Q_PROPERTY(bool isScanning READ isScanning NOTIFY isScanningChanged)

    explicit Scanner(QObject* parent = nullptr);

    WindowController *getWC() const { return wc; }
    void setWC(WindowController *value) { wc = value; emit wcChanged(); }

    FuseVolume *currentVolume() const { return wc ? wc->currentVolume() : nullptr; }

    bool getStrict() const { return strict; }
    QByteArray getUsageMap() const { return usageMap; }
    QByteArray getAllocMap() const { return allocMap; }
    QByteArray getHealthMap() const { return healthMap; }
    QString getAllocInfo() const;
    QString getHealthInfo() const;
    Q_INVOKABLE QString itemInfo(int blk, int row, int col) const;
    Q_INVOKABLE QString errorInfo(int blk, int row, int col) const;
    bool isScanning() const { return watcher.isRunning(); }

    void setStrict(bool value);

    // Scans the current volume
    Q_INVOKABLE virtual void startScan();

signals:
    void wcChanged();
    void strictChanged();
    void usageMapChanged();
    void allocMapChanged();
    void healthMapChanged();
    void allocInfoChanged();
    void healthInfoChanged();
    void isScanningChanged();

protected:
    void runTask(function<ScanResult()> task);

private slots:
    void onScanFinished();
};
