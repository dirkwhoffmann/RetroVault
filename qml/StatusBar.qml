import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

RowLayout {

    anchors.fill: parent
    anchors.leftMargin: 10
    anchors.rightMargin: 10

    // BOTTOM LEFT: Icon + Label
    RowLayout {
//        anchors.verticalCenter: parent.verticalCenter
        spacing: 8

        Image {
            source: "../assets/LEDred.png"
            sourceSize: Qt.size(18, 18)
        }
        Label {
            text: "macFUSE not installed"
            font.pixelSize: 12
        }
    }

    // SPACER: This invisible item eats all available middle space
    Item {
        Layout.fillWidth: true
    }

    // BOTTOM RIGHT: Single Icon
    Image {
        source: "../assets/github.png"
        sourceSize: Qt.size(18, 18)
    }
}
