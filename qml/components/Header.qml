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
                color: Style.tertiaryBg
                border.color: Style.border
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
                color: Style.secondary
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
                    color: col === 0 ? Style.primary : Style.secondary
                    Layout.rightMargin: col === 2 ? 2 * Style.largeSpacing : 0
                    Layout.alignment: Qt.AlignLeft;
                    Layout.fillWidth: col === 0
                }
            }

        }
    }
}
