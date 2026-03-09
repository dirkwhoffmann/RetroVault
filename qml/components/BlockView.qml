import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Rectangle {

    property alias model: tableView.model

    anchors.fill: parent

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
        model: model // Backend.blockTableModel
        anchors.left: parent.left
        anchors.top: horizontalHeader.bottom
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        columnSpacing: 1
        rowSpacing: 1
        clip: true

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

            Label {

                anchors.centerIn: parent
                text: display
                font: Style.mono
            }
        }
    }
}
