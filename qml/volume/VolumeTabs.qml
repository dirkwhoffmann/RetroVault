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
import retrovaultUI
import RetroVault.Controllers
import RetroVault.Theme

ColumnLayout {

    id: root
    required property WindowController windowController
    required property VolumePanelController panelController
    required property Scanner scanner

    anchors.fill: parent
    spacing: 0 // Style.smallSpacing

    Component.onCompleted: {

        console.log("VolumeTablBar loaded");
        panelController.refresh()
    }

    //
    // Tab bar
    //

    TabBar {
        id: bar
        Layout.bottomMargin: 0 //Style.mediumSpacing
        Layout.alignment: Qt.AlignLeft //  Qt.AlignHCenter
        z: 10

        TabButton {
            text: qsTr("Block Map")
            implicitWidth: 128
            implicitHeight: Style.iconMedium
        }
        TabButton {
            text: qsTr("Allocation Map")
            implicitWidth: 128
            implicitHeight: Style.iconMedium
        }
        TabButton {
            text: qsTr("Diagnose")
            implicitWidth: 128
            implicitHeight: Style.iconMedium
        }
    }

    //
    // Tabs
    //

    Frame {
        Layout.fillWidth: true
        // Layout.fillHeight: true
        Layout.preferredHeight:
            Style.largeSpacing +
            Style.iconMedium + Style.smallSpacing +
            Style.iconSmall + Style.tinySpacing +
            Style.iconMedium + Style.tinySpacing +
            Style.iconMedium + Style.tinySpacing

        topPadding: Style.largeSpacing
        leftPadding: Style.largeSpacing
        rightPadding: Style.largeSpacing
        bottomPadding: Style.mediumSpacing

        background: Rectangle {
            color: Palette.secondaryBg
            border.color: Palette.border
            radius: Style.borderRadius
        }

        StackLayout {
            anchors.fill: parent
            currentIndex: bar.currentIndex

            UsageTab {
                windowController: root.windowController
                panelController: root.panelController
                scanner: volumeScanner
            }
            AllocTab {
                windowController: root.windowController
                panelController: root.panelController
                scanner: volumeScanner
            }
            HealthTab {
                windowController: root.windowController
                panelController: root.panelController
                scanner: volumeScanner
            }
        }
    }
}