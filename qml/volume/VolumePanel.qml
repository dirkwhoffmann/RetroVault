import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import Backend

Item {

    id: root
    property int devNr: -1
    property int volNr: -1
    property var volInfo: []

    ColumnLayout {

        anchors.fill: parent
        spacing: 0

        Pane {

            id: headerPane
            Layout.fillWidth: true
            topPadding: Style.largeSpacing
            leftPadding: Style.largeSpacing
            rightPadding: Style.largeSpacing
            Header {

                id: header
                gridData: volInfo
            }
        }

        Pane {

            id: tabPane
            Layout.fillWidth: true
            Layout.preferredHeight: 150
            leftPadding: Style.largeSpacing
            rightPadding: Style.largeSpacing
            LayoutTab {

                id: layoutTab
            }
        }

        Pane {

            id: blockSelectorPane
            Layout.fillWidth: true
            leftPadding: Style.largeSpacing
            rightPadding: Style.largeSpacing
            DeviceBlockSelector {

                id: deviceBlockSelector
            }
        }

        Pane {

            id: blockViewPane
            Layout.fillHeight: true
            Layout.fillWidth: true
            leftPadding: Style.largeSpacing
            rightPadding: Style.largeSpacing
            bottomPadding: Style.largeSpacing
            BlockView {

                id: blockView
                dev: devNr
                blk: deviceBlockSelector.block
            }
        }
    }

    onDevNrChanged: {

        console.log("onDevNrChanged: " + devNr)
    }

    onVolNrChanged: {

        console.log("onVolNrChanged: " + devNr)
    }
}
