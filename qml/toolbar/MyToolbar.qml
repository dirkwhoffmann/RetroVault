import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Dialogs
import RetroVault.Controllers
import RetroVault.Assets

ToolBar {

    property WindowController controller

    FileDialog {

        id: fileDialog
        title: "Please choose a file"
        // currentFolder: StandardPaths.writableLocation(StandardPaths.DocumentsLocation)
        onAccepted: {
            console.log("Selected file URL: " + selectedFile)
            try {
                controller.addImage(selectedFile)
            } catch (e) {
                console.log("Calling showError...")
                UIController.showError(e.message)
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

        anchors.fill: parent
        spacing: Style.mediumSpacing

        Item {

            Layout.preferredWidth: sidebarWidth + 1
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
                    }
                }

                /*
                NavButton {

                    id: burgerButton
                    icon.source: "qrc:/assets/icons/burger.svg"

                    onClicked: burgerMenu.open()

                    Menu {
                        id: burgerMenu
                        y: burgerButton.height

                        MenuItem {
                            text: "Add Image"
                            onTriggered: fileDialog.open()
                        }
                    }
                }
                */

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