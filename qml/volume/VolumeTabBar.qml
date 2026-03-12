import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import retrovaultUI
import RetroVault.Models
import RetroVault.Controllers

ColumnLayout {

    id: root
    required property Model model
    property var palette: []

    anchors.fill: parent
    spacing: Style.smallSpacing

    //
    // Tab bar
    //

    TabBar {
        id: bar
        // Layout.fillWidth: true

        TabButton { text: "Device Info" }
        TabButton { text: "Hex View" }
        TabButton { text: "Settings" }
    }

    //
    // Tabs
    //

    Frame {
        Layout.fillWidth: true
        Layout.fillHeight: true
        padding: 10

        background: Rectangle {
            color: Qt.rgba(0,0,0, 0.02)
            border.color: Qt.rgba(0,0,0, 0.1)
            radius: Style.borderRadius

            // Optional: Remove top border/radius to make it look
            // physically attached to the TabBar
        }

        StackLayout {
            anchors.fill: parent
            currentIndex: bar.currentIndex

            UsageTab {
                model: root.model
            }
            AllocTab {
                model: root.model
            }
            HealthTab {
                model: root.model
            }
        }
    }
}