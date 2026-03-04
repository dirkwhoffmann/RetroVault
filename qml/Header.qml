import QtQuick
import QtQuick.Layouts
import QtQuick.Controls

Pane {
    id: root
    anchors.fill: parent
    padding: 24

    // Expects a 2D array: [ ["Key", "Val", "Key", "Val"], ["Key", "Val", "..."] ]
    property var gridData: []

    /*
    readonly property var transposedData: {
        if (!gridData || gridData.length === 0 || !gridData[0]) return [];
        return gridData[0].map((_, i) => gridData.map(col => col[i]));
    }
    */

    readonly property int gridColumns: gridData.length > 0 ? gridData[0].length : 1
    // readonly property int gridRows: gridData.length > 0 ?  gridData[0].length : 1
    // readonly property int gridColumns: gridData.length

    contentItem: RowLayout {
        spacing: 15

        Image {
            source: "../assets/images/floppy35_dd.png"
            sourceSize: Qt.size(80, 80)
            Layout.alignment: Qt.AlignTop
        }

        GridLayout {

            columns: root.gridColumns
            Layout.fillWidth: true
            columnSpacing: 4
            rowSpacing: 4

            // First row: Spans all columns
            Label {

                text: "/Home/Users/My very great image.adf"
                font.pointSize: Style.regular
                font.weight: Style.weightBold
                Layout.columnSpan: gridColumns
                Layout.fillWidth: true
            }

            // Second row: Separator
            Rectangle {

                height: 1
                color: "#cccccc"
                Layout.columnSpan: gridColumns
                Layout.fillWidth: true
                Layout.topMargin: 2
                Layout.bottomMargin: 5
            }

            // All other rows: Custom data
            Repeater {

                model: root.gridData.reduce((acc, val) => acc.concat(val), [])

                delegate: Label {

                    readonly property int col: index % gridColumns

                    text: modelData //  + (col % 2 === 1 ? ":" : "")
                    font.pointSize: Style.small
                    elide: Text.ElideRight
                    color: col === 0 ? "#000" : "#666"
                    Layout.alignment: Qt.AlignLeft // col % 2 === 1 ? Qt.AlignRight : Qt.AlignLeft
                    Layout.fillWidth: col === 0 // index % 2 !== 1
                }
            }
        }
    }
}
/*
Pane {
    // id: root
    anchors.fill: parent
    padding: 24

    background: Rectangle { color: "red" }


    RowLayout {
        anchors.fill: parent
        spacing: 15

        // 1. Fixed Size Image on the Left
        Image {
            id: headerIcon
            source: "../assets/images/floppy35_dd.png"
            sourceSize: Qt.size(80, 80)
            Layout.preferredWidth: 80
            Layout.preferredHeight: 80
            fillMode: Image.PreserveAspectFit
        }

        // 2. Grid View for the rest of the space
        GridLayout {
            Layout.fillWidth: true
            Layout.fillHeight: true
            columns: 6
            rows: 4
            columnSpacing: 10
            rowSpacing: 2

            // ROW 1: Spans all 6 columns
            Label {
                text: "Device Statistics & Information"
                font.bold: true
                font.pixelSize: 18
                Layout.columnSpan: 6
                Layout.fillWidth: true
            }

            // ROW 2: The Horizontal Line (Separator)
            Rectangle {
                height: 1
                color: "#cccccc"
                Layout.columnSpan: 6
                Layout.fillWidth: true
                Layout.topMargin: 2
                Layout.bottomMargin: 5
            }

            // ROWS 3 & 4: Data Cells
            // Column Pattern: [Right Aligned] [Left Aligned] [Right Aligned] [Left Aligned] ...

            // --- Row 3 ---
            Label { text: "Status:"; color: "#666"; Layout.alignment: Qt.AlignRight }
            Label { text: "Connected"; font.bold: true; Layout.fillWidth: true }

            Label { text: "Serial:"; color: "#666"; Layout.alignment: Qt.AlignRight }
            Label { text: "REV-4092"; font.bold: true; Layout.fillWidth: true }

            Label { text: "Uptime:"; color: "#666"; Layout.alignment: Qt.AlignRight }
            Label { text: "12d 4h"; font.bold: true; Layout.fillWidth: true }

            // --- Row 4 ---
            Label { text: "Storage:"; color: "#666"; Layout.alignment: Qt.AlignRight }
            Label { text: "1.2 TB / 4 TB"; font.bold: true; Layout.fillWidth: true }

            Label { text: "Temp:"; color: "#666"; Layout.alignment: Qt.AlignRight }
            Label { text: "42°C"; font.bold: true; Layout.fillWidth: true }

            Label { text: "Link:"; color: "#666"; Layout.alignment: Qt.AlignRight }
            Label { text: "10 Gbps"; font.bold: true; Layout.fillWidth: true }
        }
    }
}

 */