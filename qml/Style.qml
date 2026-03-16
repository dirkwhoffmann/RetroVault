import QtQuick
pragma Singleton

QtObject {

    property SystemPalette _palette: SystemPalette {
        colorGroup: SystemPalette.Active
    }

    // Colors

    readonly property color primary: _palette.windowText
    readonly property color secondary: Qt.rgba(primary.r, primary.g, primary.b, 0.7)
    readonly property color tertiary: Qt.rgba(primary.r, primary.g, primary.b, 0.45)

    readonly property color white:  "#ffffff"
    readonly property color gray:   "#808080"
    readonly property color black:  "#000000"
    readonly property color red:    "#ff6666"
    readonly property color orange: "#ffb266"
    readonly property color yellow: "#ffff66"
    readonly property color green:  "#66ff66"
    readonly property color dgreen: "#009900"
    readonly property color cyan:   "#66ffff"
    readonly property color blue:   "#66b2ff"
    readonly property color purple: "#b266ff"
    readonly property color pink:   "#ff66ff"

    // Layout Units
    readonly property real gridUnit: Qt.application.font.pointSize
    readonly property real tinySpacing: 2
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