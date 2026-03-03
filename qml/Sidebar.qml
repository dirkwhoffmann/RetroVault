import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import Backend 1.0

Item {
    id: sidebar
    height: parent.height

    // 1. Define a structured model
    /*
    ListModel {
        id: sidebarModel
        ListElement {
            title: "Dashboard"; subtitle: "Overview";
            iconSource: "../assets/icons/github.png"; expanded: false
            // Note: ListElement can't hold nested lists easily,
            // so we'll handle sub-items via a simple array or logic below.
        }
        ListElement {
            title: "Devices"; subtitle: "Manage Hardware";
            iconSource: "../assets/icons/github.png"; expanded: false
        }
    }
    */

    Rectangle {
        id: sidebarRect
        anchors.fill: parent
        color: "#ffffff"

        ListView {
            anchors.fill: parent
            id: sidebarList
            model: Backend.sidebarModel
    /*
            model: [
                { title: "Test Device", subtitle: "Sub", isDevice: true, isExpanded: false },
                    { title: "Test Volume", subtitle: "Vol", isDevice: false, isExpanded: false }
                ]

     */
            clip: true

            // Optional: add a nice animation when items appear/disappear
            add: Transition { NumberAnimation { property: "opacity"; from: 0; to: 1.0; duration: 150 } }
            remove: Transition { NumberAnimation { property: "opacity"; to: 0; duration: 150 } }

            delegate:
                ItemDelegate {
                width: sidebarList.width
                height: model.isDevice ? 64 : 44 // Volumes slightly taller for better touch/click targets

                contentItem: RowLayout {
                    spacing: 12
                    // Center the content vertically within the delegate
                    anchors.verticalCenter: parent.verticalCenter

                    // Indent volumes and make them slightly translucent
                    Item {
                        width: model.isDevice ? 0 : 24
                    }

                    // Icon/Arrow Section
                    Text {
                        Layout.alignment: Qt.AlignVCenter
                        visible: model.isDevice
                        text: model.isExpanded ? "▼" : "▶"
                        font.pixelSize: 10
                        color: "#999"
                    }

                    ColumnLayout {
                        spacing: 0
                        Layout.fillWidth: true
                        Layout.alignment: Qt.AlignVCenter

                        opacity: model.isDevice ? 1.0 : 0.8 // Visual hierarchy

                        Label {
                            text: model.title
                            font.bold: model.isDevice
                            font.pixelSize: model.isDevice ? 14 : 13
                            color: model.isDevice ? "#222" : "#444"
                            elide: Text.ElideRight
                            Layout.fillWidth: true
                        }

                        Label {
                            text: model.subtitle
                            font.pixelSize: 11
                            color: "#888"
                            elide: Text.ElideRight
                            Layout.fillWidth: true
                            // Hide subtitle if empty to save space
                            visible: text !== ""
                        }
                    }
                }

                background: Rectangle {
                    color: highlighted ? "#f0f0f0" : "transparent"

                    // Subtle separator line for devices
                    Rectangle {
                        anchors.bottom: parent.bottom
                        width: parent.width
                        height: 1
                        color: "#eee"
                        visible: model.isDevice
                    }
                }

                onClicked: {
                    if (model.isDevice) {
                        // Ensure this matches your C++ method name: toggleExpanded
                        Backend.sidebarModel.toggleExpanded(index)
                    } else {
                        console.log("Volume clicked:", model.title)
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