import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

RowLayout {

    id: root
    spacing: Style.mediumSpacing

    property alias label: textLabel.text
    property alias color: colorBox.color

    Rectangle {
        id: colorBox
        visible: label && label !== ""
        width: 12
        height: 12
        radius: 2
        border.color: Style.tertiary
        border.width: 1
    }

    Label {
        id: textLabel
        Layout.fillWidth: true
        text: "Lorem ipsum"
        font.pointSize: Style.small
        elide: Text.ElideRight
        verticalAlignment: Text.AlignVCenter
    }
}