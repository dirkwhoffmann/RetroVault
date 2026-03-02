// -----------------------------------------------------------------------------
// This file is part of RetroVault
//
// Copyright (C) Dirk W. Hoffmann. www.dirkwhoffmann.de
// Licensed under the Mozilla Public License v2
//
// See https://mozilla.org/MPL/2.0 for license information
// -----------------------------------------------------------------------------

#pragma once

#include <FuseDevice.h>

using namespace retro::vault;

/* Overview:
 *
 * Three classes participate in binding the file system to the FUSE backend.
 *
 * FuseMountPoint:
 *
 *     Represents a single FUSE file system. It acts as a thin wrapper around
 *     the FUSE C API, connecting application-level code with the FUSE backend.
 *
 * FuseVolume:
 *
 *     A specialized FuseMountPoint that wraps a logical volume and hosts a
 *     file system mounted on that volume.
 *
 * FuseDevice:
 *
 *     Wraps a disk image and manages a collection of FuseVolume instances.
 *
 *    ------------------          ------------------
 *   |    FuseDevice    |        |  FuseMountPoint  |
 *    ------------------          ------------------
 *           < >                          ^
 *            |                           |
 *            |                n  ------------------
 *            -------------------|    FuseVolume    |
 *                                ------------------
 *                                        ^
 *              --------------------------|-------------------------
 *             |                          |                         |
 *    ------------------          ------------------       ------------------
 *   | FuseAmigaVolume  |        |  FuseCBMVolume   |     |        ...       |
 *    ------------------          ------------------       ------------------
 */

class DeviceManager : Loggable {

    // Device database
    std::vector<std::unique_ptr<FuseDevice>> devices;

    // Delegate (message receiver)
    AdapterCallback *callback = nullptr;

    // Payload send to message receiver
    const void *listener = nullptr;


    //
    // Initializing
    //

public:

    DeviceManager();
    ~DeviceManager();

    // Registers a listener together with it's callback function
    void setListener(void *listener, AdapterCallback *func);


    //
    // Querying information
    //

public:

    FuseDevice &getDevice(isize deviceNr);


    //
    // Configuring
    //


    //
    // Adding and removing devices
    //

public:

    // void open(const fs::path &url);
    void add(const fs::path &imageFile);

    void remove(isize deviceNr);
    void removeAll();

    // void save(isize deviceNr);
    // void saveAll();
};
