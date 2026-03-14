import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import RetroVault.Assets
import RetroVault.Controllers

Item {

    id: root
    required property WindowController windowController
    required property VolumePanelController panelController
    required property Scanner scanner

    Connections {
        target: windowController

        function onSelectionChanged() {

            console.log("HealthTab: onSelectionChanged ")
            console.log("Dev: " + windowController.device + " Vol: " + windowController.volume);
            scanner.startScan();
        }
    }

    ColumnLayout {

        anchors.fill: parent

        // Row 1

        RowLayout {
            Layout.fillWidth: true

            ColorBar {

                Layout.fillWidth: true
                Layout.preferredHeight: Style.iconMedium
                rawData: scanner.healthMap
                palette: [
                    Style.gray,
                    Style.green,
                    Style.red,
                    Style.white ]
            }

            BusyButton {
                imageSource: Assets.iconUrl(Assets.Sync)
                size: Style.iconMedium
                onClicked: { scanner.startScan() }
                busy: scanner.isScanning

                ToolTip.text: "Scan Image..."
                ToolTip.visible: hovered
            }
        }
        // Row 2

        RowLayout {

            Layout.fillWidth: true

            Slider {
                Layout.fillWidth: true
                from: 0
                value: panelController.block
                to: panelController.numBlocks
                stepSize: 1
                snapMode: Slider.SnapAlways
                onMoved: panelController.block = Math.floor(value)
            }

            Item {
                Layout.preferredWidth: Style.iconMedium
                Layout.fillHeight: true
            }
        }

        // Row 3

        RowLayout {

            Layout.fillWidth: true

            ColorInfo {

                Layout.fillWidth: true
                Layout.preferredWidth: 164
                color: panelController.okColor
                label: "Consistent Blocks"
            }
            ColorInfo {

                Layout.fillWidth: true
                Layout.preferredWidth: 164
                color: panelController.errorColor
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

            Label {
                text: "Some error text..."
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