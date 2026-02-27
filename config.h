// -----------------------------------------------------------------------------
// This file is part of vAmiga
//
// Copyright (C) Dirk W. Hoffmann. www.dirkwhoffmann.de
// Licensed under the Mozilla Public License v2
//
// See https://mozilla.org/MPL/2.0 for license information
// -----------------------------------------------------------------------------

#pragma once

#include "debug.h"

//
// Release settings
//

// Version number
static constexpr int VER_MAJOR      = 0;
static constexpr int VER_MINOR      = 1;
static constexpr int VER_SUBMINOR   = 0;
static constexpr int VER_BETA       = 0;

#ifdef NDEBUG
static constexpr bool releaseBuild = 1;
static constexpr bool debugBuild = 0;
#else
static constexpr bool releaseBuild = 0;
static constexpr bool debugBuild = 1;
#endif

#ifdef __APPLE__
static constexpr bool macOS = 1;
#else
static constexpr bool macOS = 0;
#endif

#ifdef __EMSCRIPTEN__
static constexpr bool wasmBuild = 1;
#else
static constexpr bool wasmBuild = 0;
#endif
