import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import Backend 1.0

Item {

    property int deviceId: -1
    property int volumeId: -1

    ColumnLayout {

        anchors.fill: parent
        spacing: 0

        Pane {

            Layout.fillWidth: true
            topPadding: Style.largeSpacing
            leftPadding: Style.largeSpacing
            rightPadding: Style.largeSpacing
            Header {

                id: header
                gridData: []
            }
        }

        Pane {

            Layout.fillWidth: true
            leftPadding: Style.largeSpacing
            rightPadding: Style.largeSpacing
            DeviceBlockSelector {

                id: deviceBlockSelector
            }
        }

        Pane {

            Layout.fillHeight: true
            Layout.fillWidth: true
            leftPadding: Style.largeSpacing
            rightPadding: Style.largeSpacing
            bottomPadding: Style.largeSpacing
            BlockView {

            }
        }
    }

    onDeviceIdChanged: {

        console.log("DevicePanel: Loading data for device index: " + deviceId)

        if (deviceId !== -1) {

            let info = Backend.deviceInfo(deviceId);

            header.gridData = [
                [ info[0],  "Cylinders:",   "42", "     Blocks:", "10334" ],
                [ info[1],  "Heads:",       "2", "      Block size:", "512" ],
                [ "",       "Sectors:",     "16",       "" ]
            ]
        }
    }

    onVolumeIdChanged: {
        console.log("DevicePanel: Loading data for volume index: " + volumeId)
    }
}
