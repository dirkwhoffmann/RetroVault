import QtQuick
import QtQuick.Effects
import QtQuick.Controls

Item {

    id: sidebar
    width: 200
    height: parent.height

    Rectangle {
        id: sidebarRect
        anchors.fill: parent
        // Layout.fillHeight: true
        //Layout.fillWidth: true //  preferredWidth: 200
        color: "#ffffff"

        ListView {
            id: sidebarList
            anchors.fill: parent
            model: ["Dashboard", "Settings", "Profile", "Stats"]
            delegate: ItemDelegate {
                width: sidebarList.width
                text: modelData
                onClicked: {
                    // Change content based on selection
                    mainStack.replace(devicePanel, {"title": modelData})
                }
            }
        }
    }

    // The Shadow Effect

    MultiEffect {
        source: sidebarRect
        anchors.fill: sidebarRect
        shadowEnabled: true
        shadowColor: "black"
        shadowBlur: 1.0      // How soft the shadow is
        shadowHorizontalOffset: 5 // Moves shadow to the right
        shadowVerticalOffset: 0
        shadowOpacity: 0.2    // Keep it subtle
    }
}