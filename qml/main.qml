import QtQuick
import QtQuick.Controls
import QtQuick.Dialogs
import QtQuick.Layouts
import QtQuick.Effects
import QtGraphs

ApplicationWindow {
    visible: true
    width: 900
    height: 450
    // minimumWidth: 900
    // minimumHeight: 450

    // menuBar: MainMenu { }

    header: MyToolbar {
        id: mainToolbar
    }

    title: "RetroVault"
    // flags: Qt.Window | Qt.CustomizeWindowHint | Qt.WindowTitleHint

    RowLayout {
        anchors.fill: parent
        spacing: 0

        // --- 1. THE SIDEBAR ---
        Sidebar {
            id: mySidebar
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
    }

    // Component for the Splash Screen
    Component {
        id: splashPage
        SplashView {
            // onStartClicked: mainStack.push(tableViewPage)
        }
    }

    Component {
        id: devicePanel
        DevicePanel {}
    }

    // Component for the Main Table View
    Component {
        id: tableViewPage
        MainTableView {}
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

    /*
    DropArea {
        id: dropArea
        // anchors.fill: parent
        // keys: ["text/plain"] // Only accept this specific type

        onDropped: (drop) => {

            if (drop.hasText) {
                console.log("Dropped data:", drop.text)
                // drop.acceptProposedAction()
            }
            if (drop.hasUrls) {
                // 1. Loop through all dropped items
                for (var i = 0; i < drop.urls.length; i++) {
                    let rawUrl = drop.urls[i].toString();

                    // 2. Convert to a clean local path
                    // Using Qt.resolvedUrl or simple regex to remove 'file://'
                    let localPath = rawUrl.replace(/^(file:\/{2})/,"");

                    // On Linux/Kubuntu, the path might still have a leading /
                    // e.g., /home/user/Documents/project.txt
                    console.log("Accepted file:", localPath);
                }
                drop.acceptProposedAction();

                mainStack.push(tableViewPage)
            }
        }
    }

     */
}
