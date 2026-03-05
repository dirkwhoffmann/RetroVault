import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import Backend

Item {

    property int deviceId: -1
    property int volumeId: -1

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
                dev: deviceId
                gridData: []
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
                }
            }
        }
    }

    onDeviceIdChanged: {

        console.log("DevicePanel: Loading data for device index: " + deviceId)

        if (deviceId !== -1) {

            // Backend.selectDevice(deviceId)
            /* let info = Backend.oldDeviceInfo(deviceId)

            Backend.refreshBlockView(deviceId, blockView.blk)
            header.gridData = [
                [ info[0],  "Cylinders:",   "42", "     Blocks:", "10334" ],
                [ info[1],  "Heads:",       "2", "      Block size:", "512" ],
                [ "",       "Sectors:",     "16",       "" ]
            ]

             */
        }
    }

    onVolumeIdChanged: {
        console.log("DevicePanel: Loading data for volume index: " + volumeId)
    }
}
