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

ToolButton {

    font.pixelSize: Style.fontSize
    icon.width: Style.iconMedium
    icon.height: Style.iconMedium

    icon.color: {
        if (!enabled) return Style.tertiary // Disabled
        if (down) return Style.primary      // Pressed
        if (hovered) return Style.primary   // Hovered
        return Style.secondary
    }
}