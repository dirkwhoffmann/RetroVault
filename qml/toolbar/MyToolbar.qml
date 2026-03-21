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
import QtQuick.Dialogs
import RetroVault.Controllers
import RetroVault.Assets

ToolBar {

    id: root
    required property WindowController windowController
    property real sidebarWidth: 200

    topPadding: Style.smallSpacing
    bottomPadding: Style.smallSpacing

    contentItem: RowLayout {

        anchors.fill: parent
        spacing: 0

        // DebugRect{}

        Item {

            Layout.preferredWidth: sidebarWidth + 2 * Style.smallSpacing
            Layout.fillHeight: true

            RowLayout {
                anchors.fill: parent

                Item {
                    Layout.fillWidth: true
                }

                NavButton {

                    id: plusButton
                    icon.source: Assets.iconUrl(Assets.Plus)
                    MyToolTip { text: "Mount New Image" }

                    onClicked: {
                        windowController.requestOpenImage()
                    }
                }

                NavButton {

                    id: minusButton
                    icon.source: Assets.iconUrl(Assets.Minus)
                    MyToolTip { text: "Unmount" }

                    onClicked: {
                        windowController.remove()
                    }
                }

                ToolSeparator {
                    Layout.fillHeight: true
                }
            }
        }

        NavButton {

            icon.source: Assets.iconUrl(Assets.Folder)
            enabled: windowController.mountPoint !== ""
            MyToolTip { text: "Open in Finder" }
            onClicked: Qt.openUrlExternally(encodeURI("file://" + windowController.mountPoint));
        }
        NavButton {

            icon.source: Assets.iconUrl(Assets.Sync)
            enabled: windowController.isDirty
            MyToolTip { text: "Update Image on Disk" }

            onClicked: {
                windowController.save()
            }
        }

        Spacer {}

        NavButton {

            icon.source: Assets.iconUrl(windowController.isProtected ? Assets.Locked : Assets.Unlocked)
            enabled: windowController.volume != -1
            MyToolTip { text: windowController.isProtected ? "Unprotect File System" : "Protect File System" }

            onClicked: {
                windowController.toggleProtection()
            }
        }
    }
}