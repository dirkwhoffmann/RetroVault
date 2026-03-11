import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import RetroVault.Controllers
import RetroVault.Assets

Item {

    id: root
    required property WindowController windowController
    required property int device

    DevicePanelController {

        id: controller
        windowController: root.windowController
        device: root.device
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
                image.source: controller.icon
                title: controller.name
                gridData: controller.deviceInfo
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
                    to: Math.max(0, controller.numCylinders - 1)
                    value: controller.cylinder
                    onValueChanged: { controller.cylinder = value }
                }

                Item {
                    Layout.fillWidth: true
                }

                LabeledStepper {
                    label: "Head"
                    to: Math.max(0, controller.numHeads - 1)
                    value: controller.head
                    onValueChanged: { controller.head = value }
                }

                Item {
                    Layout.fillWidth: true
                }

                LabeledStepper {
                    label: "Track"
                    to: Math.max(0, controller.numTracks - 1)
                    value: controller.track
                    onValueChanged: { controller.track = value }
                }

                Item {
                    Layout.fillWidth: true
                }

                LabeledStepper {
                    label: "Sector"
                    to: Math.max(0, controller.numSectors - 1)
                    value: controller.sector
                    onValueChanged: { controller.sector = value }
                }

                Item {
                    Layout.fillWidth: true
                }

                LabeledStepper {
                    id: blockStepper
                    label: "Block"
                    to: Math.max(0, controller.numBlocks - 1)
                    value: controller.block
                    onValueChanged: { controller.block = value }
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
                model: controller.tableModel
            }
        }
    }

    Component.onCompleted: {

        console.log("DevicePanelController fully loaded. ");
        controller.refresh()
    }
}
