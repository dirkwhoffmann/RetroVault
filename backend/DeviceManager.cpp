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
DeviceManager::add(const fs::path &imageFile, const fs::path &mountPoint)
{
    printf("DeviceManager::add(%s)\n", imageFile.string().c_str());

    loginfo(FUSE_DEBUG, "Create device...\n");
    auto fd = std::make_unique<FuseDevice>(imageFile);

    printf("Mount file system at %s\n", mountPoint.string().c_str());
    loginfo(FUSE_DEBUG, "Mount file system as /Volumes/%s\n", mountPoint.string().c_str());
    fd->mount(mountPoint);

    loginfo(FUSE_DEBUG, "Adding device to the database...\n");
    devices.push_back(std::move(fd));

    // Inform the GUI
    // if (callback) callback(listener, 42);
}

void
DeviceManager::remove(isize d)
{
    if (d >= 0 && d < devices.size())
        devices.erase(devices.begin() + d);
}

void
DeviceManager::remove(isize d, isize v)
{
    if (d >= 0 && d < devices.size())
    {
        devices[d]->unmount(v);
    }
}

void
DeviceManager::removeAll()
{
    while (!devices.empty()) remove(0);
}

bool
DeviceManager::isDirty(isize d) const
{
    if (d >= 0 && d < devices.size())
        return devices[d]->isDirty();

    return false;
}

bool
DeviceManager::isDirty(isize d, isize v) const
{
    if (d >= 0 && d < devices.size())
        return devices[d]->isDirty(v);

    return false;
}

void
DeviceManager::save(isize d)
{
    if (d >= 0 && d < devices.size())
    {
        devices[d]->save();
    }
}

void DeviceManager::save(isize d, isize v)
{
    if (d >= 0 && d < devices.size())
    {
        devices[d]->save(v);
    }
}

void
DeviceManager::saveAll()
{
    for (auto &device : devices)
    {
        device->save();
    }
}
