import QtQuick
import QtQuick.Layouts

Item {
    id: root

    property bool debug: false

    // Allow setting a fixed size if desired, otherwise fills
    property alias size: root.implicitWidth

    Layout.fillWidth: true
    Layout.fillHeight: true

    // Debug rectangle
    Rectangle {
        anchors.fill: parent
        color: "magenta"
        opacity: 0.3
        border.color: "magenta"
        border.width: 1
        visible: root.debug
    }
}