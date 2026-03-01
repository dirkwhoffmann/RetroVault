import QtQuick
pragma Singleton

QtObject {
    // Brand Colors
    readonly property color primary: "#2196F3"
    readonly property color accent: "#FF4081"
    readonly property color background: "#FFFFFF"

    // Interaction Colors
    readonly property color hoverColor: "#FF0000" // "#F5F5F5"
    readonly property color pressedColor: "#E0E0E0"
    readonly property color iconDefault: "#546E7A"

    // Dimensions
    readonly property int toolbarHeight: 22
    readonly property int iconSize: 22
    readonly property int fontSize: 16
    readonly property int borderRadius: 4

    // Typography
    /*
    readonly property font labelFont: Qt.font({
        family: "Roboto",
        pixelSize: 14,
        weight: Font.Medium
    })
    */
}