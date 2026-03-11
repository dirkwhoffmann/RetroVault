import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

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
        }
    }
}