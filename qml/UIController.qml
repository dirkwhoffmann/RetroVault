pragma Singleton
import QtQuick

Item {
    signal requestErrorDialog(string message)

    function showError(msg) {
        requestErrorDialog(msg)
    }
}