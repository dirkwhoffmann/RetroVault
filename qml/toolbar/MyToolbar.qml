import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Dialogs
import RetroVault.Controllers
import RetroVault.Assets

ToolBar {

    required property WindowController windowController

    FileDialog {

        id: fileDialog
        title: "Please choose a file"
        // currentFolder: StandardPaths.writableLocation(StandardPaths.DocumentsLocation)
        onAccepted: {
            console.log("Selected file URL: " + selectedFile)
            try {
                windowController.addImage(selectedFile)
            } catch (e) {
                console.log("Calling showError...")
                UIController.showError(e.message)
            }
        }
        /*
        onRejected: {
            console.log("Canceled")
        }
        */
    }

    property real sidebarWidth: 200

    // Ensure the toolbar has a default height if the layout is empty
    implicitHeight: 40

    RowLayout {

        anchors.fill: parent
        spacing: Style.mediumSpacing

        Item {

            Layout.preferredWidth: sidebarWidth + 2
            Layout.fillHeight: true

            RowLayout {
                anchors.fill: parent

                Item {
                    Layout.fillWidth: true
                }

                NavButton {

                    id: plusButton
                    icon.source: Assets.iconUrl(Assets.Plus)

                    onClicked: {
                        console.log("Plus clicked")
                        fileDialog.open()
                    }
                }

                NavButton {

                    id: minusButton
                    icon.source: Assets.iconUrl(Assets.Minus)

                    onClicked: {
                        console.log("Minus clicked")
                        windowController.remove()
                    }
                }

                // 3. Put the Separator at the very right edge of this container
                ToolSeparator {
                    Layout.fillHeight: true
                }
            }
        }

        NavButton {

            icon.source: Assets.iconUrl(Assets.Folder)
            MyToolTip { text: "Open in Finder" }

            enabled: wc.mountPoint !== ""

            onClicked: {
                console.log("Folder icon clicked: " + wc.mountPoint)
                Qt.openUrlExternally(wc.mountPoint)
            }
        }
        NavButton { icon.source: Assets.iconUrl(Assets.Sync) }

        Item { Layout.fillWidth: true } // Spacer

        NavButton {

            icon.source: Assets.iconUrl(windowController.isProtected ? Assets.Locked : Assets.Unlocked)
            enabled: windowController.volume != -1
            MyToolTip { text: "Toggle Write Protection" }

            onClicked: {
                console.log("Lock icon clicked: ")
                windowController.isProtected = !windowController.isProtected
            }
        }
    }
}