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

RoundButton {

    id: control

    property url imageSource: ""
    property real size: Style.iconLarge
    property real iconScale: 0.8

    implicitWidth: size
    implicitHeight: size
    padding: 0
    radius: 4

    icon.source: imageSource
    icon.color: Palette.secondary
    icon.width: size * iconScale
    icon.height: size * iconScale
}