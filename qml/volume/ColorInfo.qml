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
import RetroVault.Theme

RowLayout {

    id: root

    property int spacing: Style.mediumSpacing
    property alias label: textLabel.text
    property alias color: colorBox.color

    implicitHeight: Math.max(12, textLabel.implicitHeight)

    Rectangle {
        id: colorBox
        visible: !!textLabel.text
        Layout.preferredWidth: 12
        Layout.preferredHeight: 12
        Layout.alignment: Qt.AlignVCenter
        radius: 2
        border.color: Palette.tertiary
        border.width: 1
    }

    Label {
        id: textLabel
        Layout.fillWidth: true
        Layout.alignment: Qt.AlignVCenter
        font.pointSize: Style.small
        elide: Text.ElideRight
    }
}