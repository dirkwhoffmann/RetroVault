import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Item {
    signal startClicked()

    FontLoader {
        id: brandFont
        source: "../assets/fonts/SourceSans3-VariableFont_wght.ttf"
    }

    // Background Image
    Image {
        anchors.fill: parent
        source: "../assets/images/splash.png"
        fillMode: Image.PreserveAspectCrop
        opacity: 1.0
    }

    ColumnLayout {
        anchors.fill: parent
        spacing: 0

        Rectangle {
            Layout.fillHeight: true
            Layout.fillWidth: true
            color: "transparent"
            clip: true
            Logo { anchors.centerIn: parent }
        }

        Item {
            Layout.preferredHeight: 32
            Layout.fillWidth: true
            // color: "transparent"
            StatusBar { }
        }
    }
}
