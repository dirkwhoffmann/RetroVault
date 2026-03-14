import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import RetroVault.Controllers

Item {

    id: root
    required property WindowController windowController

    Connections {
        target: windowController

        function onSelectionChanged() {

            console.log("VolumePanel: onSelectionChanged ")
            console.log("Dev: " + windowController.device + " Vol: " + windowController.volume);
            pc.refresh();
        }
        /*
        function onDeviceChanged() {
            console.log("VolumePanel: onDeviceChanged " + windowController.device);
            pc.refresh();
        }

        function onVolumeChanged() {
            console.log("VolumePanel: onVolumeChanged " + windowController.volume);
            pc.refresh();
        }
        */
    }

    VolumePanelController {

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
            Header {

                id: header
                image.source: pc.icon
                title: pc.name
                gridData: pc.volumeInfo
            }
        }

        Pane {

            id: tabPane
            Layout.fillWidth: true
            Layout.preferredHeight: 150
            leftPadding: Style.largeSpacing
            rightPadding: Style.largeSpacing
            VolumeTabs {

                id: layoutTab
                windowController: root.windowController
                panelController: pc
            }
        }

        Pane {

            id: blockSelectorPane
            Layout.fillWidth: true
            leftPadding: Style.largeSpacing
            rightPadding: Style.largeSpacing
            RowLayout {

                anchors.fill: parent
                // spacing: 0

                LabeledStepper {
                    id: blockStepper
                    label: "Block"
                    to: Math.max(0, pc.numBlocks - 1)
                    value: pc.block
                    onValueChanged: { console.log("Stepper: " + value); pc.block = value }
                }

                Label {
                    id: usageString
                    text: "Usage description"
                    font.pointSize: Style.small
                    Layout.alignment: Qt.AlignHCenter
                }

                Item {
                    Layout.fillWidth: true
                }

                Label {
                    id: errorString
                    text: "Holla, die Waldfee"
                    color: "red"
                    font.pointSize: Style.small
                    Layout.alignment: Qt.AlignHCenter
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
                model: pc.tableModel
            }
        }
    }

    Component.onCompleted: {

        console.log("VolumePanelController loaded.");
        console.log("Device: " + windowController.device + " Volume: " + windowController.volume);
        pc.refresh()
    }
}
