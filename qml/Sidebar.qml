import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import Backend 1.0

Item {
    id: sidebar
    height: parent.height

    Rectangle {
        id: sidebarRect
        anchors.fill: parent
        color: "#ffffff"

        TreeView {
            id: treeView
            anchors.fill: parent
            model: Backend.sidebarModel
            clip: true
            alternatingRows: false
            topMargin: 10
            rowSpacing: 10

            delegate: TreeViewDelegate {

                required property bool isDevice
                required property string title
                required property string subtitle

                width: treeView.width
                height: isDevice ? 64 : 44

                contentItem: RowLayout {

                    spacing: 8

                    Image {
                        source: "../assets/images/LEDred.png"
                        sourceSize: Qt.size(18, 18)

                        // This is the "Magic" line that centers the image relative to the row's height
                        Layout.alignment: Qt.AlignVCenter
                    }

                    ColumnLayout {
                        spacing: 0
                        Layout.fillWidth: true
                        Layout.alignment: Qt.AlignVCenter

                        Label {
                            text: title
                            font.bold: isDevice
                            Layout.fillWidth: true
                        }
                        Label {
                            text: subtitle
                            visible: subtitle !== ""
                            font.pixelSize: 11
                            color: "#888"
                            Layout.fillWidth: true
                        }
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