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
#include <QFile>

QmlAdapter::QmlAdapter(QObject* parent) : QObject(parent)
{
    manager.setListener(this, [](void* context, int value)
    {
        auto* self = static_cast<QmlAdapter*>(context);

        printf("In callback handler...\n");
        self->processMsg(value);
    });

    m_sidebarModel = new SidebarModel(this);
    // m_blockTableModel = new BlockTableModel(this);
    m_deviceInfo = new DeviceInfo(this);
}

void
QmlAdapter::processMsg(int value)
{
    static int count = 0;

    printf("processMsg %d\n", count++);

    // refreshSidebar();
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
    QFile file(imageFile.toLocalFile());
    if (!file.open(QIODevice::ReadOnly)) {
        qDebug() << "Error Code:" << file.error();
        qDebug() << "Error String:" << file.errorString();
    }

    try
    {
        printf("proxy::add(%s)\n", imageFile.toLocalFile().toStdString().c_str());
        manager.add(imageFile.toLocalFile().toStdString());
    }
    catch (std::exception& e)
    {
        rethrow(e);
    }
}

DeviceInfo *
QmlAdapter::getDeviceInfo(int deviceNr)
{
    auto &device = manager.getDevice(deviceNr);
    auto *image = device.getImage();
    auto &path = image->path;

    m_deviceInfo->m_name = QString::fromStdString(path.string());
    m_deviceInfo->m_numBlocks = int(image->numBlocks());
    m_deviceInfo->m_bsize = int(image->bsize());
    m_deviceInfo->m_numCyls = int(image->numCyls());
    m_deviceInfo->m_numHeads = int(image->numHeads());
    m_deviceInfo->m_format = DeviceInfo::Format(image->format());

    return m_deviceInfo;
}
