import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import RetroVault.Controllers

Item {

    property int deviceId: -1
    property int volumeId: -1

    DevicePanelController {

        id: controller
        device: deviceId
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
                    value: controller.cylinder
                    from: 0;
                    to: 15
                    onValueChanged: { controller.cylinder = value }
                }

                Item {
                    Layout.fillWidth: true
                }

                LabeledStepper {
                    label: "Head"
                    from: 0;
                    to: 1
                }

                Item {
                    Layout.fillWidth: true
                }

                LabeledStepper {
                    label: "Track"
                    from: 0;
                    to: 64
                }

                Item {
                    Layout.fillWidth: true
                }

                LabeledStepper {
                    label: "Sector"
                    from: 0;
                    to: 64
                }

                Item {
                    Layout.fillWidth: true
                }

                LabeledStepper {
                    id: blockStepper
                    label: "Block"
                    from: 0;
                    to: 1024
                }
            }
        }

        /*
        Pane {

            id: blockSelectorPane
            Layout.fillWidth: true
            leftPadding: Style.largeSpacing
            rightPadding: Style.largeSpacing
            DeviceBlockSelector {

                id: deviceBlockSelector
            }
        }
        */

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
                dev: deviceId
                blk: controller.block

                onBlkChanged: {
                    console.log("onBlkChanged: " + blk)
                    controller.refresh()
                }
            }
        }
    }

    onDeviceIdChanged: {

        console.log("DevicePanel: Loading data for device index: " + deviceId)

        if (deviceId !== -1) {

            controller.refresh(deviceId)
        }
    }

    Component.onCompleted: {

        console.log("Component fully loaded. Triggering refresh... " + deviceId);
        controller.refresh(deviceId)
    }
}
