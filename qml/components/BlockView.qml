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

Rectangle {

    id: root
    property int block: 0
    property Scanner scanner
    property bool selectable: false
    property alias model: tableView.model
    property alias selectedRow: tableView.selectedRow
    property alias selectedColumn: tableView.selectedColumn

    anchors.fill: parent
    color: Palette.secondaryBg

    HorizontalHeaderView {

        property var columnLabels: [
            "",
            "0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "A", "B", "C", "D", "E", "F",
            "ASCII"
        ]

        id: horizontalHeader
        anchors.left: tableView.left
        anchors.top: parent.top
        syncView: tableView
        model: columnLabels
        clip: true
    }

    TableView {

        id: tableView
        model: model
        anchors.left: parent.left
        anchors.top: horizontalHeader.bottom
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        columnSpacing: 1
        rowSpacing: 1
        clip: true

        property int selectedRow: -1
        property int selectedColumn: -1

        function offset(row: int, col: int) : int {

            if (row < 0 || col < 1) return -1;
            return (row * 16) + col - 1;
        }

        function textColor(blk: int, row: int, col: int) : color {

            if (!scanner) return Palette.primary
            if (row === tableView.selectedRow && col === tableView.selectedColumn)
                return "#ffffff" // Style.highlight
            if (col === 0 || col === tableView.columns - 1)
                return Palette.primary
            return scanner.hasError(blk, offset(row, col)) ? Palette.error : Palette.primary
        }

    /*
    function cellBg(blk: int, row: int, col: int) : color {

        if (!scanner) return Palette.primaryBg
        if (col === 0 || col === tableView.columns - 1)
            return Palette.primaryBg
        return scanner.hasError(blk, offset(row, col)) ? : Palette.error : Palette.primaryBg
    }
    */

    columnWidthProvider: function (column) {

        let n = tableView.columns
        if (n === 0) return 0

        // Calculate total units: (n-1) columns of weight 1 + 1 column of weight 8
        let totalUnits = (n - 1) + 8

        // Subtract spacing from total width to get actual drawable area
        let availableWidth = tableView.width - (tableView.columnSpacing * (n - 1))
        let unitWidth = availableWidth / totalUnits

        if (column < n - 1) {
            return Math.max(16, unitWidth)  // Standard column
        } else {
            return Math.max(100, unitWidth * 8) // The "8x" stretching column
        }
    }

    // Refresh layout whenever the window resizes
    onWidthChanged: tableView.forceLayout()

    ScrollBar.vertical: ScrollBar {

        policy: ScrollBar.AsNeeded
        active: true // Makes it visible when scrolling
    }

    ScrollBar.horizontal: ScrollBar {

        policy: ScrollBar.AsNeeded
        active: true
    }

    delegate: Rectangle {

        implicitHeight: 20

        color: (row === tableView.selectedRow && column === tableView.selectedColumn)
            ? Style.accent
            : "transparent"

        Label {
            id: label
            anchors.centerIn: parent
            text: display
            color: tableView.textColor(block, row, column)
            Binding {
                target: label
                property: "font"
                value: Style.mono
                when: column !== 0
            }
        }

        MouseArea {
            anchors.fill: parent
            enabled: root.selectable
            hoverEnabled: root.selectable

            onClicked: {

                if (column === 0 || column === tableView.columns - 1)
                    return

                if (row == tableView.selectedRow && column == tableView.selectedColumn) {
                    tableView.selectedRow = -1
                    tableView.selectedColumn = -1
                } else {
                    tableView.selectedRow = row
                    tableView.selectedColumn = column
                }
            }

            onEntered: label.opacity = 0.5
            onExited: label.opacity = 1.0
        }
    }
}
}
