import QtQuick
import QtQuick.Controls
// import "."

ToolButton {
    id: control

    /*
    contentItem: Row {
        spacing: 8
        icon: control.icon
        text: control.text
        font: Style.labelFont
        color: control.visualFocus ? Style.accent : Style.iconDefault
        display: control.display
    }
    */

    font.pixelSize: Style.fontSize
    icon.width: Style.iconSize
    icon.height: Style.iconSize
    // background.implicitWidth: Style.toolbarHeight
    // background.implicitHeight: Style.toolbarHeight
    /*
    background: Rectangle {
        implicitWidth: Style.toolbarHeight
        implicitHeight: Style.toolbarHeight
        radius: Style.borderRadius
        color: control.pressed ? Style.pressedColor :
            (control.hovered ? Style.hoverColor : "transparent")
*/
        // Subtle indicator for the active/checked state
        /*
        Rectangle {
            width: parent.width
            height: 3
            anchors.bottom: parent.bottom
            color: Style.primary
            visible: control.checked
        }
        */
   // }
}