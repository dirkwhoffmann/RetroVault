import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Frame {
    id: root
    anchors.fill: parent
    padding: 10

    // Theming the Frame background like a macOS "Section"
    background: Rectangle {
        color: Qt.rgba(0,0,0, 0.02)
        border.color: Qt.rgba(0,0,0, 0.1)
        radius: Style.borderRadius
    }

    RowLayout {
        // anchors.fill: parent
        spacing: 0

        // Layout.fillWidth: true
        anchors.fill: parent

        LabeledStepper {
            label: "Cylinder"
            from: 0; to: 15
        }

        Item { Layout.fillWidth: true }

        LabeledStepper {
            label: "Head"
            from: 0; to: 1
        }

        Item { Layout.fillWidth: true }

        LabeledStepper {
            label: "Track"
            from: 0; to: 64
        }

        Item { Layout.fillWidth: true }

        LabeledStepper {
            label: "Sector"
            from: 0; to: 64
        }

        Item { Layout.fillWidth: true }

        LabeledStepper {
            label: "Block"
            from: 0; to: 1024
        }
    }
}