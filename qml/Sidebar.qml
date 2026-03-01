import QtQuick
import QtQuick.Controls
import QtQuick.Effects
import QtQuick.Layouts

Item {

    id: sidebar
    width: 200
    height: parent.height

    Rectangle {
        id: sidebarRect
        anchors.fill: parent
        anchors.margins: 6
        radius: 8 // This rounds all four corners
        clip: true

        // Layout.fillHeight: true
        //Layout.fillWidth: true //  preferredWidth: 200
        color: "#ffffff"

        ListView {
            id: sidebarList
            anchors.fill: parent
            model: ["Dashboard", "Settings", "Profile", "Stats"]
            delegate: ItemDelegate {
                width: sidebarList.width
                height: 64

                contentItem: RowLayout {
                    spacing: 12
                    anchors.fill: parent
                    anchors.leftMargin: 10
                    anchors.rightMargin: 10

                    // 1. THE IMAGE (Left)
                    Image {
                        id: icon
                        // source: model.iconSource // Assumes your model has this role
                        sourceSize.width: 32
                        sourceSize.height: 32
                        Layout.alignment: Qt.AlignVCenter
                        fillMode: Image.PreserveAspectFit
                    }

                    // 2. THE TEXT BLOCK (Right)
                    ColumnLayout {
                        spacing: 2
                        Layout.fillWidth: true
                        Layout.alignment: Qt.AlignVCenter

                        Label {
                            text: "Holla, die Waldfee" // model.title // Main Text
                            font.bold: true
                            font.pixelSize: 14
                            color: "#333333"
                            Layout.fillWidth: true
                            elide: Text.ElideRight // Adds "..." if text is too long
                        }

                        Label {
                            text: "Bazinga" // model.subtitle // Smaller Description
                            font.pixelSize: 12
                            color: "#777777"
                            Layout.fillWidth: true
                            elide: Text.ElideRight
                        }
                    }
                }

                // text: modelData
                onClicked: {
                    // Change content based on selection
                    mainStack.replace(devicePanel, {"title": modelData})
                }
            }
        }
    }

    /*
    // A thin divider line instead of a heavy shadow
    Rectangle {
        width: 1
        anchors.right: parent.right
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        color: "#d0d0d0"
    }
    */
    /*
    // The "Fake" Shadow
    Rectangle {
        width: 10
        height: parent.height
        anchors.left: parent.right

        gradient: Gradient {
            orientation: Gradient.Horizontal
            GradientStop { position: 0.0; color: "#11000000" } // Darker near edge
            GradientStop { position: 1.0; color: "transparent" } // Fades out
        }
    }

     */

    // A real shadow effect
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