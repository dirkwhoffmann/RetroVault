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

Item {
    id: root

    // property alias image: imageButton
    property alias imageSource: imageButton.imageSource
    property alias size: imageButton.size
    property alias hovered: imageButton.hovered
    property bool busy: false

    signal clicked()

    implicitWidth: imageButton.width
    implicitHeight: imageButton.height

    ImageButton {
        id: imageButton
        anchors.centerIn: parent
        visible: !root.busy
        onClicked: root.clicked()
    }

    BusyIndicator {
        id: indicator
        anchors.centerIn: parent
        width: root.size
        height: root.size
        visible: root.busy
        running: root.busy
        padding: 2
    }
}
