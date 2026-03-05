import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import UsageDisplay

ColumnLayout {
    anchors.fill: parent
    spacing: 4 // Remove space so TabBar sits flush against the Frame

    // 1. TabBar is now outside the Frame
    TabBar {
        id: bar
        // Layout.fillWidth: true

        TabButton { text: "Device Info" }
        TabButton { text: "Hex View" }
        TabButton { text: "Settings" }
    }

    // 2. Frame now only contains the content
    Frame {
        Layout.fillWidth: true
        Layout.fillHeight: true
        padding: 10

        background: Rectangle {
            color: Qt.rgba(0,0,0, 0.02)
            border.color: Qt.rgba(0,0,0, 0.1)
            radius: Style.borderRadius

            // Optional: Remove top border/radius if you want it to look
            // physically attached to the TabBar
        }

        StackLayout {
            anchors.fill: parent
            currentIndex: bar.currentIndex

            Item {

                ColumnLayout {

                    anchors.fill: parent

                    UsageDisplay {

                        id: usageVisual
                        Layout.fillWidth: true
                        Layout.preferredHeight: 24
                    }

                    Item {
                        Layout.fillHeight: true
                    } // Spacer
                }
            }
            Item {
                // Label { text: "Page 2 Content" }
                Rectangle { anchors.fill: parent; color: "red" }
            }
            Item {
                Label { text: "Page 3 Content" }
            }
        }
    }
}