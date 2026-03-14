//
// Created by Dirk Hoffmann on 13.03.26.
//

#include "HealthScanner.h"

void
HealthScanner::startScan()
{
    if (auto* fv = wc ? wc->currentVolume() : nullptr)
    {
        runTask([fv]()
        {
            QByteArray data(1024, 0);
            fv->createHealthMap((u8*)data.data(), data.size());
            return data;
        });
    }
}