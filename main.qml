import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

ApplicationWindow {
    width: 640
    height: 480
    visible: true
    title: "vBoard Desktop"

    // This allows the UI to "Listen" to the C++ object
    Connections {
        target: cppBackend

        // Signal names in C++ become 'onSignalName' (camelCase) in QML
        function onStatusChanged(newStatus) {
            statusLabel.text = "C++ says: " + newStatus
            statusLabel.color = "blue"
        }
        function onUpdateFinished(newText) {
            console.log("onUpdateFinished")
            myDisplayField.text = newText
        }
    }

    // Use a ColumnLayout to stack items vertically with padding
    ColumnLayout {
        anchors.centerIn: parent
        spacing: 20

        Label {
            id: statusLabel
            text: "Waiting for C++..."
            font.pixelSize: 18
        }

        // 1. A Standard Button
        Button {
            text: "Click Me"
            Layout.preferredWidth: 200
            onClicked: {
                console.log("Button was clicked!")
                cppBackend.handleButtonClick("Hello from the UI!")
            }
        }

        // 2. A Slider
        Slider {
            id: controlSlider
            from: 0
            to: 100
            value: 50
            Layout.preferredWidth: 200
        }

        // 3. A Dropdown Box (ComboBox)
        ComboBox {
            model: ["Option 1", "Option 2", "Option 3"]
            Layout.preferredWidth: 200
            onActivated: (index) => console.log("Selected:", textAt(index))
        }

        // Just to show the slider value
        Text {
            id: myDisplayField
            text: "Value: " + Math.floor(controlSlider.value)
            Layout.alignment: Qt.AlignHCenter
        }
    }
}

/*
import QtQuick
import QtQuick.Controls

ApplicationWindow {
    width: 640
    height: 480
    visible: true
    title: "My Desktop App"

    Label {
        text: "Hello from Qt Quick!"
        anchors.centerIn: parent
        font.pixelSize: 24
    }
}
*/