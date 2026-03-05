import QtQuick
import QtQuick.Controls
import QtQuick.Effects
import "."

Item {

    id: root
    implicitWidth: iconSize
    implicitHeight: iconSize

    property url iconSource
    property url targetUrl
    property real iconSize: Style.iconMedium

    Image {

        id: iconImage
        anchors.fill: parent
        source: root.iconSource
    }

    MouseArea {

        id: mouseArea
        anchors.fill: parent
        cursorShape: Qt.PointingHandCursor

        onClicked: {
            if (root.targetUrl.toString() !== "") {
                Qt.openUrlExternally(root.targetUrl)
            }
        }
    }
}
