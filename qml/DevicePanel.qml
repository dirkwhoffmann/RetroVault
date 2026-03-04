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

        Rectangle {

            Layout.preferredHeight: header.implicitHeight
            Layout.fillWidth: true

            Header {

                id: header
                gridData: []
            }
        }

        Rectangle {

            Layout.preferredHeight: deviceBlockSelector.implicitHeight
            Layout.fillWidth: true

            DeviceBlockSelector {

                id: deviceBlockSelector
            }
        }

        Rectangle {

            Layout.fillHeight: true
            Layout.fillWidth: true

            BlockView {
            }
        }
    }

    onDeviceIdChanged: {
        console.log("DevicePanel: Loading data for device index: " + deviceId)

        if (deviceId !== -1) {

            // 1. Get the QStringList from C++
            // Example return: ["Status", "Active", "Serial", "A100"]
            let info = Backend.deviceInfo(deviceId);

            // 2. Wrap it into a 2D array (one row) for the Header
            // We put the entire list as the first element of our gridData
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

    /*
    Text {
        text: "DevicePanel: Viewing Device " + deviceId + " Volume " + volumeId
        anchors.centerIn: parent
    }
    */
}
