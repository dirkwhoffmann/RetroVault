import QtQuick
import QtQuick.Controls

ApplicationWindow {
    id: root
    visible: true

    // The main application window
    Component {
        id: appWindow
        AppWindow {}
    }

    function createAppWindow(name) {
        return appWindow.createObject(root, {
            "title": name
        });
    }

    Component.onCompleted: {
        // Create the application window
        createAppWindow("RetroVault");

        // Ensure the root window is hidden
        root.hide();

        console.log("App started.");
    }
}
