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

    ColumnLayout {

        anchors.fill: parent
        spacing: 0

        // Row 1

        RowLayout {
            Layout.fillWidth: true
            Layout.bottomMargin: Style.smallSpacing

            ColorBar {
                Layout.fillWidth: true
                Layout.preferredHeight: Style.iconMedium
                rawData: scanner.allocMap
                palette: panelController.allocPanelColors
            }

            BusyButton {
                imageSource: Assets.iconUrl(Assets.Sync)
                size: Style.iconMedium
                onClicked: { scanner.startScan(panelController.strict) }
                busy: scanner.isScanning
                ToolTip.text: "Scan Image..."
                ToolTip.visible: hovered
            }
        }
        // Row 2

        RowLayout {

            Layout.fillWidth: true
            Layout.bottomMargin: Style.tinySpacing

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
            }
        }

        // Row 3

        RowLayout {

            Layout.fillWidth: true
            Layout.bottomMargin: Style.tinySpacing

            ColorInfo {

                Layout.fillWidth: true
                Layout.preferredWidth: 164
                color: panelController.okColor
                label: "Used and Allocated"
            }
            ColorInfo {

                visible: panelController.strict
                Layout.fillWidth: true
                Layout.preferredWidth: 164
                color: panelController.warnColor
                label: "Unused but Allocated"
            }
            ColorInfo {

                Layout.fillWidth: true
                Layout.preferredWidth: 164
                color: panelController.errorColor
                label: "Used but Unallocated"
            }

            Item {
                Layout.fillWidth: true
            } // Spacer

            Label {
                text: "Strict"
            }

            ImageButton {
                size: Style.iconMedium
                icon.source: panelController.strict ? Assets.iconUrl(Assets.Checked) : ""
                onClicked: {
                    panelController.strict = !panelController.strict
                    scanner.startScan(panelController.strict)
                }
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
        }

        // Spacer

        Item {
            Layout.fillHeight: true
        }
    }
}