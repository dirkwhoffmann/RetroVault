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

GridLayout {

    columns: 2
    columnSpacing: 20
    rowSpacing: 20

    FontLoader {

        id: logoFont
        source: "qrc:/assets/fonts/SourceSans3-VariableFont_wght.ttf"
    }

    // 1. Upper Left: Image
    Image {

        source: "qrc:/assets/images/AppIcon.png"
        Layout.preferredWidth: 100
        Layout.preferredHeight: 100
        Layout.row: 0
        Layout.column: 0
    }

    // 2. Upper Right: Multi-line Text
    ColumnLayout {

        Layout.alignment: Qt.AlignTop // | Qt.AlignLeft
        // spacing: 5
        Label {
            text: "Retro Vault"
            font.pixelSize: 38
            font.family: logoFont.name
            font.weight: 700 // Font.Bold
            // font.bold: true
            color: Style.primary
            Layout.alignment: Qt.AlignLeft
        }
        Label {
            text: "Where Sectors Come to Life"
            font.pixelSize: 24
            // font.bold: false
            font.weight: 300 // Font.Light
            color: Style.secondary
            Layout.alignment: Qt.AlignLeft
        }
    }

    Rectangle {
        Layout.columnSpan: 2
        Layout.fillWidth: true
        height: 1
        color: Style.secondary
        opacity: 1.0
    }

    // 3. Lower Left: (Empty or Spacer)
    Item {
        // Layout.row: 2
        // Layout.column: 0
    }

    // 4. Lower Right: Multi-line Text with different sizes
    ColumnLayout {
        Layout.alignment: Qt.AlignTop | Qt.AlignLeft
        // pacing: 25

        Label {
            text: "Drag an image file onto this window to add a file system. "
            font.pixelSize: 14
            color: Style.tertiary
            Layout.alignment: Qt.AlignLeft
        }
        Label {
            text: "Supported image formats:"
            font.pixelSize: 14
            horizontalAlignment: Text.AlignLeft
            color: Style.tertiary
            Layout.alignment: Qt.AlignLeft
            Layout.topMargin: 25
        }

        GridLayout {
            columns: 2
            rowSpacing: 5
            columnSpacing: 10
            Layout.topMargin: 10

            Label {
                text: ".ADF:"; color: Style.tertiary; font.bold: false
            }
            Label {
                text: "Commodore Amiga Floppy Disk"; color: Style.tertiary
            }
            Label {
                text: ".D64:"; color: Style.tertiary; font.bold: false
            }
            Label {
                text: "Commodore 64 Floppy Disk"; color: Style.tertiary
            }
        }
    }
}