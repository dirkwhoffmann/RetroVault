import QtQuick
import QtQuick.Controls

RoundButton {
    id: control

    property url imageSource: ""
    property real size: Style.iconLarge
    property real iconScale: 0.8 // 0.6

    implicitWidth: size
    implicitHeight: size
    padding: 0
    radius: 4

    icon.source: imageSource
    icon.color: Style.secondary
    icon.width: size * iconScale
    icon.height: size * iconScale
}