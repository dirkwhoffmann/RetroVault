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

        RowLayout {

            Layout.fillWidth: true
            Layout.bottomMargin: Style.smallSpacing

            Slider {
                id: blockSlider
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
            }
        }

        // Row 3

        RowLayout {

            Layout.fillWidth: true

            Repeater {
                model: panelController.legendData.slice(0, 4)
                delegate: ColorInfo {
                    Layout.fillWidth: true
                    Layout.preferredWidth: root.cellWidth
                    color: modelData.color
                    label: modelData.label
                }
            }
        }

        // Row 4

        RowLayout {

            Layout.fillWidth: true

            Repeater {
                model: panelController.legendData.slice(4, 8)
                delegate: ColorInfo {
                    Layout.fillWidth: true
                    Layout.preferredWidth: root.cellWidth
                    color: modelData.color
                    label: modelData.label
                }
            }
        }

        Item {
            Layout.fillHeight: true
        }
    }
}