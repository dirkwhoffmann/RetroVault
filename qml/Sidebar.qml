import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Item {
    id: sidebar
    height: parent.height

    // 1. Define a structured model
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

    Rectangle {
        id: sidebarRect
        anchors.fill: parent
        color: "#ffffff"

        ListView {
            id: sidebarList
            anchors.fill: parent
            clip: true

            // We use the count as the model.
            // To refresh, we just re-assign the count or use a Connections block.
            model: vaultProxy.deviceCount()

            // When C++ says things changed, we tell the list to refresh
            Connections {
                target: vaultProxy
                function onDataChanged() {
                    sidebarList.model = 0; // Force reset
                    sidebarList.model = vaultProxy.deviceCount();
                }
            }

            // Smoothly animate the height changes when expanding
            add: Transition { NumberAnimation { property: "opacity"; from: 0; to: 1.0; duration: 200 } }
            displaced: Transition { NumberAnimation { properties: "y"; duration: 200; easing.type: Easing.OutQuad } }

            delegate: Column {
                width: sidebarList.width
                readonly property int devIdx: index // Capture our position

                // --- TOP LEVEL ITEM ---
                ItemDelegate {
                    id: mainItem
                    width: parent.width
                    height: 64

                    contentItem: RowLayout {
                        spacing: 12
                        // anchors.fill: parent
                        // anchors.leftMargin: 4
                        Layout.fillWidth: true
                        Layout.alignment: Qt.AlignVCenter

                       //  Rectangle {anchors.fill: parent; border.color: "#ff0000"; border.width: 2 }

                        // Expansion Indicator (Arrow)
                        Text {
                            text: model.expanded ? "▼" : "▶"
                            font.pixelSize: 10
                            color: "#bbb"
                            Layout.leftMargin: 8
                        }

                        Image {
                            source: "../assets/icons/github.png"
                            sourceSize: Qt.size(32, 32)
                            Layout.alignment: Qt.AlignVCenter
                        }

                        ColumnLayout {
                            // Rectangle {anchors.fill: parent; color: "red" }
                            spacing: 2
                            Layout.fillWidth: true
                            Label {
                                text: vaultProxy.deviceTitle(devIdx)
                                font.bold: true
                                color: "#333"
                                Layout.fillWidth: true
                                Layout.alignment: Qt.AlignLeft
                            }
                            Label {
                                text: "TODO" // model.subtitle
                                font.pixelSize: 12
                                color: "#777"
                                Layout.fillWidth: true
                                Layout.alignment: Qt.AlignLeft
                            }
                        }
                    }

                    onClicked: {
                        // Toggle the expanded property in the model
                        sidebarModel.setProperty(index, "expanded", !model.expanded)
                    }
                }

                // --- EXPANDABLE SECTION (Sub-items) ---
                Column {
                    width: parent.width
                    visible: model.expanded // Only show if expanded

                    // Simple Repeater for sub-items
                    Repeater {
                        model: model.volumes // ["Sub Action A", "Sub Action B"]
                        delegate: ItemDelegate {
                            width: parent.width
                            height: 40
                            contentItem: Label {
                                text: vaultProxy.volumeNames(devIdx)
                                leftPadding: 54 // Indent sub-items
                                verticalAlignment: Text.AlignVCenter
                                color: "#555"
                            }
                            background: Rectangle {
                                color: highlighted ? "#f0f0f0" : "transparent"
                            }
                            onClicked: console.log("Clicked sub-item: " + modelData)
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