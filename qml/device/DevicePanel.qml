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
import RetroVault.Assets
import RetroVault.Theme

Item {

    id: root
    required property WindowController windowController

    Connections {
        target: windowController

        function onSelectionChanged() { pc.refresh(); }
    }

    DevicePanelController {

        id: pc
        windowController: root.windowController
    }

    ColumnLayout {

        anchors.fill: parent
        spacing: 0

        Pane {

            background: Rectangle { color: Palette.primaryBg }
            id: headerPane
            Layout.fillWidth: true
            topPadding: Style.largeSpacing
            leftPadding: Style.largeSpacing
            rightPadding: Style.largeSpacing
            bottomPadding: Style.mediumSpacing
            Header {

                id: header
                image.source: windowController.deviceIcon
                title: pc.name
                gridData: pc.deviceInfo
            }
        }

        Pane {

            background: Rectangle { color: Palette.primaryBg }
            id: blockSelectorPane
            Layout.fillWidth: true
            topPadding: Style.mediumSpacing
            leftPadding: Style.largeSpacing
            rightPadding: Style.largeSpacing
            bottomPadding: Style.smallSpacing
            RowLayout {

                anchors.fill: parent
                spacing: 0

                LabeledStepper {
                    label: "Cylinder"
                    enabled: pc.numCylinders > 0
                    from: 0
                    to: Math.max(0, pc.numCylinders - 1)
                    value: pc.cylinder
                    onValueModified: pc.cylinder = value
                }

                Spacer {}

                LabeledStepper {
                    label: "Head"
                    enabled: pc.numHeads > 0
                    from: 0
                    to: Math.max(0, pc.numHeads - 1)
                    value: pc.head
                    onValueModified: pc.head = value
                }

                Spacer {}

                LabeledStepper {
                    label: "Track"
                    enabled: pc.numTracks > 0
                    from: 0
                    to: Math.max(0, pc.numTracks - 1)
                    value: pc.track
                    onValueModified: pc.track = value
                }

                Spacer {}

                LabeledStepper {
                    label: "Sector"
                    enabled: pc.numSectors > 0
                    from: 0
                    to: Math.max(0, pc.numSectors - 1)
                    value: pc.sector
                    onValueModified: pc.sector = value
                }

                Spacer {}

                LabeledStepper {
                    id: blockStepper
                    label: "Block"
                    enabled: pc.numBlocks > 0
                    from: 0
                    to: Math.max(0, pc.numBlocks - 1)
                    value: pc.block
                    onValueModified: pc.block = value
                }
            }
        }

        Pane {

            background: Rectangle { color: Palette.primaryBg }
            id: blockViewPane
            Layout.fillHeight: true
            Layout.fillWidth: true
            topPadding: Style.smallSpacing
            leftPadding: Style.largeSpacing
            rightPadding: Style.largeSpacing
            bottomPadding: Style.largeSpacing
            BlockView {

                id: blockView
                selectable: false
                model: pc.tableModel
            }
        }
    }

    Component.onCompleted: {

        // console.log("DevicePanelController loaded. ");
        pc.refresh()
    }
}
