import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import RetroVault.Controllers

Item {

    id: root
    property int devNr: -1
    property int volNr: -1
    // property var volInfo: []

    VolumePanelController {

        id: controller
        device: devNr
        volume: volNr
        model: mainModel
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
            LayoutTab {

                id: layoutTab
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

    onDevNrChanged: {

        console.log("onDevNrChanged: " + devNr)
    }

    onVolNrChanged: {

        console.log("onVolNrChanged: " + devNr)
    }

    Component.onCompleted: {

        console.log("VolumePanelController fully loaded. " + devNr);
        controller.refresh()
    }
}
