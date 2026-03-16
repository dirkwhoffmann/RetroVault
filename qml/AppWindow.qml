import QtQuick
import QtQuick.Controls
import QtQuick.Dialogs
import QtQuick.Layouts
import QtQuick.Effects
import RetroVault.Controllers
import "components"

ApplicationWindow {

    id: root

    WindowController {

        id: wc

        onVolumeChanged: { updateStack() }
        onDeviceChanged: { updateStack() }
        onNumDevicesChanged: {
            console.log("ApplicationWindow::onNumDevicesChanged: " + numDevices)
            mySidebar.refresh()
        }
    }

    visible: true
    width: 900
    height: 500
    // minimumWidth: 900
    // minimumHeight: 420

    header: MyToolbar {

        id: mainToolbar
        windowController: wc
    }

    // title: "RetroVault"
    // flags: Qt.Window | Qt.CustomizeWindowHint | Qt.WindowTitleHint

    RowLayout {
        anchors.fill: parent
        spacing: 0

        Sidebar {

            id: mySidebar
            windowController: wc
            Layout.fillHeight: true
            Layout.preferredWidth: 256
            Layout.minimumWidth: 200
            z: 1

            Component.onCompleted: {
                mainToolbar.sidebarWidth = mySidebar.width
            }
        }

        StackView {
            id: mainStack
            Layout.fillWidth: true
            Layout.fillHeight: true
            z: 0

            // The first page to show
            initialItem: splashPage

            replaceEnter: Transition {
                NumberAnimation {
                    property: "opacity"
                    from: 0.0
                    to: 1.0
                    duration: 400
                    easing.type: Easing.InOutQuad
                }
            }

            // When the old item is removed
            replaceExit: Transition {
                NumberAnimation {
                    property: "opacity"
                    from: 1.0
                    to: 0.0
                    duration: 400
                    easing.type: Easing.InOutQuad
                }
            }
        }

        SplashPanel {
            id: splashPage
            windowController: wc
        }
        DevicePanel {
            id: devicePanel
            windowController: wc
        }
        VolumePanel {
            id: volumePanel
            windowController: wc
        }
    }

    function updateStack() {

        console.log("updateStack: ", wc.device, ", ", wc.volume)

        if (wc.device == -1) {
            mainStack.replace(splashPage);
        } else if (wc.volume == -1) {
            mainStack.replace(devicePanel);
        } else {
            mainStack.replace(volumePanel);
        }
    }

    Connections {

        target: UIController
        function onRequestErrorDialog(message) {
            errorDialog.text = message
            errorDialog.open()
        }
    }

    MessageDialog {
        id: errorDialog
        title: "Application Error"
    }
}