import QtQuick
import QtQuick.Controls

ImageButton {

    required property url targetUrl

    background: Rectangle { color: "transparent" }

    onClicked: {
        if (targetUrl.toString() !== "") {
            Qt.openUrlExternally(targetUrl)
        }
    }
}