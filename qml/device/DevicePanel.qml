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

        function onSelectionChanged() { pc.refresh(); }
    }

    DevicePanelController {

        id: pc
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
            bottomPadding: Style.mediumSpacing
            Header {

                id: header
                image.source: windowController.deviceIcon
                title: pc.name
                gridData: pc.deviceInfo
            }
        }

        Pane {

            id: blockSelectorPane
            Layout.fillWidth: true
            topPadding: Style.mediumSpacing
            leftPadding: Style.largeSpacing
            rightPadding: Style.largeSpacing
            bottomPadding: Style.smallSpacing
            RowLayout {

                anchors.fill: parent
                spacing: 0

                LabeledStepper {
                    label: "Cylinder"
                    to: Math.max(0, pc.numCylinders - 1)
                    value: pc.cylinder
                    onValueChanged: { pc.cylinder = value }
                }

                Item {
                    Layout.fillWidth: true
                }

                LabeledStepper {
                    label: "Head"
                    to: Math.max(0, pc.numHeads - 1)
                    value: pc.head
                    onValueChanged: { pc.head = value }
                }

                Item {
                    Layout.fillWidth: true
                }

                LabeledStepper {
                    label: "Track"
                    to: Math.max(0, pc.numTracks - 1)
                    value: pc.track
                    onValueChanged: { pc.track = value }
                }

                Item {
                    Layout.fillWidth: true
                }

                LabeledStepper {
                    label: "Sector"
                    to: Math.max(0, pc.numSectors - 1)
                    value: pc.sector
                    onValueChanged: { pc.sector = value }
                }

                Item {
                    Layout.fillWidth: true
                }

                LabeledStepper {
                    id: blockStepper
                    label: "Block"
                    to: Math.max(0, pc.numBlocks - 1)
                    value: pc.block
                    onValueChanged: { pc.block = value }
                }
            }
        }

        Pane {

            id: blockViewPane
            Layout.fillHeight: true
            Layout.fillWidth: true
            topPadding: Style.smallSpacing
            leftPadding: Style.largeSpacing
            rightPadding: Style.largeSpacing
            bottomPadding: Style.largeSpacing
            BlockView {

                id: blockView
                model: pc.tableModel
            }
        }
    }

    Component.onCompleted: {

        // console.log("DevicePanelController loaded. ");
        pc.refresh()
    }
}
