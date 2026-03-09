import QtQuick
import QtQuick.Controls

Button {
    id: control

    property url imageSource: ""
    property real size: 32
    property real iconScale: 1.0 // 0.6

    implicitWidth: size
    implicitHeight: size
    padding: 0

    icon.source: imageSource
    icon.width: size * iconScale
    icon.height: size * iconScale
    icon.color: "transparent"

    background: Rectangle {
        color: control.down ? "#d0d0d0" : (control.hovered ? "#e8e8e8" : "transparent") // "#f5f5f5")
        radius: 4
        // border.color: "#cccccc"
        // border.width: control.activeFocus ? 2 : 1
    }
}