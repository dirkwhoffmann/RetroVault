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
#include <dlfcn.h>

using namespace retro::vault;

DeviceManager::DeviceManager()
{
    printf("DeviceManager::DeviceManager()\n");
}

DeviceManager::~DeviceManager()
{

}

bool DeviceManager::hasFuse()
{

    if (dlsym(RTLD_DEFAULT, "fuse_mount") || dlsym(RTLD_DEFAULT, "fuse_main"))
        return true;

    // Optional: Check for the standard library path
    /*
    if (fs::exists("/usr/local/lib/libosxfuse.2.dylib") ||
        fs::exists("/usr/local/lib/libfuse.2.dylib")) {
        return true;
        }
    */

    return false;
}

void
DeviceManager::setListener(void *listener, AdapterCallback *callback)
{
    this->listener = listener;
    this->callback = callback;
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

    devices.push_back(std::make_unique<FuseDevice>(imageFile));

    // Inform the GUI
   if (callback) callback(listener, 42);
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