import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import Backend

Pane {

    id: root
    anchors.fill: parent
    padding: 0
    background: Rectangle { color: "transparent" }

    contentItem: RowLayout {

        anchors.fill: parent
        spacing: Style.mediumSpacing

        readonly property bool installed: Backend.hasFuse()

        Image {
            id: ledImage
            // source: "../assets/images/LEDred.png"
            source: parent.installed ? "../assets/images/LEDgreen.png" : "../assets/images/LEDred.png"
            sourceSize: Qt.size(Style.iconSmall, Style.iconSmall)
        }
        Label {
            text: parent.installed ? "macFUSE installed" : "macFUSE not installed"
        }

        Item {  Layout.fillWidth: true } // Spacer

        IconLink {
            iconSource: "../assets/icons/github.svg"
            targetUrl: "https://dirkwhoffmann.github.io/vAmiga/"
        }
    }
}
