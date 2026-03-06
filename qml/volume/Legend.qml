import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Item {

    implicitHeight: grid.implicitHeight

    GridLayout {

        id: grid
        columns: 4
        anchors.left: parent.left
        anchors.right: parent.right
        columnSpacing: 4
        rowSpacing: 4

        Repeater {

            model: ["1", "2", "3", "4", "5", "6", "7", "8"]

            delegate: ColorInfo {

                Layout.fillWidth: true
                /*
                readonly property int col: index % gridColumns

                text: modelData //  + (col % 2 === 1 ? ":" : "")
                font.pointSize: Style.small
                elide: Text.ElideRight
                color: col === 0 ? "#000" : "#666"
                Layout.alignment: Qt.AlignLeft // col % 2 === 1 ? Qt.AlignRight : Qt.AlignLeft
                Layout.fillWidth: col === 0 // index % 2 !== 1
                 */
            }
        }
    }
}
