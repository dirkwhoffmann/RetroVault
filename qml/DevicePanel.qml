import QtQuick
import QtQuick.Controls

Rectangle {
    id: devicePanel
    property string title: "Welcome"
    color: "gray"
    Text {
        anchors.centerIn: parent
        text: "Viewing: " + parent.title
        font.pixelSize: 24
    }
}