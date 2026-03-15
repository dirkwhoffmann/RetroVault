import QtQuick
import QtQuick.Controls

Control {
    id: root

    // The "Wrapped" Button will be the initial item
    default property alias content: stack.initialItem
    property bool running: false

    // Sync the enabled state of the whole control
    enabled: !running

    // Force the control to take the size of the inner button
    implicitWidth: stack.implicitWidth
    implicitHeight: stack.implicitHeight

    StackView {
        id: stack
        anchors.fill: parent

        // Logic to switch views based on the 'running' property
        onRunningChanged: {
            if (running) {
                stack.push(busyComponent)
            } else {
                stack.pop()
            }
        }

        // Define the Busy State as a Component
        Component {
            id: busyComponent
            Item {
                BusyIndicator {
                    anchors.centerIn: parent
                    running: root.running
                    // Scale to fit the button's dimensions
                    width: Math.min(parent.width, parent.height) * 0.8
                    height: width
                }
            }
        }

        // Optional: Customize the transition (Fade, Zoom, etc.)
        replaceEnter: Transition { NumberAnimation { property: "opacity"; from: 0; to: 1; duration: 200 } }
        replaceExit: Transition { NumberAnimation { property: "opacity"; from: 1; to: 0; duration: 200 } }
    }
}

/*
Control {
    id: root

    // This allows you to put the ImageButton inside the curly braces
    default property alias content: container.data

    property bool running: false
    property real iconScale: 0.8

    implicitWidth: container.implicitWidth
    implicitHeight: container.implicitHeight

    // The "Wrapper" Logic
    Item {
        id: container
        anchors.fill: parent

        // This makes the wrapped button (ImageButton)
        // invisible while the loader is spinning
        opacity: root.running ? 0 : 1
        enabled: !root.running

        Behavior on opacity { NumberAnimation { duration: 200 } }
    }

    BusyIndicator {
        anchors.centerIn: parent
        width: Math.min(parent.width, parent.height) * root.iconScale
        height: width
        running: root.running
        visible: root.running
    }
}
*/
