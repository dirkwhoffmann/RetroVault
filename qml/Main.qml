import QtQuick
import QtQuick.Controls
import QtQuick.Dialogs
import QtQuick.Layouts
import QtQuick.Effects
import RetroVault.Models
import RetroVault.Controllers
import "components"

ApplicationWindow {

    id: root

    property WindowController wcontroller: controllerInstance

    property alias numDevices: controllerInstance.numDevices
    property alias device: controllerInstance.device
    property alias volume: controllerInstance.volume

    WindowController {

        id: controllerInstance
        model: mainModel
    }

    onNumDevicesChanged: {
        console.log("onNumDevicesChanged: " + numDevices)
    }

    onVolumeChanged: { updateStack() }
    onDeviceChanged: { updateStack() }


    property Model model

    // property int dev: -1
    // property int vol: -1

    visible: true
    width: 900
    height: 450
    // minimumWidth: 900
    // minimumHeight: 450

    // menuBar: MainMenu { }

    header: MyToolbar {

        id: mainToolbar
        windowController: wcontroller
    }

    title: "RetroVault"
    // flags: Qt.Window | Qt.CustomizeWindowHint | Qt.WindowTitleHint

    RowLayout {
        anchors.fill: parent
        spacing: 0

        Sidebar {

            id: mySidebar
            windowController: wcontroller
            numDevices: wcontroller.numDevices
            Layout.fillHeight: true
            Layout.preferredWidth: 256
            Layout.minimumWidth: 200
            z: 1

            Component.onCompleted: {
                mainToolbar.sidebarWidth = mySidebar.width
            }

            /*
            onItemSelected: (deviceId, volumeId) => {

                console.log("onItemSelected: " + deviceId + " " + volumeId);
                controller.select(deviceId, volumeId);
            }
            */
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

        // Component for the Splash Screen
        Component {
            id: splashPage
            SplashPanel {
                windowController: wcontroller
            }
        }

        Component {
            id: devicePanel
            DevicePanel {
                windowController: wcontroller
            }
        }

        Component {
            id: volumePanel
            VolumePanel {
                windowController: wcontroller
            }
        }
    }

    function updateStack() {

        console.log("updateStack for Dev:", device, "and Vol:", volume)

        if (device == -1) {
            mainStack.replace(splashPage);
        } else if (volume == -1) {
            mainStack.replace(devicePanel);
        } else {
            mainStack.replace(volumePanel);
        }
    }

    // onVolChanged: { updateStack() }
    // onDevChanged: { updateStack() }

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
