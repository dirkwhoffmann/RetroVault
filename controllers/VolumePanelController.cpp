// -----------------------------------------------------------------------------
// This file is part of RetroVault
//
// Copyright (C) Dirk W. Hoffmann. www.dirkwhoffmann.de
// Licensed under the Mozilla Public License v2
//
// See https://mozilla.org/MPL/2.0 for license information
// -----------------------------------------------------------------------------

#include "VolumePanelController.h"
#include "Assets.h"
#include <QColor>
#include <QList>

//
// Table View
//

int
VolumePanelController::BlockViewModel::rowCount(const QModelIndex&) const
{
    if (auto *dev = controller->currentDevice())
        return (int)dev->bsize() / 16;

    return 0;
}

int
VolumePanelController::BlockViewModel::columnCount(const QModelIndex&) const
{
    return 18;
}

QVariant
VolumePanelController::BlockViewModel::data(const QModelIndex& index, int role) const
{
    auto row = index.row();
    auto col = index.column();

    auto *v = controller->currentVolume();
    if (!v) return QVariant();

    auto offset = blkNr * v->stat().bsize + row * 16;

    if (role == Qt::DisplayRole)
    {
        switch (col)
        {
        case 0:

            return QString::asprintf("%02X", row);

        case 17:
            {
                QString ascii;
                ascii.reserve(16);

                for (int i = 0; i < 16; ++i)
                {
                    unsigned char byte = v->getVolume().readByte(offset + i);

                    // isprint() requires <cctype> or <ctype.h>
                    if (isprint(byte))
                    {
                        ascii.append(QChar(byte));
                    }
                    else
                    {
                        ascii.append('.');
                    }
                }
                return ascii;
            }

        default:

            return QString::asprintf("%02X", v->getVolume().readByte(offset + col - 1));
        }
    }

    return QVariant();
}

void
VolumePanelController::BlockViewModel::refresh(int b)
{
    beginResetModel();
    blkNr = b;
    endResetModel();
}

//
// Controller
//

void
VolumePanelController::setBlock(int value)
{
    if (const auto* fv = currentVolume())
    {
        auto tmp = fv->describe();
        value = std::clamp(value, 0, std::max(0, numBlocks - 1));

        if (blkNr != value)
        {
            blkNr = value;
            emit blockChanged();
            tableModel.refresh(blkNr);
        }
    }
}

void
VolumePanelController::setName(QString &value)
{
    name = value;
    emit nameChanged();
}

void
VolumePanelController::setImageFmt(QString &value)
{
    imageFmt = value;
    emit imageFmtChanged();
}

/*
void
VolumePanelController::setIcon(QString &value)
{
    printf("VolumePanelController: setIcon(%s)\n", value.toStdString().c_str());
    icon = value;
    emit iconChanged();
}
*/

void
VolumePanelController::setVolumeInfo(const QVariantList& info)
{
    if (volumeInfo != info)
    {
        volumeInfo = info;
        emit volumeInfoChanged();
    }
}

void
VolumePanelController::refresh()
{
    printf("%p: VolumePanelController::refresh blk: %d\n", this, blkNr);

    QVariantList list;

    if (auto* fv = currentVolume())
    {
        auto stat = fv->stat();
        auto info = fv->describe();
        auto mp = fv->getMountPoint();
        auto title = QString::fromStdString(mp.filename().string());
        auto format = currentImageFormat();

        setNumBlocks(int(stat.blocks));
        setBsize(int(stat.bsize));

        if (title == "") title = "Logical Volume";

        setName(title);
        setImageFmt(format);

        // updateIcon();

        auto txt1 = QString::fromStdString(info.size() > 0 ? info[0] : "");
        auto txt2 = QString::fromStdString(info.size() > 1 ? info[1] : "");
        auto txt3 = "";

        list << txt1;
        list << "Blocks:" << qint64(stat.blocks) << "Cached:" << qint64(stat.cachedBlocks);
        list << txt2;
        list << "Used:" << qint64(stat.usedBlocks) << "Dirty:" << qint64(stat.dirtyBlocks);
        list << txt3;
        list << "Read:" << qint64(fv->reads()) << "Write:" << qint64(fv->writes());

        tableModel.refresh(blkNr);

        emit usagePanelColorsChanged();
        emit legendDataChanged();
    }

    setVolumeInfo(list);
}

