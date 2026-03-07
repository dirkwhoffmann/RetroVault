import QtQuick
import QtQuick.Controls
import QtQuick.Dialogs
import QtQuick.Layouts
import QtQuick.Effects
import RetroVault.Models
import RetroVault.Controllers
import "components"

ApplicationWindow {

    WindowController {

        id: controller
        model: mainModel
    }

    property Model model

    property int dev: -1
    property int vol: -1

    visible: true
    width: 900
    height: 450
    // minimumWidth: 900
    // minimumHeight: 450

    // menuBar: MainMenu { }

    header: MyToolbar {

        id: mainToolbar
        controller: controller
    }

    title: "RetroVault"
    // flags: Qt.Window | Qt.CustomizeWindowHint | Qt.WindowTitleHint

    RowLayout {
        anchors.fill: parent
        spacing: 0

        Sidebar {
            id: mySidebar
            Layout.fillHeight: true
            Layout.preferredWidth: 256
            Layout.minimumWidth: 200
            z: 1

            Component.onCompleted: {
                mainToolbar.sidebarWidth = mySidebar.width
            }

            onItemSelected: (deviceId, volumeId) => {

                dev = deviceId
                vol = volumeId
            }
        }

        StackView {
            id: mainStack
            // anchors.fill: parent
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
            /*
            pushEnter: null
            pushExit: null
            popEnter: null
            popExit: null
            */
        }

        // Component for the Splash Screen
        Component {
            id: splashPage
            SplashPanel {
            }
        }

        Component {
            id: devicePanel
            DevicePanel {
            }
        }

        Component {
            id: volumePanel
            VolumePanel {
            }
        }
    }

    function updateStack() {

        console.log("updateStack for Dev:", dev, "and Vol:", vol)

        if (dev == -1) {
            mainStack.replace(splashPage);
        } else if (vol == -1) {
            mainStack.replace(devicePanel, {"deviceId": dev, "volumeId": vol});
        } else {
            mainStack.replace(volumePanel, {"devNr": dev, "volNr": vol});
        }
    }

    /*
    onVolChanged: { updateStack() }
    onDevChanged: { updateStack() }
    */

    Connections {

        target: UIController
        function onRequestErrorDialog(message) {
            errorDialog.text = message
            errorDialog.open()
        }
    }

    /*
    Connections {
        target: Backend
        function onUpdateCanvas() {
            console.log("UIController: onUpdateCanvas: ");
        }

        function onUpdateSidebar() {
            console.log("UIController: onUpdateSidebar: ");
        }
    }
    */

    MessageDialog {
        id: errorDialog
        title: "Application Error"
    }
}
