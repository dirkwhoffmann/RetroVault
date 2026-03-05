import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import Backend 1.0

Item {
    id: sidebar
    height: parent.height

    signal itemSelected(int deviceId, int volumeId)

    Rectangle {
        id: sidebarRect
        anchors.fill: parent
        color: "#ffffff"

        TreeView {
            id: treeView
            anchors.fill: parent
            clip: true
            alternatingRows: true
            topMargin: 10
            model: Backend.sidebarModel
            selectionMode: TreeView.SingleSelection
            selectionModel: ItemSelectionModel { }
            columnWidthProvider: function(column) { return treeView.width }
            delegate: TreeViewDelegate {

                id: myDelegate
                required property string iconSource
                required property string title
                required property string subtitle
                required property int deviceId
                required property int volumeId
                required property bool isDevice

                width: treeView.width

                contentItem: RowLayout {

                    spacing: 8

                    Image {

                        source: `qrc:/assets/images/${iconSource}`
                        sourceSize: Qt.size(36, 36)
                        Layout.alignment: Qt.AlignVCenter
                    }


                    Item {
                        // color: "red"
                        Layout.preferredHeight: 50
                        Layout.preferredWidth: 2
                    }

                    ColumnLayout {

                        Layout.fillWidth: true
                        Layout.alignment: Qt.AlignVCenter

                        Label {
                            text: title
                            font.bold: isDevice
                            color:  highlighted ? "white" : treeView.palette.text
                            Layout.fillWidth: true
                        }
                        Label {
                            text: subtitle
                            visible: subtitle !== ""
                            font.pixelSize: 11
                            color:  highlighted ? "white" : treeView.palette.text
                            Layout.fillWidth: true
                        }
                    }
                }

                TapHandler {
                    onTapped: {

                        // console.log("modelIndex = " + modelIndex);
                        console.log("deviceId = " + deviceId);
                        console.log("volumeId = " + volumeId);
                        sidebar.itemSelected(deviceId, volumeId);
                    }
                }
            }
        }
    }

    // Right-side divider
    Rectangle {

        width: 1
        anchors.right: parent.right
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        color: "#d0d0d0"
    }
}