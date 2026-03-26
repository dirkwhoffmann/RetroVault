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
import RetroVault.Controllers

Item {

    id: root

    required property SplashPanelController controller
    property bool fuseInstalled: AppController.hasFuse()

    Layout.fillWidth: true
    implicitHeight: content.implicitHeight

    RowLayout {

        id: content
        anchors.fill: parent
        spacing: Style.mediumSpacing

        Image {
            id: ledImage
            source: fuseInstalled
                ? Assets.iconUrl(Assets.LEDGreen)
                : Assets.iconUrl(Assets.LEDRed)
            sourceSize: Qt.size(Style.iconSmall, Style.iconSmall)
        }

        Label {
            text: fuseInstalled
                ? "macFUSE installed"
                : "macFUSE not installed"
        }

        Spacer {}

        Label {
            text: qsTr("v0.9b1")
            font.pixelSize: Style.regular
            // color: Palette.error
        }
        LinkButton {
            imageSource: Assets.iconUrl(Assets.GitHub)
            size: Style.iconMedium
            targetUrl: "https://dirkwhoffmann.github.io/retrovault/"
        }
    }
}
