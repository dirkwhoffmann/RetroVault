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
            // onStartClicked: mainStack.push(tableViewPage)
        }
    }

    // Component for the Main Table View
    Component {
        id: tableViewPage
        MainTableView {}
    }

    DropArea {
        id: dropArea
        anchors.fill: parent
        // keys: ["text/plain"] // Only accept this specific type

        onDropped: (drop) => {

            if (drop.hasText) {
                console.log("Dropped data:", drop.text)
                // drop.acceptProposedAction()
            }
            if (drop.hasUrls) {
                // 1. Loop through all dropped items
                for (var i = 0; i < drop.urls.length; i++) {
                    let rawUrl = drop.urls[i].toString();

                    // 2. Convert to a clean local path
                    // Using Qt.resolvedUrl or simple regex to remove 'file://'
                    let localPath = rawUrl.replace(/^(file:\/{2})/,"");

                    // On Linux/Kubuntu, the path might still have a leading /
                    // e.g., /home/user/Documents/project.txt
                    console.log("Accepted file:", localPath);
                }
                drop.acceptProposedAction();

                mainStack.push(tableViewPage)
            }
        }
    }
}
