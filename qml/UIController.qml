pragma Singleton
import QtQuick

Item {
    objectName: "uiController"

    signal requestErrorDialog(string message)

    function showError(msg) {
        requestErrorDialog(msg)
    }
}