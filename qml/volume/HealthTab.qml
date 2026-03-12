import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import RetroVault.Assets
import RetroVault.Models
import RetroVault.Controllers

Item {

    id: root
    required property Model model

    /*
    UsageScanner {

        id: scanner
        model: root.controller.model
        device: root.controller.device
        volume: root.controller.volume
    }
    */

    ColumnLayout {

        anchors.fill: parent

        // Row 1

        RowLayout {
            Layout.fillWidth: true

            UsageDisplay {

                id: usageVisual
                model: mainModel
                implicitWidth: 1
                Layout.fillWidth: true
                Layout.preferredHeight: 18
                palette: [] // root.palette
            }

            /*
            Rectangle {
                color: "red"
                Layout.fillWidth: true
                Layout.preferredHeight: 18
            }
            */

            ImageButton {
                // This is now the "content" of the BusyButton
                imageSource: "qrc:/assets/icons/sync.svg"
                size: Style.iconMedium
                // onClicked: { usageVisual.refreshImage() }
                onClicked: { scanner.startScan() }
                visible: !usageVisual.isProcessing
            }
            BusyIndicator {
                implicitHeight: Style.iconMedium
                implicitWidth: Style.iconMedium
                visible: usageVisual.isProcessing
                padding: 2
                /*
                BusyIndicator {
                    running: usageVisual.isProcessing
                    // anchors.centerIn: parent

                    ImageButton {
                        // This is now the "content" of the BusyButton
                        imageSource: "qrc:/assets/icons/sync.svg"
                        size: Style.iconMedium
                        onClicked: usageVisual.refreshImage()
                        // Note: You don't need to manually hide this;
                        // BusyButton handles the opacity/enabled state.
                    }
                }
    */
                /*
                BusyButton {
                    imageSource: "qrc:/assets/icons/sync.svg"
                    size: Style.iconMedium
                    running: usageVisual.isProcessing
                    onClicked: usageVisual.refreshImage()

                    ToolTip.text: "Recalculate image"
                    ToolTip.visible: hovered
                }

                 */
            }
        }
        // Row 2

        RowLayout {

            Layout.fillWidth: true

            Slider {
                id: blockSlider
                Layout.fillWidth: true
                from: 1
                value: 25
                to: 100
            }

            Item {
                Layout.preferredWidth: Style.iconMedium
                Layout.fillHeight: true
            }
        }

        // Row 3

        RowLayout {

            Layout.fillWidth: true

            /*
            Legend {
                id: legend
                Layout.fillWidth: true
                palette: root.palette
            }
            */
            ColorInfo {

                Layout.fillWidth: true
                color: "green"
                label: "Consistent Blocks"
            }
            ColorInfo {

                Layout.fillWidth: true
                color: "red"
                label: "Corrupted Blocks"
            }

            Item {
                Layout.fillWidth: true
            } // Spacer

            Label {
                text: "Strict"
            }

            ImageButton {
                size: Style.iconMedium
                icon.source: Assets.iconUrl(Assets.Checked)
            }
        }

        // Row 4

        RowLayout {

            Layout.fillWidth: true

            ColorInfo {

                Layout.fillWidth: true
                color: "red"
                label: "Waldfee"
            }

            Item {
                Layout.fillWidth: true
            } // Spacer

            Label {
                text: "Rectify"
            }

            ImageButton {
                size: Style.iconMedium
                icon.source: Assets.iconUrl(Assets.Health)
            }
            /*
                        ImageButton {
                            imageSource: "qrc:/assets/icons/sync.svg"
                            size: 18
                        }

             */
        }
    }
}