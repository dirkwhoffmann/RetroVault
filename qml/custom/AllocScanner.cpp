//
// Created by Dirk Hoffmann on 13.03.26.
//

#include "AllocScanner.h"

void AllocScanner::startScan()
{
    if (auto* fv = controller->currentVolume())
    {
        runTask([fv]()
        {
            QByteArray data(1024, 0);
            fv->createHealthMap((u8*)data.data(), data.size());
            return data;
        });
    }
}