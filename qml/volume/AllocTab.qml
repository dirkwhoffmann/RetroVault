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
import RetroVault.Assets
import RetroVault.Controllers

Item {

    id: root
    required property WindowController windowController
    required property VolumePanelController panelController
    required property Scanner scanner

    ColumnLayout {

        anchors.fill: parent
        spacing: 0

        // Row 1

        RowLayout {
            Layout.fillWidth: true
            Layout.bottomMargin: Style.smallSpacing

            ColorBar {
                Layout.fillWidth: true
                Layout.preferredHeight: Style.iconMedium
                rawData: scanner.allocMap
                colors: scanner.strict ? panelController.sallocPanelColors : panelController.allocPanelColors
            }

            BusyButton {
                imageSource: Assets.iconUrl(Assets.Sync)
                size: Style.iconMedium
                onClicked: { scanner.startScan() }
                busy: scanner.isScanning
                MyToolTip {
                    text: qsTr("Scan Image...")
                    visible: parent.hovered && !scanner.isScanning
                }
            }
        }
        // Row 2

        RowLayout {

            Layout.fillWidth: true
            Layout.bottomMargin: Style.tinySpacing

            Slider {
                Layout.fillWidth: true
                from: 0
                value: panelController.block
                to: Math.max(0, panelController.numBlocks - 1)
                stepSize: 1
                snapMode: Slider.SnapAlways
                onMoved: panelController.block = value
            }

            Item {
                Layout.preferredWidth: Style.iconMedium
            }
        }

        // Row 3

        RowLayout {

            Layout.fillWidth: true
            Layout.bottomMargin: Style.tinySpacing

            ColorInfo {

                Layout.fillWidth: true
                Layout.preferredWidth: 164
                color: panelController.okColor
                label: qsTr("Used and Allocated")
            }
            ColorInfo {

                visible: scanner.strict
                Layout.fillWidth: true
                Layout.preferredWidth: 164
                color: panelController.warnColor
                label: qsTr("Unused but Allocated")
            }
            ColorInfo {

                Layout.fillWidth: true
                Layout.preferredWidth: 164
                color: panelController.errorColor
                label: qsTr("Used but Unallocated")
            }

            Spacer {}

            Label {
                text: qsTr("Strict")
            }

            ImageButton {
                size: Style.iconMedium
                icon.source: scanner.strict ? Assets.iconUrl(Assets.Checked) : ""
                onClicked: {
                    scanner.strict = !scanner.strict
                    scanner.startScan()
                }
                MyToolTip {
                    text: qsTr("Toggle detail level")
                }
            }
        }

        // Row 4

        RowLayout {

            Layout.fillWidth: true

            Label {
                text: scanner.allocInfo
            }

            Spacer {}

            Label {
                text: qsTr("Rectify")
            }

            ImageButton {
                size: Style.iconMedium
                icon.source: Assets.iconUrl(Assets.Doctor)
                onClicked: {
                    console.log("Rectify alloc map clicked")
                    panelController.rectifyAllocMap(scanner.strict)
                }
                MyToolTip {
                    text: qsTr("Fix all recoverable errors")
                }
            }
        }
    }

    Spacer {}
}