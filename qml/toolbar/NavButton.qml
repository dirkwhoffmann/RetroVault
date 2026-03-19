import QtQuick
import QtQuick.Controls

ToolButton {

    font.pixelSize: Style.fontSize
    icon.width: Style.iconMedium
    icon.height: Style.iconMedium

    icon.color: {
        if (!enabled) return Style.tertiary // Disabled
        if (down) return Style.primary      // Pressed
        if (hovered) return Style.primary   // Hovered
        return Style.secondary
    }
}