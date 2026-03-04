import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

RowLayout {
    id: control
    spacing: 4

    // Properties to make the component functional
    property alias label: titleLabel.text
    property alias value: sb.value
    property alias from: sb.from
    property alias to: sb.to
    property alias stepSize: sb.stepSize

    Label {
        id: titleLabel
        font.pointSize: Style.small
        Layout.alignment: Qt.AlignHCenter
    }

    SpinBox {
        id: sb
        editable: true
        Layout.preferredWidth: 64
        // Layout.maximumWidth: 120
        Layout.alignment: Qt.AlignHCenter

        // Customizing the text input for a cleaner look
        contentItem: TextInput {
            text: sb.textFromValue(sb.value, sb.locale)
            font.pointSize: Style.small
            horizontalAlignment: Qt.AlignHCenter
            verticalAlignment: Qt.AlignVCenter
            readOnly: !sb.editable
            validator: sb.validator
            inputMethodHints: Qt.ImhDigitsOnly
        }
    }
}