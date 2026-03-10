import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import retrovaultUI

ColumnLayout {

    id: root
    property var palette: []

    anchors.fill: parent
    spacing: Style.smallSpacing

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

                    RowLayout {
                        Layout.fillWidth: true

                        UsageDisplay {

                            id: usageVisual
                            model: mainModel
                            Layout.fillWidth: true
                            Layout.preferredHeight: 18
                            palette: root.palette
                        }

                        BusyButton {
                            imageSource: "qrc:/assets/icons/sync.svg"
                            size: 18
                            running: usageVisual.isProcessing
                            onClicked: usageVisual.refreshImage()

                            ToolTip.text: "Recalculate image"
                            ToolTip.visible: hovered
                        }
                    }

                    Slider {
                        id: blockSlider
                        Layout.fillWidth: true
                        from: 1
                        value: 25
                        to: 100
                    }

                    Legend {
                        id: legend
                        Layout.fillWidth: true
                        palette: root.palette
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