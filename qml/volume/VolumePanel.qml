import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import RetroVault.Models
import RetroVault.Controllers

Item {

    id: root
    required property Model model
    required property int device
    required property int volume

    VolumePanelController {

        id: controller
        model: root.model
        device: root.device
        volume: root.volume
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
                gridData: controller.volumeInfo
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
                controller: root.controller
                palette: controller.legendData
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
                    to: Math.max(0, controller.numBlocks - 1)
                    value: controller.block
                    onValueChanged: { controller.block = value }
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
                model: controller.tableModel
            }
        }
    }

    /*
    onDevNrChanged: {

        console.log("onDevNrChanged: " + devNr)
    }

    onVolNrChanged: {

        console.log("onVolNrChanged: " + devNr)
    }
    */

    Component.onCompleted: {

        console.log("VolumePanelController fully loaded. " + devNr);
        controller.refresh()
    }
}
