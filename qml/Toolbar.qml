// CustomToolbar.qml
import QtQuick
import QtQuick.Controls
import QtQuick.Effects
import QtQuick.Layouts

ToolBar {

    anchors.fill: parent

    RowLayout {
        anchors.fill: parent

        NavButton {
            icon.source: "../assets/icons/folder-search-svgrepo-com.svg"
        }
        NavButton {
            icon.source: "../assets/icons/arrow-up-from-arc-svgrepo-com.svg"
        }
        NavButton {
            icon.source: "../assets/icons/refresh-ccw-alt-3-svgrepo-com.svg"
        }

        Label {
            text: "My Application"
            font.bold: true
        }

        Item {
            Layout.fillWidth: true
        }

        NavButton {
            icon.source: "../assets/icons/lock-svgrepo-com.svg"
        }
    }

    /*
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

     */
}