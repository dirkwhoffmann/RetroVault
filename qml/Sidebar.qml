import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import RetroVault.Controllers

Item {
    id: root
    height: parent.height

    required property WindowController windowController

    SidebarController {

        id: panelController
        windowController: root.windowController
    }

    Rectangle {

        id: sidebarRect
        anchors.fill: parent
        color: "#ffffff"

        TreeView {

            id: treeView
            anchors {
                left: parent.left
                top: parent.top
                bottom: parent.bottom
                right: parent.right
                rightMargin: Style.mediumSpacing
            }
            clip: true
            alternatingRows: true
            topMargin: 10
            model: panelController.sidebarModel
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
                        source: iconSource
                        sourceSize: Qt.size(36, 36)
                        Layout.alignment: Qt.AlignVCenter
                    }

                    Item {
                        Layout.preferredHeight: 50
                        Layout.preferredWidth: 2
                    }

                    ColumnLayout {

                        Layout.fillWidth: true
                        Layout.alignment: Qt.AlignVCenter

                        Label {
                            text: title
                            font.bold: isDevice
                            color: highlighted ? "white" : treeView.palette.text
                            Layout.fillWidth: true
                            elide: Text.ElideRight
                        }
                        Label {
                            text: subtitle
                            visible: subtitle !== ""
                            font.pixelSize: 11
                            color:  highlighted ? "white" : treeView.palette.text
                            Layout.fillWidth: true
                            elide: Text.ElideRight
                        }
                    }
                }

                TapHandler {

                    onTapped: {

                        console.log("Sidebar::select " + deviceId + " " + volumeId);
                        windowController.select(deviceId, volumeId);
                    }
                }
            }
        }
    }

    // Right-side divider
    /*
    Rectangle {

        width: 1
        anchors.right: parent.right
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        color: "#d0d0d0"
    }
    */
    function refresh() {
        console.log("Sidebar::refresh")
        panelController.refresh()
    }
}