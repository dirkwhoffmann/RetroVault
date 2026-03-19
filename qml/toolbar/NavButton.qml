import QtQuick
import QtQuick.Controls

ToolButton {

    font.pixelSize: Style.fontSize
    icon.width: Style.iconMedium
    icon.height: Style.iconMedium

    icon.color: {
        if (!enabled) return "#bdc3c7"      // Disabled (Gainsboro)
        if (down) return Style.primary      // Pressed
        if (hovered) return "#2c3e50"       // Hovered (Darker)
        return "#7f8c8d"                    // Normal (Subtle Grey)
    }
}