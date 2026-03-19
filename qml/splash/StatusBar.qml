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

Pane {

    property SplashPanelController controller

    id: root
    anchors.fill: parent
    padding: 0
    background: Rectangle { color: "transparent" }

    contentItem: RowLayout {

        anchors.fill: parent
        spacing: Style.mediumSpacing

        Image {
            id: ledImage
            source: controller.hasFuse() ? Assets.iconUrl(Assets.LEDGreen) : Assets.iconUrl(Assets.LEDRed)
            sourceSize: Qt.size(Style.iconSmall, Style.iconSmall)
        }
        Label {
            text: parent.installed ? "macFUSE installed" : "macFUSE not installed"
        }

        Item {  Layout.fillWidth: true } // Spacer

        LinkButton {
            imageSource: Assets.iconUrl(Assets.GitHub)
            size: Style.iconMedium
            targetUrl: "https://dirkwhoffmann.github.io/retrovault/"
        }
        /*
        IconLink {
            iconSource: Assets.iconUrl(Assets.GitHub)
            targetUrl: "https://dirkwhoffmann.github.io/vAmiga/"
        }
        */
    }
}
