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

VaultProxy::VaultProxy(QObject *parent) : QObject(parent)
{
    manager.setListener(this, [](const void* context, int value) {
        // 1. Cast to the known type (still const)
        auto* constSelf = static_cast<const VaultProxy*>(context);

        // 2. Cast away the const-ness to get a mutable pointer
        auto* self = const_cast<VaultProxy*>(constSelf);

        // Now you can call methods on 'self'
        printf("In callback handler...\n");
        // self->handleCallback(value);
        self->processMsg(QString::fromStdString("HallOO"));
    });
}

/*
void
VaultProxy::processMsg(QString message) const
{
    printf("processMsg\n");
}
*/

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
        manager.add(imageFile.toLocalFile().toStdString());
    } catch (std::exception &e) {
        rethrow(e);
    }
}
