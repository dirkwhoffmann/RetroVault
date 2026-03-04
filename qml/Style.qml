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
    readonly property real _baseSize: Qt.application.font.pointSize
    readonly property font heading: Qt.font({ pointSize: _baseSize * 1.5, weight: Font.DemiBold })
    readonly property font regular: Qt.font({ pointSize: _baseSize })
    readonly property font small: Qt.font({ pointSize: _baseSize * 0.85 })
    readonly property font mini: Qt.font({ pointSize: _baseSize * 0.7 })
    */
    readonly property real _baseSize: Qt.application.font.pointSize
    readonly property real heading: _baseSize * 1.5
    readonly property real regular: _baseSize
    readonly property real small: _baseSize * 0.85
    readonly property real mini: _baseSize * 0.7

    // Helper for specific weights
    readonly property int weightBold: Font.Bold
    readonly property int weightMedium: Font.Medium
}