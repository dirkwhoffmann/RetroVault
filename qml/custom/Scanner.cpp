#include "Scanner.h"
#include <qtconcurrentrun.h>

Scanner::Scanner(QObject* parent) : QObject(parent)
{
    connect(&watcher, &QFutureWatcher<QByteArray>::finished, this, &Scanner::onScanFinished);
}

void
Scanner::startScan(bool strict)
{
    if (auto* fv = wc ? wc->currentVolume() : nullptr)
    {
        runTask([fv, strict]()
        {
            // Record the start time
            auto startTime = std::chrono::steady_clock::now();

            ScanResult result;
            result.usageMap.resize(1024);
            result.allocMap.resize(1024);
            result.healthMap.resize(1024);

            // Perform heavy work
            fv->xray(strict);
            fv->createUsageMap(reinterpret_cast<u8*>(result.usageMap.data()), result.usageMap.size());
            fv->createAllocationMap(reinterpret_cast<u8*>(result.allocMap.data()), result.allocMap.size());
            fv->createHealthMap(reinterpret_cast<u8*>(result.healthMap.data()), result.healthMap.size());

            // Calculate elapsed time
            auto endTime = std::chrono::steady_clock::now();
            auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime);

            // For debugging: Make sure the tasks consumes noticable time
            long long remainingMs = 1500 - elapsed.count();
            if (remainingMs > 0)
                std::this_thread::sleep_for(std::chrono::milliseconds(remainingMs));

            return result;
        });
    }
}

void
Scanner::runTask(std::function<ScanResult()> task)
{
    // Only proceed if no scan is in progress
    if (watcher.isRunning()) return;

    watcher.setFuture(QtConcurrent::run(task));
    emit isScanningChanged();
}

void
Scanner::onScanFinished()
{
    auto result = watcher.result();

    usageMap = result.usageMap;
    allocMap = result.allocMap;
    healthMap = result.healthMap;

    emit usageMapChanged();
    emit allocMapChanged();
    emit healthMapChanged();
    emit isScanningChanged();
}