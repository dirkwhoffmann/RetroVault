import QtQuick
import QtQuick.Layouts
import QtQuick.Controls

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
                color: Qt.rgba(0, 0, 0, 0.03) // Subtle darkening tint
                border.color: Qt.rgba(0, 0, 0, 0.1) // Thin, soft border
                border.width: 2
                radius: 8
            }

            Image {

                id: image
                // source: "qrc:/assets/images/floppy35_dd.png"
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
                color: "#cccccc"
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
                    color: col === 0 ? "#000" : "#666"
                    Layout.alignment: Qt.AlignLeft
                    Layout.fillWidth: col === 0
                }
            }

        }
    }
}
