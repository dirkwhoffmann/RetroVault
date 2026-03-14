import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import RetroVault.Controllers

Item {

    id: root
    required property WindowController windowController
    required property VolumePanelController panelController
    required property Scanner scanner

    readonly property int cellWidth: width / 4

    Connections {
        target: windowController

        function onSelectionChanged() {

            console.log("UsageTab: onSelectionChanged ")
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
                rawData: scanner.usageMap
                palette: panelController.usagePanelColors
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

        Slider {
            // id: blockSlider
            Layout.fillWidth: true
            from: 0
            value: panelController.block
            to: panelController.numBlocks
            stepSize: 1
            snapMode: Slider.SnapAlways
            onMoved: panelController.block = Math.floor(value)
        }

        // Row 3

        RowLayout {

            Layout.fillWidth: true

            ColorInfo {

                Layout.fillWidth: true
                Layout.preferredWidth: root.cellWidth
                color: panelController.bootBlockColor
                label: "Boot Block"
            }
            ColorInfo {

                Layout.fillWidth: true
                Layout.preferredWidth: root.cellWidth
                color: panelController.bitmapBlockColor
                label: "Bitmap Block"
            }
            ColorInfo {

                Layout.fillWidth: true
                Layout.preferredWidth: root.cellWidth
                color: panelController.directoryBlockColor
                label: "User Directory Block"
            }
            ColorInfo {

                Layout.fillWidth: true
                Layout.preferredWidth: root.cellWidth
                color: panelController.listBlockColor
                label: "File List Block"
            }
        }

        // Row 4

        RowLayout {

            Layout.fillWidth: true

            ColorInfo {

                Layout.fillWidth: true
                Layout.preferredWidth: root.cellWidth
                color: panelController.rootBlockColor
                label: "Root Block"
            }
            ColorInfo {

                Layout.fillWidth: true
                Layout.preferredWidth: root.cellWidth
                color: panelController.bitmapExtBlockColor
                label: "Bitmap Extension Block"
            }
            ColorInfo {

                Layout.fillWidth: true
                Layout.preferredWidth: root.cellWidth
                color: panelController.headerBlockColor
                label: "File Header Block"
            }
            ColorInfo {

                Layout.fillWidth: true
                Layout.preferredWidth: root.cellWidth
                color: panelController.dataBlockColor
                label: "Data Block"
            }
        }
    }
}