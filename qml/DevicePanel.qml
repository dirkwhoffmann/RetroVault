import QtQuick
import QtQuick.Controls

Item {
    property int deviceId: -1
    property int volumeId: -1

    onDeviceIdChanged: {
        console.log("DevicePanel: Loading data for device index: " + deviceId)
    }

    onVolumeIdChanged: {
        console.log("DevicePanel: Loading data for volume index: " + volumeId)
    }

    Text {
        text: "DevicePanel: Viewing Device " + deviceId + " Volume " + volumeId
        anchors.centerIn: parent
    }
}
