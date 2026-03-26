import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import RetroVault.Theme

Rectangle {
    id: root
    property alias text: label.text

    // anchors.horizontalCenter: parent.horizontalCenter
    anchors.right: parent.right
    anchors.rightMargin: Style.largeSpacing
    y: parent.height // Start off-screen
    width: Math.min(parent.width * 0.8, 400)
    height: 50
    radius: Style.borderRadius
    border.color: Palette.border
    color: Palette.secondaryBg
    opacity: 0
    z: 100

    RowLayout {
        anchors.fill: parent
        anchors.margins: 10
        spacing: 10

        Rectangle {
            width: 4
            Layout.fillHeight: true
            color: Palette.accent
            radius: 2
        }

        Label {
            id: label
            Layout.fillWidth: true
            color: Palette.primary
            font.pointSize: Style.small
            elide: Text.ElideRight
        }
    }

    // Animations
    SequentialAnimation on y {
        id: anim
        running: false
        NumberAnimation {
            to: root.parent.height - 80; duration: 400; easing.type: Easing.OutCubic
        }
        PauseAnimation {
            duration: 4000
        }
        NumberAnimation {
            to: root.parent.height; duration: 400; easing.type: Easing.InCubic
        }
        onFinished: root.destroy() // Clean up memory after showing
    }

    NumberAnimation on opacity {
        id: fade
        running: anim.running
        from: 0;
        to: 1; duration: 400
    }

    Component.onCompleted: anim.start()
}