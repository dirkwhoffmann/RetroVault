import QtQuick
import QtQuick.Layouts
import QtQuick.Controls
import Backend
import DeviceInfo

Pane {

    id: root
    anchors.fill: parent
    padding: 0

    // property int dev: -1
    // onDevChanged: updateData()

    property var gridData: []

    readonly property int gridColumns: gridData.length > 0 ? gridData[0].length : 1

    contentItem: RowLayout {
        spacing: 15

        Frame {
            Layout.alignment: Qt.AlignTop
            background: Rectangle {
                color: Qt.rgba(0, 0, 0, 0.03) // Subtle darkening tint
                border.color: Qt.rgba(0, 0, 0, 0.1) // Thin, soft border
                border.width: 2
                radius: 8
            }
            Image {
                source: "../assets/images/floppy35_dd.png"
                sourceSize: Qt.size(80, 80)
            }
        }

        GridLayout {

            columns: root.gridColumns
            Layout.fillWidth: true
            Layout.alignment: Qt.AlignTop
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

    //
    // Functions
    //

    /*
    function updateData() {

        if (dev < 0) return [];

        let info = Backend.getDeviceInfo(dev);

        gridData = [
            [info.name, "Cylinders:", info.numCyls, "     Blocks:", info.numBlocks],
            ["", "Heads:", info.numHeads, "      Block size:", info.bsize],
            ["", "Sectors:", "TODO", ""] // or dev.maxSectors
        ];
    }
    */

}
