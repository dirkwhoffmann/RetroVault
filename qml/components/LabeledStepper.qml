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
    id: control
    spacing: 4

    property alias label: titleLabel.text
    property alias value: sb.value
    property alias from: sb.from
    property alias to: sb.to
    property alias stepSize: sb.stepSize
    property alias pointSize: titleLabel.font.pointSize

    Label {
        id: titleLabel
        font.pointSize: Style.small
        color: Style.primary
        Layout.alignment: Qt.AlignHCenter
    }

    SpinBox {
        id: sb
        editable: true
        Layout.preferredWidth: 64
        Layout.alignment: Qt.AlignHCenter
    }
}