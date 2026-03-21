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
    required property WindowController windowController

    SplashPanelController {

        id: controller
        windowController: root.windowController
    }

    // Background Image
    Image {

        anchors.fill: parent
        source: Assets.iconUrl(Assets.Splash)
        fillMode: Image.PreserveAspectCrop
        opacity: 1.0
        cache: true
    }

    ColumnLayout {
        anchors.fill: parent

        Item {
            Layout.fillWidth: true
            Layout.fillHeight: true
            Logo { anchors.centerIn: parent }
        }

        StatusBar {
            Layout.fillWidth: true
            Layout.margins: Style.mediumSpacing
            controller: controller
        }
    }
}
