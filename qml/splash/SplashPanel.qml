import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import RetroVault.Controllers

Item {

    id: root
    required property WindowController windowController

    SplashPanelController {

        id: controller
        windowController: root.windowController
    }

    FontLoader {

        id: logoFont
        source: "qrc:/assets/fonts/SourceSans3-VariableFont_wght.ttf"
    }

    // Background Image
    Image {

        anchors.fill: parent
        source: "qrc:/assets/images/splash.png"
        fillMode: Image.PreserveAspectCrop
        opacity: 1.0
    }

    ColumnLayout {

        anchors.fill: parent
        spacing: 0

        Pane {

            background: Rectangle { color: "transparent" }
            Layout.fillWidth: true
            Layout.fillHeight: true
            topPadding: Style.largeSpacing
            leftPadding: Style.largeSpacing
            rightPadding: Style.largeSpacing
            Logo {

                anchors.centerIn: parent
            }
        }

        Pane {

            background: Rectangle { color: "transparent" }
            Layout.fillWidth: true
            leftPadding: Style.mediumSpacing
            rightPadding: Style.mediumSpacing
            bottomPadding: Style.mediumSpacing
            StatusBar {

                id: statusBar
                controller: controller
            }
        }
    }
}
