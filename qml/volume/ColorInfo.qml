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
import QtQuick.Layouts

RowLayout {

    id: root
    spacing: Style.mediumSpacing

    property alias label: textLabel.text
    property alias color: colorBox.color

    Rectangle {
        id: colorBox
        visible: label && label !== ""
        width: 12
        height: 12
        radius: 2
        border.color: Style.tertiary
        border.width: 1
    }

    Label {
        id: textLabel
        Layout.fillWidth: true
        text: "Lorem ipsum"
        font.pointSize: Style.small
        elide: Text.ElideRight
        verticalAlignment: Text.AlignVCenter
    }
}