// -----------------------------------------------------------------------------
// This file is part of RetroVault
//
// Copyright (C) Dirk W. Hoffmann. www.dirkwhoffmann.de
// Licensed under the Mozilla Public License v2
//
// See https://mozilla.org/MPL/2.0 for license information
// -----------------------------------------------------------------------------

#include "Scanner.h"
#include <qtconcurrentrun.h>

Scanner::Scanner(QObject *parent) : QObject(parent)
{
    connect(&watcher, &QFutureWatcher<QByteArray>::finished, this, &Scanner::onScanFinished);
}

QString
Scanner::getAllocInfo() const
{
    if (auto *fv = currentVolume()) {

        auto total = fv->usedButUnallocated().size();

        if (strict) total += fv->unusedButAllocated().size();

        if (total > 0) {
            const char *blocks = total == 1 ? "block" : "blocks";
            return QString::asprintf("%ld suspicious %s found", total, blocks);
        }
    }
    return "";
}

QString
Scanner::getHealthInfo() const
{
    if (auto *fv = currentVolume()) {

        auto total = fv->blockErrors().size();

        if (total > 0) {
            const char *blocks = total == 1 ? "block" : "blocks";
            return QString::asprintf("%ld corrupted %s found", total, blocks);
        }
    }
    return "";
}

QString
Scanner::itemInfo(int blk, int offset) const
{
    if (auto *fv = currentVolume()) {

        if (offset >= 0) {
            return QString::fromStdString(fv->typeOf(blk, offset));
        }
        return QString::fromStdString(fv->blockType(blk));
    }
    return "";
}

QString
Scanner::errorInfo(int blk, int offset) const
{
    if (auto *fv = currentVolume()) {

        if (offset >= 0) {

            optional<u8> exp;
            auto err = fv->xray(blk, offset, strict, exp);
            return QString::fromStdString(err);
        }
    }
    return "";
}

bool
Scanner::hasError(int blk, int offset) const
{
    if (auto *fv = currentVolume()) {

        if (offset >= 0) {

            optional<u8> exp;
            return fv->xray8(blk, offset, strict, exp) != 0;
        }
    }
    return false;
}

int
Scanner::expectedValue(int blk, int offset) const
{
    if (auto *fv = currentVolume()) {

        if (offset >= 0) {

            optional<u8> exp;
            (void)fv->xray(blk, offset, strict, exp);
            if (exp) return *exp;
        }
    }
    return -1;
}

void
Scanner::setStrict(bool value)
{
    if (strict != value) {

        strict = value;
        emit strictChanged();
    }
}

void
Scanner::startScan()
{
    if (auto *fv = currentVolume()) {

        runTask([this, fv]() {
            // Record the start time
            auto startTime = std::chrono::steady_clock::now();

            ScanResult result;
            result.usageMap.resize(1024);
            result.allocMap.resize(1024);
            result.healthMap.resize(1024);

            // Perform heavy work
            fv->xray(strict);
            fv->createUsageMap(reinterpret_cast<u8 *>(result.usageMap.data()), result.usageMap.size());
            fv->createAllocationMap(reinterpret_cast<u8 *>(result.allocMap.data()), result.allocMap.size());
            fv->createHealthMap(reinterpret_cast<u8 *>(result.healthMap.data()), result.healthMap.size());

            // Calculate elapsed time
            auto endTime = std::chrono::steady_clock::now();
            auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime);

            // For debugging: Make sure the tasks consumes noticeable time
            long long remainingMs = 1500 - elapsed.count();
            if (remainingMs > 0) std::this_thread::sleep_for(std::chrono::milliseconds(remainingMs));

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

    emit allocInfoChanged();
    emit healthInfoChanged();
    emit usageMapChanged();
    emit allocMapChanged();
    emit healthMapChanged();
    emit isScanningChanged();
}