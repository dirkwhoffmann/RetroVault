// -----------------------------------------------------------------------------
// This file is part of RetroVault
//
// Copyright (C) Dirk W. Hoffmann. www.dirkwhoffmann.de
// Licensed under the Mozilla Public License v2
//
// See https://mozilla.org/MPL/2.0 for license information
// -----------------------------------------------------------------------------

#include "QmlAdapter.h"
#include <QQmlEngine>
#include <QQmlContext>

QmlAdapter::QmlAdapter(QObject* parent) : QObject(parent)
{
    manager.setListener(this, [](const void* context, int value)
    {
        // 1. Cast to the known type (still const)
        auto* self = static_cast<const QmlAdapter*>(context);

        // 2. Cast away the const-ness to get a mutable pointer
        // auto* self = const_cast<VaultProxy*>(constSelf);

        // Now you can call methods on 'self'
        printf("In callback handler...\n");
        // self->handleCallback(value);
        self->processMsg(value);
    });

    m_sidebarModel = new SidebarModel(this);
    m_blockTableModel = new BlockTableModel(this);
    m_deviceInfo = new DeviceInfo(this);
}

void
QmlAdapter::processMsg(int value) const
{
    static int count = 0;

    printf("processMsg %d\n", count++);
}

void
QmlAdapter::rethrow(std::exception& e)
{
    assert(qmlEngine(this));

    QString errorMsg = QString::fromStdString(e.what());
    printf("%s\n", errorMsg.toStdString().c_str());
    qmlEngine(this)->throwError(errorMsg);
}

void
QmlAdapter::add(const QUrl& imageFile)
{
    try
    {
        printf("proxy::add\n");
        manager.add(imageFile.toLocalFile().toStdString());
    }
    catch (std::exception& e)
    {
        rethrow(e);
    }
}

/*
void
VaultProxy::selectDevice(int deviceNr)
{
    printf("In selectDevice...\n");
    m_deviceInfo->m_name = QString::fromStdString("Waldfee");
    m_deviceInfo->m_numBlocks = deviceNr;
    m_deviceInfo->m_bsize = deviceNr;
    m_deviceInfo->m_numCyls = deviceNr;
    m_deviceInfo->m_numHeads = deviceNr;
    m_deviceInfo->m_format = DeviceInfo::Format::UNKNOWN;

    emit deviceInfoChanged();
}
*/


DeviceInfo *
QmlAdapter::getDeviceInfo(int deviceNr)
{
    m_deviceInfo->m_name = QString::fromStdString("Waldfee");
    m_deviceInfo->m_numBlocks = deviceNr;
    m_deviceInfo->m_bsize = deviceNr;
    m_deviceInfo->m_numCyls = deviceNr;
    m_deviceInfo->m_numHeads = deviceNr;
    m_deviceInfo->m_format = DeviceInfo::Format::UNKNOWN;

    return m_deviceInfo;
}
