//
// Created by Dirk Hoffmann on 06.03.26.
//

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
            QVariantMap{{"color", QColor("#ffb266")}, {"label", QStringLiteral("Boot Block")}},
            QVariantMap{{"color", QColor("#b266ff")}, {"label", QStringLiteral("Bitmap Block")}},
            QVariantMap{{"color", QColor("#ffff66")}, {"label", QStringLiteral("User Directory Block")}},
            QVariantMap{{"color", QColor("#009900")}, {"label", QStringLiteral("File List Block")}},
            QVariantMap{{"color", QColor("#ff6666")}, {"label", QStringLiteral("Root Block")}},
            QVariantMap{{"color", QColor("#ff66ff")}, {"label", QStringLiteral("Bitmap Extension Block")}},
            QVariantMap{{"color", QColor("#66b2ff")}, {"label", QStringLiteral("File Header Block")}},
            QVariantMap{{"color", QColor("#66ff66")}, {"label", QStringLiteral("Data Block")}}
        };

    } else if (fmt == "D64")
    {
        dataList += {
            QVariantMap{{"color", QColor("#ff6666")}, {"label", QStringLiteral("BAM")}},
            QVariantMap{{"color", QColor("#ffff66")}, {"label", QStringLiteral("Directory Block")}},
            QVariantMap{{"color", QColor("#66ff66")}, {"label", QStringLiteral("Data Block")}},
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
        QColor("#808080"),                  // GRAY
        getOkColor(),                       // Allocated and used
        getWarnColor(),                     // Allocated but unused
        getErrorColor(),                    // Unallocated but used
    };
}

QList<QColor>
VolumePanelController::getHealthPanelColors() const
{
    return {
        QColor("#808080"),                  // GRAY
        getOkColor(),                       // Consistend
        getWarnColor(),                     // Erroneous
        QColor("#ffffff")                   // WHITE
    };
}

/*
void
VolumePanelController::updateIcon()
{
    static const std::unordered_map<string, Assets::Icon> formatSuffixes = {
        {"ADF", Assets::VolumeAmiga},
        {"ADZ", Assets::VolumeAmiga},
        {"EADF", Assets::VolumeAmiga},
        {"DMS", Assets::VolumeAmiga},
        {"IMG", Assets::VolumeDOS},
        {"ST", Assets::VolumeST},
        {"D64", Assets::VolumeCBM}
    };

    auto url = QString();
    if (auto it = formatSuffixes.find(imageFmt.toStdString()); it != formatSuffixes.end())
    {
        url = Assets::getIconUrl(it->second).toString();
    }
    setIcon(url);
}
*/