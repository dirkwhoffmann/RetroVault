import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Item {
    id: root

    // property alias image: imageButton
    property alias imageSource: imageButton.imageSource
    property alias size: imageButton.size
    property alias hovered: imageButton.hovered
    property bool busy: false

    signal clicked()

    implicitWidth: imageButton.width
    implicitHeight: imageButton.height

    ImageButton {
        id: imageButton
        anchors.centerIn: parent
        visible: !root.busy
        onClicked: root.clicked()
    }

    BusyIndicator {
        id: indicator
        anchors.centerIn: parent
        width: root.size
        height: root.size
        visible: root.busy
        running: root.busy
        padding: 2
    }
}
