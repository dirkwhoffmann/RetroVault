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

ToolTip {

    delay: 500
    timeout: 3000
    visible: parent.hovered

    /*
    contentItem: Text {
        text: parent.text
        font.pixelSize: 12
        color: "white"
    }

    background: Rectangle {
        color: "#333333"
        radius: 4
    }
    */
}