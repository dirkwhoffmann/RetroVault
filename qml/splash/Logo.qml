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
import RetroVault.Theme

GridLayout {

    id: root
    columns: 2
    columnSpacing: 20
    rowSpacing: 20

    // 1. Upper Left: Image
    Image {

        source: "qrc:/assets/images/AppIcon.png"
        Layout.preferredWidth: Style.iconEpic
        Layout.preferredHeight: Style.iconEpic
        Layout.row: 0
        Layout.column: 0
    }

    // 2. Upper Right: Multi-line Text
    ColumnLayout {

        Layout.alignment: Qt.AlignTop // | Qt.AlignLeft
        spacing: 0
        Label {
            text: qsTr("Retro Vault")
            font.pixelSize: 38
            font.family: Fonts.logoFont.name
            font.weight: 700 // Font.Bold
            padding: 0
            topPadding: -5
            bottomPadding: -5
            color: Palette.primary
        }
        Label {
            text: qsTr("Where Sectors Come to Life")
            font.pixelSize: 24
            font.family: Fonts.logoFont.name
            font.weight: 400 // Font.Light
            color: Palette.secondary
            // Layout.alignment: Qt.AlignLeft
        }
        Label {
            // visible: false
            text: qsTr("BETA RELEASE: BACK UP IMAGE FILES BEFORE MOUNTING!")
            font.pixelSize: Style.small
            color: Palette.error
        }
    }

    Rectangle {
        Layout.columnSpan: 2
        Layout.fillWidth: true
        implicitHeight: 1
        color: Palette.tertiary
    }

    // 3. Lower Left: Spacer
    Item { Layout.fillWidth: true }

    // 4. Lower Right: Multi-line Text with different sizes
    ColumnLayout {
        Layout.alignment: Qt.AlignTop | Qt.AlignLeft

        /*
        Label {
            text: qsTr("Drag an image file onto this window to add a file system. ")
            font.pixelSize: 14
            color: Palette.tertiary
        }
         */
        Label {
            text: qsTr("Supported image formats:")
            font.pixelSize: 14
            horizontalAlignment: Text.AlignLeft
            color: Palette.tertiary
            // Layout.topMargin: 25
        }

        GridLayout {

            columns: 2
            rowSpacing: 5
            columnSpacing: 10
            Layout.topMargin: 10

            Label { text: qsTr(".ADF:"); color: Palette.tertiary; font.bold: false }
            Label { text: qsTr("Commodore Amiga Floppy Disk"); color: Palette.tertiary }
            Label { text: qsTr(".D64:"); color: Palette.tertiary; font.bold: false }
            Label { text: qsTr("Commodore 64 Floppy Disk"); color: Palette.tertiary }
        }
    }
}