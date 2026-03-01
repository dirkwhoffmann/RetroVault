// CustomToolbar.qml
import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

ToolBar {

    property real sidebarWidth: 200

    // REMOVE: anchors.fill: parent (The header property handles this)

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

                NavButton {
                    icon.source: "../assets/icons/folder-search-svgrepo-com.svg"
                }

                Item {
                    Layout.fillWidth: true
                }

                // 2. Put your "Burger Menu" inside this container
                NavButton {
                    icon.source: "../assets/icons/arrow-up-from-arc-svgrepo-com.svg"
                }
                /*
                ToolButton {
                    anchors.left: parent.left
                    icon.source: "..."
                    width: 48
                }
                */

                // 3. Put the Separator at the very right edge of this container
                ToolSeparator {
                    anchors.right: parent.right
                    // height: parent.height
                    Layout.fillHeight: true
                }
            }
        }
        /*
        Item {
            // This spacer matches the sidebar width
            implicitWidth: sidebarWidth - navSeparator.width
        }

        NavButton { icon.source: "../assets/icons/folder-search-svgrepo-com.svg" }
    */

        /*
        ToolSeparator {
            id: navSeparator
            Layout.fillHeight: true
            leftPadding: 10
            rightPadding: 10
        }
        */
        NavButton { icon.source: "../assets/icons/folder-search-svgrepo-com.svg" }
        NavButton { icon.source: "../assets/icons/arrow-up-from-arc-svgrepo-com.svg" }
        NavButton { icon.source: "../assets/icons/refresh-ccw-alt-3-svgrepo-com.svg" }

        Label {
            text: "My Application"
            font.bold: true
            Layout.leftMargin: 10
        }

        // This pushes the Lock button to the far right
        Item { Layout.fillWidth: true }

        NavButton {
            icon.source: "../assets/icons/lock-svgrepo-com.svg"
        }
    }
}