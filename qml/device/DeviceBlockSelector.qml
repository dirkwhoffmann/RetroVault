import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Frame {

    id: root

    // Internal State
    property int cylinder: 0
    property int head: 0
    property int track: 0
    property int sector: 0

    property alias block: blockStepper.value

    anchors.fill: parent
    padding: 10

    background: Rectangle {

        color: Qt.rgba(0,0,0, 0.02)
        border.color: Qt.rgba(0,0,0, 0.1)
        radius: Style.borderRadius
    }

    RowLayout {

        anchors.fill: parent
        spacing: 0

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
            id: blockStepper
            label: "Block"
            from: 0; to: 1024
        }
    }

    function updateHead(value) {
        console.log("updateHead: " + value)
    }

    /*
    function updateBlock(value) {
        console.log("updateBlock: " + value)
        block += 1
    }
    */
}