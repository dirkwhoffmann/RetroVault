// -----------------------------------------------------------------------------
// This file is part of RetroVault
//
// Copyright (C) Dirk W. Hoffmann. www.dirkwhoffmann.de
// Licensed under the Mozilla Public License v2
//
// See https://mozilla.org/MPL/2.0 for license information
// -----------------------------------------------------------------------------

#include <QObject>
#include <QUrl>
#include <QtQml>

class Assets : public QObject
{
    Q_OBJECT
    QML_ELEMENT
    QML_SINGLETON

public:

    enum class Icon {

        Unknown,

        // Icons
        ArrowNext,
        ArrowPrev,
        Burger,
        Checked,
        Doctor,
        Eject,
        Folder,
        GitHub,
        Health,
        Locked,
        Minus,
        Plus,
        Search,
        Sync,
        Unchecked,
        Unlocked,
        Vaccine,
        Wrench,

        // Images
        AppIcon,
        Floppy35DD,
        Floppy35HD,
        Floppy525DD,
        HardDrive,
        LEDGreen,
        LEDRed,
        Splash,
        VolumeAmiga,
        VolumeCBM,
        VolumeDOS,
        VolumeST
    };
    Q_ENUM(Icon)

    static Assets* instance() {
        static Assets* inst = new Assets();
        return inst;
    }

    static Assets* create(QQmlEngine *qmlEngine, QJSEngine *jsEngine) {
        Q_UNUSED(qmlEngine)
        Q_UNUSED(jsEngine)
        return instance();
    }

    static QUrl getIconUrl(Icon icon);
    Q_INVOKABLE QUrl iconUrl(Icon icon) const { return getIconUrl(icon); }

private:
    explicit Assets(QObject *parent = nullptr) : QObject(parent) {}
    Q_DISABLE_COPY(Assets) // Prevent accidental copies

public:
    // static QUrl iconUrl(Icon icon);
};