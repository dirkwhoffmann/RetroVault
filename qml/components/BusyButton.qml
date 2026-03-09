import QtQuick
import QtQuick.Controls

ImageButton {
    id: busyControl

    property bool running: false

    enabled: !running

    contentItem: Item {

        anchors.fill: parent

        BusyIndicator {
            padding: parent.padding
            anchors.centerIn: parent
            width: parent.width
            height: parent.height
            running: busyControl.running
            visible: running
        }

        Image {
            anchors.centerIn: parent
            width: busyControl.icon.width
            height: busyControl.icon.height
            source: busyControl.icon.source
            fillMode: Image.PreserveAspectFit
            visible: !busyControl.running
        }
    }
}