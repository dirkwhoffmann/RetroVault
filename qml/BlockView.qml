import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import Backend

Rectangle {
    anchors.fill: parent
    // The background color will show through the cell
    // spacing, and therefore become the grid line color.
    // color: Application.styleHints.appearance === Qt.Light ? palette.mid : palette.midlight

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

    /*
    VerticalHeaderView {
        id: verticalHeader
        anchors.top: tableView.top
        anchors.left: parent.left
        syncView: tableView
        clip: true
    }
    */

    TableView {

        id: tableView
        anchors.left: parent.left
        anchors.top: horizontalHeader.bottom
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        clip: true

        columnSpacing: 1
        rowSpacing: 1

        /*
        columnWidthProvider: function(column) {
            return Math.min(24, tableView.width / 20);
        }

        columnWidthProvider: function (column) {

            let totalCols = tableView.columns
            let fixedWidth = 24

            if (column < totalCols - 1) {
                return fixedWidth
            } else {
                // Calculate remaining space:
                // Total Width - (Fixed columns * width) - (any spacing)
                let spentSpace = (totalCols - 1) * (fixedWidth + tableView.columnSpacing)
                let remaining = tableView.width - spentSpace

                // Ensure we don't return a negative number
                return Math.max(100, remaining)
            }
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
                return unitWidth    // Standard column
            } else {
                return unitWidth * 8 // The "8x" stretching column
            }
        }

        // Refresh layout whenever the window resizes
        onWidthChanged: tableView.forceLayout()

        model: Backend.blockTableModel

        delegate: Rectangle {
            // implicitWidth: 100
            implicitHeight: 20

            /*
            Text {
                text: display
            }
            */
            Label {
                anchors.centerIn: parent
                // Format as Hex: 00, FF, etc.
                text: display
                    /*typeof display === "number"
                    ? display.toString(16).toUpperCase().padStart(2, '0')
                    : display */

                font: Style.mono
                // color: column === 0 ? Style.primary : "black"
            }
        }
    }
}

/*

import Qt.labs.qmlmodels // Required for TableModel

Frame {
    id: root
    padding: 1 // 1px border around the table

    // Example input: [ {addr: 0x0, d0: 0xFF...}, {addr: 0x1, d0: 0x00...} ]
    property alias model: tableModel.rows

    // 1. Define the Data Mapping
    TableModel {
        id: tableModel
        TableModelColumn { display: "addr" }
        TableModelColumn { display: "d0" }
        TableModelColumn { display: "d1" }
        TableModelColumn { display: "chk" }
    }

    ColumnLayout {
        anchors.fill: parent
        spacing: 0

        // 2. The Header (Manual row since TableView doesn't include one by default)
        HorizontalHeaderView {
            id: header
            syncView: tableView
            Layout.fillWidth: true
            delegate: Rectangle {
                implicitHeight: 30
                color: Qt.rgba(0,0,0, 0.05)
                border.color: Qt.rgba(0,0,0, 0.1)

                Label {
                    text: modelData // Names from TableModelColumn
                    anchors.centerIn: parent
                    font.pointSize: Style.small
                    font.bold: true
                }
            }
        }

        // 3. The Table Body
        TableView {
            id: tableView
            Layout.fillWidth: true
            Layout.fillHeight: true
            clip: true
            model: tableModel

            // Fixed column widths for hex alignment
            columnWidthProvider: function (column) { return tableView.width / 4; }

            delegate: Rectangle {
                implicitHeight: 32
                color: (row % 2 === 0) ? "transparent" : Qt.rgba(0, 0, 0, 0.02)

                Label {
                    anchors.centerIn: parent
                    // Format as Hex: 00, FF, etc.
                    text: typeof display === "number"
                        ? display.toString(16).toUpperCase().padStart(2, '0')
                        : display

                    font: Style.mono
                    color: column === 0 ? Style.primary : "black"
                }
            }

            ScrollIndicator.vertical: ScrollIndicator { }
        }
    }
}

 */