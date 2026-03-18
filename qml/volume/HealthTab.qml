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
                rawData: scanner.healthMap
                palette: panelController.healthPanelColors
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
                icon.source: scanner.strict ? Assets.iconUrl(Assets.Checked) : ""
                onClicked: {
                    scanner.strict = !scanner.strict
                    scanner.startScan()
                }
            }
        }

        // Row 4

        RowLayout {

            Layout.fillWidth: true

            Row {
                spacing: 0
                visible: scanner.healthInfo !== ""

                ImageButton {
                    size: Style.iconMedium
                    icon.source: Assets.iconUrl(Assets.ArrowPrev)
                    MyToolTip {
                        text: "Goto Previous Corrupted Block"
                    }
                    onClicked: {
                        console.log("Goto clicked")
                        panelController.gotoPrevCorruptedBlock()
                    }
                }

                ImageButton {
                    size: Style.iconMedium
                    icon.source: Assets.iconUrl(Assets.ArrowNext)
                    MyToolTip {
                        text: "Goto Next Corrupted Block"
                    }
                    onClicked: {
                        console.log("Goto clicked")
                        panelController.gotoNextCorruptedBlock()
                    }
                }
            }

            Label {
                text: scanner.healthInfo
            }

            Item {
                Layout.fillWidth: true
            } // Spacer

            Label {
                text: "Rectify"
            }

            ImageButton {
                size: Style.iconMedium
                icon.source: Assets.iconUrl(Assets.Wrench)
                onClicked: {
                    console.log("Rectify health map clicked")
                    panelController.rectifyHealthMap(scanner.strict)
                }
            }
        }

        // Spacer

        Item {
            Layout.fillHeight: true
        }
    }
}