import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import RetroVault.Controllers

Item {

    id: root
    required property WindowController windowController
    required property VolumePanelController panelController

    UsageScanner {

        id: scanner
        windowController: root.windowController
        // Component.onCompleted: { startScan() }
    }

    ColumnLayout {

        anchors.fill: parent

        RowLayout {
            Layout.fillWidth: true

            ColorBar {

                Layout.fillWidth: true
                Layout.preferredHeight: Style.iconMedium
                rawData: scanner.buffer
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

        Legend {
            id: legend
            Layout.fillWidth: true
            palette: [] // root.palette
        }

        Item {
            Layout.fillHeight: true
        } // Spacer
    }
}