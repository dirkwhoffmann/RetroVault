import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import Qt.labs.qmlmodels

Item {
    ColumnLayout {
        anchors.fill: parent
        anchors.margins: 20

        Label {
            text: "Dashboard Data"
            font.pixelSize: 24
        }

        HorizontalHeaderView {
            id: horizontalHeader
            syncView: tableView
            Layout.fillWidth: true
        }

        TableView {
            id: tableView
            Layout.fillWidth: true
            Layout.fillHeight: true
            clip: true
            columnSpacing: 1
            rowSpacing: 1

            model: TableModel {
                TableModelColumn { display: "id" }
                TableModelColumn { display: "name" }
                TableModelColumn { display: "status" }

                rows: [
                    { "id": 1, "name": "Hardware Node A", "status": "Active" },
                    { "id": 2, "name": "Sensor Array", "status": "Standby" },
                    { "id": 3, "name": "Logic Controller", "status": "Error" }
                ]
            }

            delegate: Rectangle {
                implicitWidth: 150
                implicitHeight: 40
                border.color: palette.mid
                color: palette.base

                Text {
                    text: display
                    anchors.centerIn: parent
                    color: palette.text
                }
            }
        }
    }
}