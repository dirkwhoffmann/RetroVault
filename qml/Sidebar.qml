// -----------------------------------------------------------------------------
// This file is part of RetroVault
//
// Copyright (C) Dirk W. Hoffmann. www.dirkwhoffmann.de
// Licensed under the Mozilla Public License v2
//
// See https://mozilla.org/MPL/2.0 for license information
// -----------------------------------------------------------------------------

import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import RetroVault.Controllers
import RetroVault.Theme

Item {
    id: root
    height: parent.height

    required property WindowController windowController
    property bool dragActive: false

    SidebarController {

        id: panelController
        windowController: root.windowController
    }

    Rectangle {

        id: sidebarRect
        anchors.fill: parent
        Palette.theme: Palette.AppDefault
        color: Palette.sidebarBg
        // color: Palette.secondaryBg // "red"

        DropArea {

            id: globalDropArea
            anchors.fill: parent

            onEntered: (drag) => {

                if (drag.hasUrls) {
                    dragActive = true
                    drag.accept(Qt.LinkAction);
                }
            }

            onExited: dragActive = false

            onDropped: (drop) => {

                dragActive = false
                if (drop.hasUrls) {
                    for (var i = 0; i < drop.urls.length; i++) {
                        console.log("Dropped file:", drop.urls[i]);
                        windowController.addImage(drop.urls[i])
                    }
                    drop.acceptProposedAction();
                }
            }
        }

        Rectangle {
            anchors.fill: parent
            color: "transparent"
            border.color: dragActive ? Style.border : "transparent"
            border.width: 4
        }

        Label {
            anchors.centerIn: parent
            text: qsTr("Click the '+' button or drag and drop to add an image")
            visible: windowController.numDevices === 0
            color: Palette.tertiary
            font.pointSize: Style.regular * 1.25
            horizontalAlignment: Text.AlignHCenter
            wrapMode: Text.WordWrap
            width: parent.width * 0.8
        }

        TreeView {

            id: treeView
            anchors {
                left: parent.left
                top: parent.top
                bottom: parent.bottom
                right: parent.right
            }
            clip: true
            alternatingRows: true
            model: panelController.sidebarModel
            selectionMode: TreeView.SingleSelection
            selectionModel: ItemSelectionModel {
            }
            columnWidthProvider: function (column) {
                return treeView.width
            }

            delegate: TreeViewDelegate {

                id: myDelegate
                required property string iconSource
                required property string title
                required property string subtitle
                required property int deviceId
                required property int volumeId
                required property bool isDevice

                width: treeView.width

                contentItem: RowLayout {

                    spacing: 8

                    Image {
                        source: iconSource
                        sourceSize: Qt.size(36, 36)
                        Layout.alignment: Qt.AlignVCenter
                    }

                    Item {
                        Layout.preferredHeight: 50
                        Layout.preferredWidth: 2
                    }

                    ColumnLayout {

                        Layout.fillWidth: true
                        Layout.alignment: Qt.AlignVCenter

                        Label {
                            text: title
                            font.bold: isDevice
                            color: highlighted ? "white" : treeView.palette.text
                            Layout.fillWidth: true
                            elide: Text.ElideRight
                        }
                        Label {
                            text: subtitle
                            visible: subtitle !== ""
                            font.pixelSize: 11
                            color: highlighted ? "white" : treeView.palette.text
                            Layout.fillWidth: true
                            elide: Text.ElideRight
                        }
                    }
                }

                TapHandler {

                    onTapped: {

                        windowController.select(deviceId, volumeId);
                    }
                }
            }
        }
    }

    function refresh() {
        panelController.refresh()
    }
}