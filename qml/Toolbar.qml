// CustomToolbar.qml
import QtQuick
import QtQuick.Controls
import QtQuick.Effects
import QtQuick.Layouts

Item {

    anchors.fill: parent

    Rectangle {

        anchors.margins: 6
        radius: 15 // This rounds all four corners
        clip: true
        id: myToolbar
        anchors.fill: parent
        //    anchors.leftMargin: 10
        //    anchors.rightMargin: 10
        // z: 10

        RowLayout {
            anchors.centerIn: parent
            anchors.leftMargin: 10
            anchors.rightMargin: 10

            ToolButton {
                text: "\u2630" // Hamburger icon (or use an Image)
                onClicked: console.log("Menu clicked")
            }

            Label {
                text: "My Application"
                font.bold: true
                font.pixelSize: 18
                Layout.fillWidth: true // Pushes subsequent buttons to the right
                verticalAlignment: Qt.AlignVCenter
            }

            ToolButton {
                text: "\uD83D\uDD0D" // Search icon
            }

            // Spacer
            Item {
                Layout.fillWidth: true
            }

            ToolButton {
                text: "\u2699" // Settings icon
            }
        }
    }

    MultiEffect {
        source: myToolbar
        // z: 9
        anchors.fill: myToolbar
        shadowEnabled: true
        shadowColor: "black"
        shadowBlur: 1.0      // How soft the shadow is
        shadowHorizontalOffset: 5 // Moves shadow to the right
        shadowVerticalOffset: 0
        shadowOpacity: 0.2    // Keep it subtle
    }
}