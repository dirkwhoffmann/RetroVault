import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import RetroVault.Controllers
import Backend // DEPRECATED

Item {

    DevicePanelController {

        id: controller
        model: mainModel
    }

    property int deviceId: -1
    property int volumeId: -1
    property var deviceInfo: []

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
                gridData: deviceInfo // []
            }
        }

        Pane {

            id: blockSelectorPane
            Layout.fillWidth: true
            leftPadding: Style.largeSpacing
            rightPadding: Style.largeSpacing
            DeviceBlockSelector {

                id: deviceBlockSelector
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
                dev: deviceId
                blk: deviceBlockSelector.block

                onBlkChanged: {
                    console.log("onBlkChanged: " + blk)
                    controller.start()
                }
            }
        }
    }

    onDeviceIdChanged: {

        console.log("DevicePanel: Loading data for device index: " + deviceId)

        if (deviceId !== -1) {

            let info = Backend.getDeviceInfo(deviceId);

            // header.title = info.name
            deviceInfo = [
                [info.name, "Cylinders:", info.numCyls, "     Blocks:", info.numBlocks],
                ["", "Heads:", info.numHeads, "      Block size:", info.bsize],
                ["", "Sectors:", "TODO", ""] // or dev.maxSectors
            ];
        }
    }

    onVolumeIdChanged: {
        console.log("DevicePanel: Loading data for volume index: " + volumeId)
    }
}
