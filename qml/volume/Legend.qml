import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Item {
    id: root

    property var palette: []

    implicitHeight: grid.implicitHeight

    GridLayout {
        id: grid
        columns: 4
        anchors.left: parent.left
        anchors.right: parent.right
        columnSpacing: 4
        rowSpacing: 4

        Repeater {

            model: root.palette

            delegate: ColorInfo {

                Layout.fillWidth: true
                color: modelData.color
                label: modelData.label
            }
        }
    }
}