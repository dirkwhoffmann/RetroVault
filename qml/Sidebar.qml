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
            id: sidebarList
            anchors.fill: parent
            clip: true

            // Use your C++ model instance
            model: Backend.sidebarModel

            // Smoothly animate additions/removals if the list changes
            add: Transition { NumberAnimation { property: "opacity"; from: 0; to: 1.0; duration: 200 } }

            delegate: Column {
                width: sidebarList.width

                // --- TOP LEVEL ITEM ---
                ItemDelegate {
                    id: mainItem
                    width: parent.width
                    height: 64

                    contentItem: RowLayout {
                        spacing: 12
                        Layout.fillWidth: true

                        // Expansion Indicator - Now driven by the model Role
                        Text {
                            text: model.expanded ? "▼" : "▶"
                            font.pixelSize: 10
                            color: "#bbb"
                            Layout.leftMargin: 8
                        }

                        Image {
                            source: "../assets/icons/device_icon.png"
                            sourceSize: Qt.size(32, 32)
                        }

                        ColumnLayout {
                            spacing: 2
                            Layout.fillWidth: true
                            Label {
                                text: model.title // From TitleRole
                                font.bold: true
                                color: "#333"
                            }
                            Label {
                                text: model.subtitle // From SubtitleRole
                                font.pixelSize: 12
                                color: "#777"
                            }
                        }
                    }

                    onClicked: sidebarList.model.toggleExpanded(index)
                }

                // --- EXPANDABLE SECTION ---
                // Using a Loader or Column with 'visible' is fine,
                // but 'visible' inside a Column still occupies space unless managed.
                Column {
                    width: parent.width
                    visible: model.expanded

                    Repeater {
                        // model.volumes comes from VolumesRole (QStringList)
                        model: model.expanded ? model.volumes : []
                        delegate: ItemDelegate {
                            width: parent.width
                            height: 40
                            contentItem: Label {
                                text: modelData
                                leftPadding: 54
                                verticalAlignment: Text.AlignVCenter
                                color: "#555"
                            }
                            onClicked: console.log("Clicked:", modelData)
                        }
                    }
                }
            }
            Component.onCompleted: {
                console.log("Model initialized. Count:", model.rowCount())
                // If this prints 'undefined', the connection to Backend is broken.
                // If this prints '0', your C++ 'm_devices' vector is empty.
            }
        }

        /*
        ListView {
            id: sidebarList
            anchors.fill: parent
            clip: true

            signal mapChanged()

            property var expandedMap: ({})

            // We use the count as the model.
            model: Backend.deviceCount()

            // When C++ says things changed, we tell the list to refresh
            Connections {
                target: Backend
                function onUpdateSidebar() {
                    sidebarList.model = 0; // Force reset
                    sidebarList.model = Backend.deviceCount();
                }
            }

            // Smoothly animate the height changes when expanding
            add: Transition { NumberAnimation { property: "opacity"; from: 0; to: 1.0; duration: 200 } }
            displaced: Transition { NumberAnimation { properties: "y"; duration: 200; easing.type: Easing.OutQuad } }

            delegate: Column {
                width: sidebarList.width
                readonly property int devIdx: index // Capture our position

                // 2. Look up the title once for this delegate
                readonly property string deviceTitle: Backend.deviceTitle(index)

                // 3. Check the map for our specific title
                // We use '|| false' to default to collapsed if the key doesn't exist
                readonly property bool expanded: sidebarList.expandedMap[deviceTitle] || false

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
                                text: Backend.deviceTitle(devIdx)
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

                        // Recreate the entire expanded map to retrigger GUI updates
                        let newMap = Object.assign({}, sidebarList.expandedMap);
                        newMap[deviceTitle] = !expanded;
                        sidebarList.expandedMap = newMap;
                    }
                }

                // --- EXPANDABLE SECTION (Sub-items) ---
                Column {
                    width: parent.width

                    visible: expanded // Only show if expanded
                    // Simple Repeater for sub-items
                    Repeater {
                        model: Backend.volumeNames(index) // ["Sub Action A", "Sub Action B"]
                        delegate: ItemDelegate {
                            width: parent.width
                            height: 40
                            contentItem: Label {
                                text: Backend.volumeNames(devIdx)
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
        */
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