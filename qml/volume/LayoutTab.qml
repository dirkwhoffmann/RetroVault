import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import retrovaultUI

ColumnLayout {
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
                            palette: [
                                "#808080", // Gray (Index 0)
                                "#66ff66", // Green (Index 1)
                                "#ffff66", // Yellow (Index 2)
                                "#ff6666", // Red (Index 3)
                                "cyan",    // You can also use names
                                "purple"
                            ]
                        }

                        BusyButton {
                            imageSource: "qrc:/assets/icons/sync.svg"
                            size: 18
                            running: usageVisual.isProcessing
                            onClicked: usageVisual.refreshImage()

                            ToolTip.text: "Recalculate image"
                            ToolTip.visible: hovered
                        }

                        /*
                        Button {
                            width: 18
                            height: 18
                            // icon.width: 24  // Set your desired width
                            // icon.height: 24 // Set your desired height
                            // icon.color: "transparent" // Use "transparent" to keep original image colors
                            // width: 50
                            // text: usageVisual.isProcessing ? "" : "Refresh Map"
                            icon.source: usageVisual.isProcessing ? "" : "qrc:/assets/icons/sync.svg"
                            enabled: !usageVisual.isProcessing
                            onClicked: usageVisual.refreshImage()
                           //  visible: !usageVisual.isProcessing

                            BusyIndicator {
                                anchors.centerIn: parent
                                height: parent.height //  * 0.8
                                running: usageVisual.isProcessing // Only spins when processing
                                visible: running // Only visible when running
                            }
                            // Optional: Disable the button while the background thread is working
                            // (Requires exposing a 'processing' property from C++)
                            // enabled: !usageVisual.isProcessing
                        }

                         */
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