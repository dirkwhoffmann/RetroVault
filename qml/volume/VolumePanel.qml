import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import RetroVault.Controllers

Item {

    id: root
    required property WindowController windowController

    Connections {
        target: windowController

        function onDeviceChanged() {
            console.log("VolumePanel(1): onDeviceChanged " + windowController.device);
            vpc.refresh();
        }

        function onVolumeChanged() {
            console.log("VolumePanel(1): onVolumeChanged " + windowController.volume);
            vpc.refresh();
        }
    }

    VolumePanelController {

        id: vpc
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
                image.source: vpc.icon
                title: vpc.name
                gridData: vpc.volumeInfo
            }
        }

        Pane {

            id: tabPane
            Layout.fillWidth: true
            Layout.preferredHeight: 150
            leftPadding: Style.largeSpacing
            rightPadding: Style.largeSpacing
            VolumeTabBar {

                id: layoutTab
                windowController: root.windowController
                panelController: vpc
                // palette: vpc.legendData
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
                    to: Math.max(0, vpc.numBlocks - 1)
                    value: vpc.block
                    onValueChanged: { console.log("Stepper: " + value); vpc.block = value }
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
                model: vpc.tableModel
            }
        }
    }

    Component.onCompleted: {

        console.log("VolumePanelController loaded.");
        console.log("Device: " + windowController.device + " Volume: " + windowController.volume);
        vpc.refresh()
    }
}
