// -----------------------------------------------------------------------------
// This file is part of RetroVault
//
// Copyright (C) Dirk W. Hoffmann. www.dirkwhoffmann.de
// Licensed under the Mozilla Public License v2
//
// See https://mozilla.org/MPL/2.0 for license information
// -----------------------------------------------------------------------------

import QtQuick
import QtQuick.Layouts
import QtQuick.Controls
import RetroVault.Theme

Pane {

    id: root
    anchors.fill: parent
    padding: 0

    property alias image: image

    property var title
    property var gridData

    contentItem: RowLayout {

        spacing: 15

        Frame {

            Layout.alignment: Qt.AlignTop
            background: Rectangle {
                color: Palette.tertiaryBg
                border.color: Palette.border
                border.width: 2
                radius: 8
            }

            Image {

                id: image
                sourceSize: Qt.size(80, 80)
            }
        }

        GridLayout {

            columns: 5 // root.gridColumns
            Layout.fillWidth: true
            Layout.alignment: Qt.AlignTop
            columnSpacing: 4
            rowSpacing: 4

            // First row: Spans all columns
            Label {

                text: title
                font.pointSize: Style.regular
                font.weight: Style.weightBold
                Layout.columnSpan: 5 // gridColumns
                Layout.fillWidth: true
            }

            // Second row: Separator
            Rectangle {

                height: 1
                color: Palette.border
                Layout.columnSpan: 5 // gridColumns
                Layout.fillWidth: true
                Layout.topMargin: 2
                Layout.bottomMargin: 5
            }

            // All other rows: Custom data
            Repeater {

                model: gridData

                delegate: Label {

                    readonly property int col: index % 5

                    text: modelData
                    font.pointSize: Style.small
                    elide: Text.ElideRight

                    // Logic for styling
                    color: col === 0 ? Palette.primary : Palette.secondary
                    Layout.rightMargin: col === 2 ? 2 * Style.largeSpacing : 0
                    Layout.alignment: Qt.AlignLeft;
                    Layout.fillWidth: col === 0
                }
            }

        }
    }
}
