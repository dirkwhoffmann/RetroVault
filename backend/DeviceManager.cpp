// -----------------------------------------------------------------------------
// This file is part of RetroVault
//
// Copyright (C) Dirk W. Hoffmann. www.dirkwhoffmann.de
// Licensed under the Mozilla Public License v2
//
// See https://mozilla.org/MPL/2.0 for license information
// -----------------------------------------------------------------------------

#include "config.h"
#include "DeviceManager.h"

using namespace retro::vault;

DeviceManager::DeviceManager()
{
    printf("DeviceManager::DeviceManager()\n");
}

DeviceManager::~DeviceManager()
{

}

FuseDevice &
DeviceManager::getDevice(isize deviceNr)
{
    assert(deviceNr >= 0 && deviceNr < devices.size());
    return *devices[deviceNr];
}

void
DeviceManager::add(const fs::path &imageFile)
{
    printf("DeviceManager::add(%s)\n", imageFile.string().c_str());
}

void
DeviceManager::remove(isize deviceNr)
{
    if (deviceNr >= 0 && deviceNr < devices.size())
        devices.erase(devices.begin() + deviceNr);
}
void
DeviceManager::removeAll()
{
    while (!devices.empty()) remove(0);
}