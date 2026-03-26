// -----------------------------------------------------------------------------
// This file is part of RetroVault
//
// Copyright (C) Dirk W. Hoffmann. www.dirkwhoffmann.de
// Licensed under the Mozilla Public License v2
//
// See https://mozilla.org/MPL/2.0 for license information
// -----------------------------------------------------------------------------

import QtQuick
import QtQuick.Controls
import QtQuick.Dialogs
import QtQuick.Layouts
import QtQuick.Effects
import RetroVault.Controllers
import RetroVault.Theme
import "components"

ApplicationWindow {

    id: root

    Palette.darkMode: AppController.darkMode

    WindowController {

        id: wc
        onSelectionChanged: { updateStack() }
        onNumDevicesChanged: { mySidebar.refresh() }
        onOpenImageRequested: { fileDialog.open() }

        onImageMounted: (mountPoint) => {
            AppController.showNotification("Mounted: " + mountPoint)
        }
    }

    Connections {

        target: AppController

        function onRequestErrorDialog(message) {
            errorDialog.text = message
            errorDialog.open()
        }

        function onRequestNotificationDialog(message) {

            const component = Qt.createComponent("components/Toast.qml");
            if (component.status === Component.Ready) {
                // Create the toast as a child of the root window
                component.createObject(root, {"text": message});
            }
        }
    }

    MessageDialog {

        id: errorDialog
        title: "RetroVault Error"
        buttons: MessageDialog.Ok
        // icon: MessageDialog.Critical
    }

    Timer {

        interval: 500
        running: true
        repeat: true
        onTriggered: { wc.periodicRefresh() }
    }

    FileDialog {

        id: fileDialog
        title: "Please choose a file"
        onAccepted: {
            try {
                wc.addImage(selectedFile)
                // AppController.showNotification("Image mounted")
            } catch (e) {
                AppController.showError(e.message)
            }
        }
    }

    visible: true
    width: 900
    height: 500
    // minimumWidth: 900
    // minimumHeight: 420

    header: MyToolbar {

        id: mainToolbar
        // padding: 50
        windowController: wc
        sidebarWidth: mySidebar.width
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

            // onWidthChanged: mainToolbar.sidebarWidth = width
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
}