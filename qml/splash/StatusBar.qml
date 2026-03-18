import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import RetroVault.Controllers

Pane {

    property SplashPanelController controller

    id: root
    anchors.fill: parent
    padding: 0
    background: Rectangle { color: "transparent" }

    contentItem: RowLayout {

        anchors.fill: parent
        spacing: Style.mediumSpacing

        Image {
            id: ledImage
            source: controller.hasFuse() ? Assets.iconUrl(Assets.LEDGreen) : Assets.iconUrl(Assets.LEDRed)
            sourceSize: Qt.size(Style.iconSmall, Style.iconSmall)
        }
        Label {
            text: parent.installed ? "macFUSE installed" : "macFUSE not installed"
        }

        Item {  Layout.fillWidth: true } // Spacer

        IconLink {
            iconSource: Assets.iconUrl(Assets.GitHub)
            targetUrl: "https://dirkwhoffmann.github.io/vAmiga/"
        }
    }
}
