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

ToolTip {

    id: root
    delay: 500
    timeout: 3000
    visible: parent.hovered

    contentItem: Text {
        text: root.text
        font.pixelSize: Style.regular
        color: Palette.primary
    }

    background: Rectangle {
        color: Palette.primaryBg
        border.color: Palette.border
        radius: 4
    }
}