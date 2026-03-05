import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

RowLayout {
    id: control
    spacing: 4

    property alias label: textLabel.text
    property alias color: colorBox.color

    Rectangle {
        id: colorBox
        width: 12
        height: 12
        color: "#27ae60"
        radius: 2
        border.color: Qt.darker(color, 1.2)
        border.width: 1
    }

    Label {
        id: textLabel
        text: "Lorem ipsum"
        font.pointSize: Style.small
        // Layout.alignment: Qt.AlignHCenter
    }
}