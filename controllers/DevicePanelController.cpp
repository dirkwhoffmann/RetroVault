//
// Created by Dirk Hoffmann on 06.03.26.
//

#include "DevicePanelController.h"
#include "QmlAdapterTypes.h"

void
DevicePanelController::refresh(int deviceId)
{
    if (deviceId == -1 || !manager) return;

    // Fetch your pure C++ info (assuming your Manager returns a struct/class)
    // auto info = manager->getDeviceInfo(deviceId);

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

    /*
    list.append(QVariantList{"1", "Cylinders:", "42", "     Blocks:", "some"});
    list.append(QVariantList{"2", "Heads:", "42", "      Block size:", "some"});
    list.append(QVariantList{"3", "Sectors:", "TODO", ""});
    */
    /*
        list.append(QVariantList{info.name, "Cylinders:", info.numCyls, "     Blocks:", info.numBlocks});
        list.append(QVariantList{"", "Heads:", info.numHeads, "      Block size:", info.bsize});
        list.append(QVariantList{"", "Sectors:", "TODO", ""});
*/
    if (m_deviceInfo != list)
    {
        m_deviceInfo = list;
        emit deviceInfoChanged();
    }
}