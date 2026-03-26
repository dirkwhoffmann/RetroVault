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
import RetroVault.Theme

Item {

    id: root
    required property WindowController windowController

    function offset(row: int, col: int) : int {

        if (row < 0 || col < 1) return -1;
        return (row * 16) + col - 1;
    }

    Connections {
        target: root.windowController
        function onGenerationChanged() { pc.refresh(); }
        function onIsDirtyChanged() { pc.refresh(); }
        function onSelectionChanged() { pc.refresh(); }
    }

    VolumePanelController {

        id: pc
        windowController: root.windowController
    }

    Scanner {

        id: volumeScanner
        windowController: root.windowController
        Component.onCompleted: { startScan(pc.strict) }
    }

    ColumnLayout {

        anchors.fill: parent
        spacing: 0

        Pane {

            id: headerPane
            Layout.fillWidth: true
            topPadding: Style.largeSpacing
            leftPadding: Style.largeSpacing
            rightPadding: Style.largeSpacing
            bottomPadding: Style.mediumSpacing
            Header {

                id: header
                image.source: windowController.volumeIcon
                title: pc.name
                gridData: pc.volumeInfo
            }
        }

        Pane {

            id: tabPane
            Layout.fillWidth: true
            topPadding: Style.mediumSpacing
            leftPadding: Style.largeSpacing
            rightPadding: Style.largeSpacing
            bottomPadding: Style.mediumSpacing
            VolumeTabs {

                id: layoutTab
                windowController: root.windowController
                panelController: pc
                scanner: volumeScanner
            }
        }

        Pane {

            id: blockSelectorPane
            Layout.fillWidth: true
            topPadding: Style.mediumSpacing
            leftPadding: Style.largeSpacing
            rightPadding: Style.largeSpacing
            bottomPadding: Style.smallSpacing
            RowLayout {

                anchors.fill: parent

                LabeledStepper {
                    id: blockStepper
                    label: "Block"
                    enabled: pc.numBlocks > 0
                    to: Math.max(0, pc.numBlocks - 1)
                    value: pc.block
                    pointSize: Style.regular
                    onValueModified: pc.block = value
                }

                Label {
                    id: usageString
                    text: volumeScanner.itemInfo(pc.block, offset(blockView.selectedRow, blockView.selectedColumn))
                    Layout.alignment: Qt.AlignHCenter
                }

                Item {
                    Layout.fillWidth: true
                }

                Label {
                    id: errorString
                    text: volumeScanner.errorInfo(pc.block, offset(blockView.selectedRow, blockView.selectedColumn))
                    color: Palette.error
                    Layout.alignment: Qt.AlignHCenter
                }
            }
        }

        Pane {

            id: blockViewPane
            Layout.fillHeight: true
            Layout.fillWidth: true
            topPadding: Style.smallSpacing
            leftPadding: Style.largeSpacing
            rightPadding: Style.largeSpacing
            bottomPadding: Style.largeSpacing
            BlockView {

                id: blockView
                scanner: volumeScanner
                block: pc.block
                selectable: true
                model: pc.tableModel
            }
        }
    }

    Component.onCompleted: {

        pc.refresh()
    }
}
