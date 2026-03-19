import QtQuick
pragma Singleton

QtObject {

    //
    // Theme mode
    //
    property string theme: "custom"

    //
    // System palette
    //

    property SystemPalette _palette: SystemPalette {
        colorGroup: SystemPalette.Active
    }

    readonly property bool darkMode: {
        const c = _palette.window
        return (0.299 * c.r + 0.587 * c.g + 0.114 * c.b) < 0.5
    }

    //
    // Base palettes
    //

    readonly property var default_theme: ({

        accent: _palette.highlight,
        alternateBase: _palette.alternateBase,
        base: _palette.base,
        button: _palette.button,
        buttonText: _palette.buttonText,
        dark: _palette.dark,
        highlight: _palette.highlight,
        highlightedText: _palette.highlightedText,
        light: _palette.light,
        mid: _palette.mid,
        midlight: _palette.midlight,
        placeholderText: _palette.placeholderText,
        shadow: _palette.shadow,
        text: _palette.text,
        window: _palette.window,
        windowText: _palette.windowText
    })

    readonly property var custom_light: ({

        // Qt native
        accent: "#0a84ff",              // macOS accent blue
        alternateBase: "#f2f2f7",       // subtle alternating background
        base: "#ffffff",                // main content background
        button: "#f2f2f7",              // buttons (slightly gray)
        buttonText: "#000000",          // primary text on buttons
        dark: "#d1d1d6",                // darker separator gray
        highlight: "#0a84ff",           // selection highlight
        highlightedText: "#ffffff",     // text on highlight
        light: "#ffffff",               // highlights
        mid: "#c7c7cc",                 // mid separator
        midlight: "#e5e5ea",            // lighter separator
        placeholderText: "#8e8e93",     // macOS placeholder gray
        shadow: "#00000022",            // subtle shadow (with alpha)
        text: "#000000",                // primary text
        window: "#f5f5f7",              // window background (NOT pure white!)
        windowText: "#000000"           // main window text
    })

    readonly property var custom_dark: ({

        // Qt native
        accent: "#0a84ff",              // system blue (same as light mode)
        alternateBase: "#2c2c2e",       // subtle alternating background
        base: "#1c1c1e",                // main content background
        button: "#2c2c2e",              // button surface
        buttonText: "#ffffff",
        dark: "#3a3a3c",                // darker separators
        highlight: "#0a84ff",           // selection highlight
        highlightedText: "#ffffff",
        light: "#3a3a3c",               // “light” in dark mode = lighter gray
        mid: "#48484a",                 // mid separator
        midlight: "#636366",            // lighter separator
        placeholderText: "#8e8e93",     // same as light mode (Apple does this)
        shadow: "#00000066",            // stronger shadow in dark mode
        text: "#ffffff",
        window: "#2c2c2e",              // window background
        windowText: "#ffffff"
    })

    //
    // Active base palette
    //

    readonly property var _base: {

        switch (theme) {

            case "custom":
                return darkMode ? custom_dark : custom_light

            default:
                return default_theme
        }
    }

    //
    // Base colors
    //

    readonly property color accent: _base.accent
    readonly property color alternateBase: _base.alternateBase
    readonly property color base: _base.base
    readonly property color button: _base.button
    readonly property color buttonText: _base.buttonText
    readonly property color dark: _base.dark
    readonly property color highlight: _base.highlight
    readonly property color highlightedText: _base.highlightedText
    readonly property color light: _base.light
    readonly property color mid: _base.mid
    readonly property color midlight: _base.midlight
    readonly property color placeholderText: _base.placeholderText
    readonly property color shadow: _base.shadow
    readonly property color text: _base.text
    readonly property color window: _base.window
    readonly property color windowText: _base.windowText

    //
    // Derived colors
    //

    readonly property color primary: windowText
    readonly property color secondary: Qt.rgba(primary.r, primary.g, primary.b, 0.75)
    readonly property color tertiary: Qt.rgba(primary.r, primary.g, primary.b, 0.5)
    // readonly property color secondary: darkMode ? Qt.darker(primary, 1.25) : Qt.lighter(primary, 1.25)
    // readonly property color tertiary: darkMode ? Qt.darker(primary, 1.5) : Qt.lighter(primary, 1.5)

    readonly property color primaryBg: window
    readonly property color secondaryBg: base
    readonly property color tertiaryBg: alternateBase
    // readonly property color secondaryBg: darkMode ? Qt.lighter(primaryBg, 1.2) : Qt.darker(primaryBg, 1.2)
    // readonly property color tertiaryBg: darkMode ? Qt.lighter(secondaryBg, 1.2) : Qt.darker(secondaryBg, 1.2)

    readonly property color separator: darkMode ? "#3c3c4355" : "#3c3c4349"

    readonly property color accentHover: Qt.lighter(accent, 1.2)
    readonly property color accentPressed: Qt.darker(accent, 1.2)
    readonly property color border: Qt.rgba(primary.r, primary.g, primary.b, 0.15)

    //
    // Layout
    //

    readonly property real gridUnit: Qt.application.font.pointSize

    readonly property real smallSpacing: 4
    readonly property real mediumSpacing: 8
    readonly property real largeSpacing: 16

    //
    // Appearance
    //

    readonly property int borderRadius: 4

    //
    // Dimensions
    //

    readonly property int iconSmall: 16
    readonly property int iconMedium: 22
    readonly property int iconLarge: 32

    readonly property int toolbarHeight: 22
    // readonly property int iconSize: 22 // DEPRECATED
    readonly property int fontSize: 16

    //
    // Animations
    //

    readonly property int shortDuration: 150
    readonly property int longDuration: 250

    //
    // Typography
    //

    readonly property real _baseSize: Qt.application.font.pointSize
    readonly property real heading: _baseSize * 1.5
    readonly property real regular: _baseSize
    readonly property real small: _baseSize * 0.85

    readonly property font mono: Qt.font({
        family: "Menlo",
        pointSize: _baseSize * 0.95,
        fixedPitch: true
    })
}