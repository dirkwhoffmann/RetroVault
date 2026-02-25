import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Effects
import QtGraphs

ApplicationWindow {
    width: 800
    height: 600
    visible: true
    title: "RetroVault"
    // flags: Qt.Window | Qt.CustomizeWindowHint | Qt.WindowTitleHint

    StackView {
        id: mainStack
        anchors.fill: parent
        // The first page to show
        initialItem: splashPage
    }

    // Component for the Splash Screen
    Component {
        id: splashPage
        SplashView {
            onStartClicked: mainStack.push(tableViewPage)
        }
    }

    // Component for the Main Table View
    Component {
        id: tableViewPage
        MainTableView {}
    }
}
