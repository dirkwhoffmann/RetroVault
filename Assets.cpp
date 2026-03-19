// -----------------------------------------------------------------------------
// This file is part of RetroVault
//
// Copyright (C) Dirk W. Hoffmann. www.dirkwhoffmann.de
// Licensed under the Mozilla Public License v2
//
// See https://mozilla.org/MPL/2.0 for license information
// -----------------------------------------------------------------------------

#include "Assets.h"

QUrl
Assets::getIconUrl(Icon icon)
{
    switch (icon)
    {
        case Assets::Unknown:       return QUrl("qrc:/assets/icons/questionmark.svg");

        case Assets::ArrowNext:     return QUrl("qrc:/assets/icons/arrow-next.svg");
        case Assets::ArrowPrev:     return QUrl("qrc:/assets/icons/arrow-prev.svg");
        case Assets::Burger:        return QUrl("qrc:/assets/icons/burger.svg");
        case Assets::Checked:       return QUrl("qrc:/assets/icons/checked.svg");
        case Assets::Eject:         return QUrl("qrc:/assets/icons/eject.svg");
        case Assets::Folder:        return QUrl("qrc:/assets/icons/folder.svg");
        case Assets::GitHub:        return QUrl("qrc:/assets/icons/github.svg");
        case Assets::Health:        return QUrl("qrc:/assets/icons/health.svg");
        case Assets::Locked:        return QUrl("qrc:/assets/icons/locked.svg");
        case Assets::Minus:         return QUrl("qrc:/assets/icons/minus.svg");
        case Assets::Plus:          return QUrl("qrc:/assets/icons/plus.svg");
        case Assets::Search:        return QUrl("qrc:/assets/icons/search.svg");
        case Assets::Sync:          return QUrl("qrc:/assets/icons/sync.svg");
        case Assets::Unchecked:     return QUrl("qrc:/assets/icons/unchecked.svg");
        case Assets::Unlocked:      return QUrl("qrc:/assets/icons/unlocked.svg");
        case Assets::Wrench:        return QUrl("qrc:/assets/icons/wrench.svg");

        case Assets::AppIcon:       return QUrl("qrc:/assets/images/AppIcon.png");
        case Assets::Floppy35DD:    return QUrl("qrc:/assets/images/floppy35_dd.png");
        case Assets::Floppy35HD:    return QUrl("qrc:/assets/images/floppy35_hd.png");
        case Assets::Floppy525DD:   return QUrl("qrc:/assets/images/floppy525_dd.png");
        case Assets::HardDrive:     return QUrl("qrc:/assets/images/harddrive.png");
        case Assets::LEDGreen:      return QUrl("qrc:/assets/images/LEDgreen.png");
        case Assets::LEDRed:        return QUrl("qrc:/assets/images/LEDred.png");
        case Assets::Splash:        return QUrl("qrc:/assets/images/splash.png");
        case Assets::VolumeAmiga:   return QUrl("qrc:/assets/images/volume_amiga.png");
        case Assets::VolumeCBM:     return QUrl("qrc:/assets/images/volume_cbm.png");
        case Assets::VolumeDOS:     return QUrl("qrc:/assets/images/volume_dos.png");
        case Assets::VolumeST:      return QUrl("qrc:/assets/images/volume_st.png");

    // default:
    //     return QUrl("");
    }
}
