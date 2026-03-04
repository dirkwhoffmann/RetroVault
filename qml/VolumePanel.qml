import QtQuick
import QtQuick.Controls

Item {
    property int deviceId: -1
    property int volumeId: -1

    onDeviceIdChanged: {
        console.log("Loading data for device index: " + deviceId)
    }

    onVolumeIdChanged: {
        console.log("Loading data for volume index: " + volumeId)
    }

    Text {
        text: "Viewing Device " + deviceId + " Volume " + volumeId
        anchors.centerIn: parent
    }
}
