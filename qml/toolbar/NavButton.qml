// -----------------------------------------------------------------------------
// This file is part of RetroVault
//
// Copyright (C) Dirk W. Hoffmann. www.dirkwhoffmann.de
// Licensed under the Mozilla Public License v2
//
// See https://mozilla.org/MPL/2.0 for license information
// -----------------------------------------------------------------------------

import QtQuick
import QtQuick.Controls
import RetroVault.Theme

ToolButton {

    font.pixelSize: Style.fontSize
    icon.width: Style.iconMedium
    icon.height: Style.iconMedium

    icon.color: {
        if (!enabled) return Palette.tertiary // Disabled
        if (down) return Palette.primary      // Pressed
        if (hovered) return Palette.primary   // Hovered
        return Palette.secondary
    }
}