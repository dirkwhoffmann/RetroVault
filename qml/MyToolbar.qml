// CustomToolbar.qml
import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Dialogs

ToolBar {

    FileDialog {
        id: fileDialog
        title: "Please choose a file"
        // currentFolder: StandardPaths.writableLocation(StandardPaths.DocumentsLocation)
        onAccepted: {
            console.log("Selected file URL: " + selectedFile)
            // let path = selectedFile.toString().replace("file://", "")
            deviceModel.addDevice(selectedFile)
        }
        onRejected: {
            console.log("Canceled")
        }
    }

    property real sidebarWidth: 200

    // Ensure the toolbar has a default height if the layout is empty
    implicitHeight: 40

    RowLayout {
        // Use anchors to stick to the edges, but let height be implicit
        anchors.fill: parent
        spacing: 0

        // 1. Create a container that exactly matches the Sidebar width
        Item {
            Layout.preferredWidth: sidebarWidth + 1
            Layout.fillHeight: true

            RowLayout {
                anchors.fill: parent

                Item {
                    Layout.fillWidth: true
                }

                // 2. Put your "Burger Menu" inside this container
                NavButton {
                    id: burgerButton
                    icon.source: "../assets/icons/burger.svg"

                    onClicked: burgerMenu.open()

                    Menu {
                        id: burgerMenu
                        y: burgerButton.height // Appear directly below the button

                        MenuItem {
                            text: qsTr("Add Image")
                            onTriggered: fileDialog.open()
                        }
                    }
                }

                // 3. Put the Separator at the very right edge of this container
                ToolSeparator {
                    Layout.fillHeight: true
                }
            }
        }

        NavButton { icon.source: "../assets/icons/eject.svg" }
        NavButton { icon.source: "../assets/icons/folder.svg" }
        NavButton { icon.source: "../assets/icons/sync.svg" }

        // This pushes the Lock button to the far right
        Item { Layout.fillWidth: true }

        NavButton {
            icon.source: "../assets/icons/locked.svg"
        }
    }
}