QVariantList
VolumePanelController::computeLegend() const
{
    auto fmt = currentImageFormat();
    QVariantList dataList;

    if (fmt == "ADF" || fmt == "ADZ" || fmt == "EADF" || fmt == "HDF" || fmt == "HDZ" || fmt == "DMS")
    {
        dataList += {
            QVariantMap{{"color", getBootBlockColor()}, {"label", QStringLiteral("Boot Block")}},
            QVariantMap{{"color", getBitmapBlockColor()}, {"label", QStringLiteral("Bitmap Block")}},
            QVariantMap{{"color", getDirectoryBlockColor()}, {"label", QStringLiteral("User Directory Block")}},
            QVariantMap{{"color", getListBlockColor()}, {"label", QStringLiteral("File List Block")}},
            QVariantMap{{"color", getRootBlockColor()}, {"label", QStringLiteral("Root Block")}},
            QVariantMap{{"color", getBitmapBlockColor()}, {"label", QStringLiteral("Bitmap Extension Block")}},
            QVariantMap{{"color", getHeaderBlockColor()}, {"label", QStringLiteral("File Header Block")}},
            QVariantMap{{"color", getDataBlockColor()}, {"label", QStringLiteral("Data Block")}}
        };

    } else if (fmt == "D64")
    {
        dataList += {
            QVariantMap{{"color", getRootBlockColor()}, {"label", QStringLiteral("BAM")}},
            QVariantMap{{"color", getDirectoryBlockColor()}, {"label", QStringLiteral("Directory Block")}},
            QVariantMap{{"color", getDataBlockColor()}, {"label", QStringLiteral("Data Block")}},
            QVariantMap{{"color", QColor()}, {"label", QStringLiteral("")}},
            QVariantMap{{"color", QColor()}, {"label", QStringLiteral("")}},
            QVariantMap{{"color", QColor()}, {"label", QStringLiteral("")}},
            QVariantMap{{"color", QColor()}, {"label", QStringLiteral("")}},
            QVariantMap{{"color", QColor()}, {"label", QStringLiteral("")}},
        };
    } else
    {
    }

    return dataList;
}

QList<QColor>
VolumePanelController::getUsagePanelColors() const
{
    auto fmt = currentImageFormat();

    if (fmt == "ADF" || fmt == "ADZ" || fmt == "EADF" || fmt == "HDF" || fmt == "HDZ" || fmt == "DMS")
    {
        return {
            QColor("#ff6666"),              // UNKNOWN
            QColor("#808080"),              // EMPTY
            getBootBlockColor(),            // BOOT
            getRootBlockColor(),            // ROOT
            getBitmapBlockColor(),          // BITMAP
            getBitmapExtBlockColor(),       // BITMAP_EXT
            getDirectoryBlockColor(),       // USERDIR
            getHeaderBlockColor(),          // FILEHEADER
            getListBlockColor(),            // FILELIST
            getDataBlockColor(),            // DATA_OFS
            getDataBlockColor()                // DATA_FFS
        };
    }

    if (fmt == "D64")
    {
        return {
            QColor("#ff6666"),              // UNKNOWN
            QColor("#808080"),              // EMPTY
            getRootBlockColor(),            // BAM
            getDirectoryBlockColor(),       // DIRECTORY
            getDataBlockColor(),            // DATA
        };
    }

    return QList<QColor>();
}

QList<QColor>
VolumePanelController::getAllocPanelColors() const
{
    return {
        QColor("#808080"),                      // GRAY
        getOkColor(),                           // Allocated and used
        getOkColor(),                           // Allocated but unused
        getErrorColor(),                        // Unallocated but used
    };
}

QList<QColor>
VolumePanelController::getSAllocPanelColors() const
{
    return {
        QColor("#808080"),                      // GRAY
        getOkColor(),                           // Allocated and used
        getWarnColor(),                         // Allocated but unused
        getErrorColor(),                        // Unallocated but used
    };
}

QList<QColor>
VolumePanelController::getHealthPanelColors() const
{
    return {
        QColor("#808080"),                      // GRAY
        getOkColor(),                           // Consistend
        getErrorColor(),                        // Erroneous
        QColor("#ffffff")                       // WHITE
    };
}

void
VolumePanelController::gotoNextCorruptedBlock()
{
    if (auto *volume = currentVolume()) {

        const auto &corrupted = volume->blockErrors();

        if (corrupted.empty()) return;

        auto it = std::upper_bound(corrupted.begin(), corrupted.end(), blkNr);

        if (it == corrupted.end()) {
            it = corrupted.begin(); // wrap to first
        }

        setBlock(*it);
    }
}

void
VolumePanelController::gotoPrevCorruptedBlock()
{
    if (auto *volume = currentVolume()) {

        const auto &corrupted = volume->blockErrors();

        if (corrupted.empty()) return;

        auto it = std::lower_bound(corrupted.begin(), corrupted.end(), blkNr);

        if (it != corrupted.begin()) {
            --it; // last element < blkNr
        } else {
            it = corrupted.end() - 1; // wrap to last
        }

        setBlock(*it);
    }
}

void
VolumePanelController::rectifyAllocMap(bool strict)
{
    if (auto *volume = currentVolume())
    {
        volume->rectifyAllocationMap(strict);
    }
}

void
VolumePanelController::rectifyHealthMap(bool strict)
{
    if (auto *volume = currentVolume())
    {
        volume->rectify(strict);
    }
}
