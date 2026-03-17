import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import retrovaultUI
import RetroVault.Controllers

ColumnLayout {

    id: root
    required property WindowController windowController
    required property VolumePanelController panelController

    anchors.fill: parent
    spacing: 0 // Style.smallSpacing

    Component.onCompleted: {

        console.log("VolumeTablBar loaded");
        panelController.refresh()
    }

    Scanner {

        id: volumeScanner
        windowController: root.windowController
        Component.onCompleted: { startScan() }
    }

    //
    // Tab bar
    //

    TabBar {
        id: bar
        // Layout.bottomMargin: -Style.iconMedium / 2
        Layout.bottomMargin: -1 //Style.mediumSpacing
        Layout.alignment: Qt.AlignLeft //  Qt.AlignHCenter
        z: 10

        TabButton {
            text: "Block Map"
            implicitWidth: 128
            implicitHeight: Style.iconMedium
        }
        TabButton {
            text: "Allocation Map"
            implicitWidth: 128
            implicitHeight: Style.iconMedium
        }
        TabButton {
            text: "Diagnose"
            implicitWidth: 128
            implicitHeight: Style.iconMedium
        }
    }

    //
    // Tabs
    //

    Frame {
        Layout.fillWidth: true
        // Layout.fillHeight: true
        Layout.preferredHeight:
            Style.largeSpacing +
            Style.iconMedium + Style.smallSpacing +
            Style.iconSmall + Style.tinySpacing +
            Style.iconMedium + Style.tinySpacing +
            Style.iconMedium + Style.tinySpacing

        topPadding: Style.largeSpacing
        leftPadding: Style.largeSpacing
        rightPadding: Style.largeSpacing
        bottomPadding: Style.mediumSpacing

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
                windowController: root.windowController
                panelController: root.panelController
                scanner: volumeScanner
            }
            AllocTab {
                windowController: root.windowController
                panelController: root.panelController
                scanner: volumeScanner
            }
            HealthTab {
                windowController: root.windowController
                panelController: root.panelController
                scanner: volumeScanner
            }
        }
    }
}