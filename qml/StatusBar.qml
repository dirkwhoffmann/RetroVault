import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Pane {

    id: root
    anchors.fill: parent
    padding: 0
    background: Rectangle { color: "transparent" }

    contentItem: RowLayout {

        anchors.fill: parent
        spacing: Style.mediumSpacing

        Image {
            id: ledImage
            source: "../assets/images/LEDred.png"
            sourceSize: Qt.size(Style.iconSmall, Style.iconSmall)
        }
        Label {
            text: "macFUSE not installed"
        }

        Item {  Layout.fillWidth: true } // Spacer

        IconLink {
            iconSource: "../assets/icons/github.svg"
            targetUrl: "https://dirkwhoffmann.github.io/vAmiga/"
        }
    }
}
