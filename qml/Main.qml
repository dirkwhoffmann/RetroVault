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
