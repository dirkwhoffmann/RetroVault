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
        case Icon::Unknown:       return QUrl("qrc:/assets/icons/questionmark.svg");

        case Icon::ArrowNext:     return QUrl("qrc:/assets/icons/arrow-next.svg");
        case Icon::ArrowPrev:     return QUrl("qrc:/assets/icons/arrow-prev.svg");
        case Icon::Burger:        return QUrl("qrc:/assets/icons/burger.svg");
        case Icon::Checked:       return QUrl("qrc:/assets/icons/checked.svg");
        case Icon::Doctor:        return QUrl("qrc:/assets/icons/doctor.svg");
        case Icon::Eject:         return QUrl("qrc:/assets/icons/eject.svg");
        case Icon::Folder:        return QUrl("qrc:/assets/icons/folder.svg");
        case Icon::GitHub:        return QUrl("qrc:/assets/icons/github.svg");
        case Icon::Health:        return QUrl("qrc:/assets/icons/health.svg");
        case Icon::Locked:        return QUrl("qrc:/assets/icons/locked.svg");
        case Icon::Minus:         return QUrl("qrc:/assets/icons/minus.svg");
        case Icon::Plus:          return QUrl("qrc:/assets/icons/plus.svg");
        case Icon::Search:        return QUrl("qrc:/assets/icons/search.svg");
        case Icon::Sync:          return QUrl("qrc:/assets/icons/sync.svg");
        case Icon::Unchecked:     return QUrl("qrc:/assets/icons/unchecked.svg");
        case Icon::Unlocked:      return QUrl("qrc:/assets/icons/unlocked.svg");
        case Icon::Vaccine:       return QUrl("qrc:/assets/icons/vaccine.svg");
        case Icon::Wrench:        return QUrl("qrc:/assets/icons/wrench.svg");

        case Icon::AppIcon:       return QUrl("qrc:/assets/images/AppIcon.png");
        case Icon::Floppy35DD:    return QUrl("qrc:/assets/images/floppy35_dd.png");
        case Icon::Floppy35HD:    return QUrl("qrc:/assets/images/floppy35_hd.png");
        case Icon::Floppy525DD:   return QUrl("qrc:/assets/images/floppy525_dd.png");
        case Icon::HardDrive:     return QUrl("qrc:/assets/images/harddrive.png");
        case Icon::LEDGreen:      return QUrl("qrc:/assets/images/LEDgreen.png");
        case Icon::LEDRed:        return QUrl("qrc:/assets/images/LEDred.png");
        case Icon::Splash:        return QUrl("qrc:/assets/images/splash.png");
        case Icon::VolumeAmiga:   return QUrl("qrc:/assets/images/volume_amiga.png");
        case Icon::VolumeCBM:     return QUrl("qrc:/assets/images/volume_cbm.png");
        case Icon::VolumeDOS:     return QUrl("qrc:/assets/images/volume_dos.png");
        case Icon::VolumeST:      return QUrl("qrc:/assets/images/volume_st.png");
    }
}
