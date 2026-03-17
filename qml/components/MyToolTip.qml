import QtQuick
import QtQuick.Controls

ToolTip {

    delay: 500
    timeout: 3000
    visible: parent.hovered

    /*
    contentItem: Text {
        text: parent.text
        font.pixelSize: 12
        color: "white"
    }

    background: Rectangle {
        color: "#333333"
        radius: 4
    }
    */
}