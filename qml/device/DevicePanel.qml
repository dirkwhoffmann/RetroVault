import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import RetroVault.Controllers
import RetroVault.Assets

Item {

    id: root
    required property WindowController windowController

    Connections {
        target: windowController

        function onDeviceChanged() { panelController.refresh(); }
        function onVolumeChanged() { panelController.refresh(); }
    }

    DevicePanelController {

        id: panelController
        windowController: root.windowController
    }

    ColumnLayout {

        anchors.fill: parent
        spacing: 0

        Pane {

            id: headerPane
            Layout.fillWidth: true
            topPadding: Style.largeSpacing
            leftPadding: Style.largeSpacing
            rightPadding: Style.largeSpacing
            Header {

                id: header
                image.source: panelController.icon
                title: panelController.name
                gridData: panelController.deviceInfo
            }
        }

        Pane {

            id: blockSelectorPane
            Layout.fillWidth: true
            leftPadding: Style.largeSpacing
            rightPadding: Style.largeSpacing
            RowLayout {

                anchors.fill: parent
                spacing: 0

                LabeledStepper {
                    label: "Cylinder"
                    to: Math.max(0, panelController.numCylinders - 1)
                    value: panelController.cylinder
                    onValueChanged: { panelController.cylinder = value }
                }

                Item {
                    Layout.fillWidth: true
                }

                LabeledStepper {
                    label: "Head"
                    to: Math.max(0, panelController.numHeads - 1)
                    value: panelController.head
                    onValueChanged: { panelController.head = value }
                }

                Item {
                    Layout.fillWidth: true
                }

                LabeledStepper {
                    label: "Track"
                    to: Math.max(0, panelController.numTracks - 1)
                    value: panelController.track
                    onValueChanged: { panelController.track = value }
                }

                Item {
                    Layout.fillWidth: true
                }

                LabeledStepper {
                    label: "Sector"
                    to: Math.max(0, panelController.numSectors - 1)
                    value: panelController.sector
                    onValueChanged: { panelController.sector = value }
                }

                Item {
                    Layout.fillWidth: true
                }

                LabeledStepper {
                    id: blockStepper
                    label: "Block"
                    to: Math.max(0, panelController.numBlocks - 1)
                    value: panelController.block
                    onValueChanged: { panelController.block = value }
                }
            }
        }

        Pane {

            id: blockViewPane
            Layout.fillHeight: true
            Layout.fillWidth: true
            leftPadding: Style.largeSpacing
            rightPadding: Style.largeSpacing
            bottomPadding: Style.largeSpacing
            BlockView {

                id: blockView
                model: panelController.tableModel
            }
        }
    }

    Component.onCompleted: {

        console.log("DevicePanelController loaded. ");
        panelController.refresh()
    }
}
