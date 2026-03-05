// CustomToolbar.qml
import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Dialogs
import Backend

ToolBar {

    FileDialog {
        id: fileDialog
        title: "Please choose a file"
        // currentFolder: StandardPaths.writableLocation(StandardPaths.DocumentsLocation)
        onAccepted: {
            console.log("Selected file URL: " + selectedFile)
            try {
                Backend.add(selectedFile)
            } catch (e) {
                UIController.showError(e.message);
            }
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
        spacing: Style.mediumSpacing

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
                    icon.source: "qrc:/assets/icons/burger.svg"

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

        NavButton { icon.source: "qrc:/assets/icons/eject.svg" }
        NavButton { icon.source: "qrc:/assets/icons/folder.svg" }
        NavButton { icon.source: "qrc:/assets/icons/sync.svg" }

        Item { Layout.fillWidth: true } // Spacer

        NavButton {
            icon.source: "qrc:/assets/icons/locked.svg"
        }
    }
}