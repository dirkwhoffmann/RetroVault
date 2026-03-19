import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

RowLayout {
    id: control
    spacing: 4

    property alias label: titleLabel.text
    property alias value: sb.value
    property alias from: sb.from
    property alias to: sb.to
    property alias stepSize: sb.stepSize
    property alias pointSize: titleLabel.font.pointSize

    Label {
        id: titleLabel
        font.pointSize: Style.small
        color: Style.primary
        Layout.alignment: Qt.AlignHCenter
    }

    SpinBox {
        id: sb
        editable: true
        Layout.preferredWidth: 64
        Layout.alignment: Qt.AlignHCenter
    }
}