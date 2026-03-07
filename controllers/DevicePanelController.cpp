//
// Created by Dirk Hoffmann on 06.03.26.
//

#include "DevicePanelController.h"
#include "QmlAdapterTypes.h"

// DevicePanelController::DevicePanelController() : Controller()

void
DevicePanelController::refresh(int deviceId)
{
    if (deviceId == -1 || !manager) return;

    printf("DevicePanelController::refresh(%d)\n", deviceId);

    auto &device = manager->getDevice(deviceId);
    auto *image = device.getImage();
    auto &path = image->path;

    auto name = QString::fromStdString(path.string());
    auto numBlocks = int(image->numBlocks());
    auto bsize = int(image->bsize());
    auto numCyls = int(image->numCyls());
    auto numHeads = int(image->numHeads());
    // auto format = DeviceInfo::Format(image->format());

    QVariantList list;

    list << name << "Cylinders:" << numCyls << "     Blocks:" << numBlocks;
    list << "" << "Heads:" << numHeads << "      Block size:" << bsize;
    list << "" << "Sectors:" << "TODO" << "" << "";

    // m_blockTableModel.refresh(m_device, m_block);

    if (m_deviceInfo != list)
    {
        m_deviceInfo = list;
        emit deviceInfoChanged();
    }
}
