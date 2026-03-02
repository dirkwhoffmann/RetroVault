// -----------------------------------------------------------------------------
// This file is part of RetroVault
//
// Copyright (C) Dirk W. Hoffmann. www.dirkwhoffmann.de
// Licensed under the Mozilla Public License v2
//
// See https://mozilla.org/MPL/2.0 for license information
// -----------------------------------------------------------------------------

#include "VaultProxy.h"
#include <QQmlEngine>
#include <QQmlContext>

void
VaultProxy::rethrow(std::exception &e)
{
    assert(qmlEngine(this));

    QString errorMsg = QString::fromStdString(e.what());
    printf("%s\n", errorMsg.toStdString().c_str());
    qmlEngine(this)->throwError(errorMsg);
}

void
VaultProxy::add(const QUrl &imageFile)
{
    try {
        printf("proxy::add\n");
        // manager.add(imageFile.toLocalFile().toStdString());
        throw(std::runtime_error("My exception"));
    } catch (std::exception &e) {
        rethrow(e);
    }
}
