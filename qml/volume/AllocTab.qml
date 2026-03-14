import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import RetroVault.Controllers

Item {

    id: root
    required property WindowController windowController
    required property VolumePanelController panelController
    required property Scanner scanner

    Rectangle { anchors.fill: parent; color: "red" }
}