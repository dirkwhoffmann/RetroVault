import QtQuick
pragma Singleton

QtObject {
    /*
    // Brand Colors
    readonly property color primary: "#2196F3"
    readonly property color accent: "#FF4081"
    readonly property color background: "#FFFFFF"

    // Interaction Colors
    readonly property color hoverColor: "#FF0000" // "#F5F5F5"
    readonly property color pressedColor: "#E0E0E0"
    readonly property color iconDefault: "#546E7A"
    */

    // Colors
    readonly property color white: QColor(0xff, 0xff, 0xff)
    readonly property color gray: QColor(0x80, 0x80, 0x80)
    readonly property color black: QColor(0x00, 0x00, 0x00)
    readonly property color red: QColor(0xff, 0x66, 0x66)
    readonly property color orange: QColor(0xff, 0xb2, 0x66)
    readonly property color yellow: QColor(0xff, 0xff, 0x66)
    readonly property color green: QColor(0x66, 0xff, 0x66)
    readonly property color dgreen: QColor(0x00, 0x99, 0x00)
    readonly property color cyan: QColor(0x66, 0xff, 0xff)
    readonly property color blue: QColor(0x66, 0xb2, 0xff)
    readonly property color purple: QColor(0xb2, 0x66, 0xff)
    readonly property color pink: QColor(0xff, 0x66, 0xff)

    // Layout Units
    readonly property real gridUnit: Qt.application.font.pointSize
    readonly property real smallSpacing: 4
    readonly property real mediumSpacing: 8
    readonly property real largeSpacing: 16

    // --- Icon Sizes (Standard Plasma sizes) ---
    readonly property int iconSmall: 16
    readonly property int iconMedium: 22
    readonly property int iconLarge: 32

    // --- Animation Timings ---
    // Kirigami uses 150ms for "short" and 250ms for "long" by default.
    readonly property int shortDuration: 150
    readonly property int longDuration: 250

    // Dimensions
    readonly property int toolbarHeight: 22
    readonly property int iconSize: 22
    readonly property int fontSize: 16
    readonly property int borderRadius: 4

    //
    // Typography
    //

    // Weights
    readonly property real _baseSize: Qt.application.font.pointSize
    readonly property real heading: _baseSize * 1.5
    readonly property real regular: _baseSize
    readonly property real small: _baseSize * 0.85
    readonly property real mini: _baseSize * 0.7

    // Weights
    readonly property int weightBold: Font.Bold
    readonly property int weightMedium: Font.Medium

    // Custom fonts
    readonly property font mono: Qt.font( {
        family: "Courier", // Or "Monospace" / "Menlo"
        pointSize: _baseSize * 0.9,
        fixedPitch: true
    })
}