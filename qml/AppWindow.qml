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

        onSelectionChanged: { updateStack() }
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

    SplitView {
        anchors.fill: parent
        spacing: 0

        handle: Item {
            implicitWidth: 2

            Row {
                anchors.centerIn: parent
                spacing: 0

                Rectangle {
                    width: 1
                    height: parent.parent.height
                    color: palette.mid
                }

                Rectangle {
                    width: 1
                    height: parent.parent.height
                    color: palette.light
                }
            }
        }

        Sidebar {

            id: mySidebar
            windowController: wc
            SplitView.preferredWidth: 256
            SplitView.minimumWidth: 200
            SplitView.fillHeight: true
            z: 1

            onWidthChanged: mainToolbar.sidebarWidth = width
        }

        StackView {
            id: mainStack
            SplitView.fillWidth: true
            SplitView.fillHeight: true
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
                    duration: 0
                    easing.type: Easing.InOutQuad
                }
            }
        }

        Component {
            id: splashPage
            SplashPanel {
                windowController: wc
            }
        }
        Component {
            id: devicePanel
            DevicePanel {
                windowController: wc
            }
        }
        Component {
            id: volumePanel
            VolumePanel {
                windowController: wc
            }
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