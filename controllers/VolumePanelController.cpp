//
// Created by Dirk Hoffmann on 06.03.26.
//

#include "VolumePanelController.h"
#include "Assets.h"
#include <QColor>
#include <QList>

#include "Model.h"

//
// Table View
//

int
VolumePanelController::BlockViewModel::rowCount(const QModelIndex&) const
{
    if (auto *dev = controller->model->currentDevice())
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

    auto *v = controller->model->currentVolume();
    auto offset = blkNr * v->stat().bsize + row * 16;

    // auto bsize = v->stat().bsize;

    // auto image = controller->fuseDevice(*m_dev)->getImage();

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
VolumePanelController::BlockViewModel::refresh(int d, int v, int b)
{
    beginResetModel();
    devNr = d;
    volNr = v;
    blkNr = b;
    endResetModel();
}

//
// Controller
//

void
VolumePanelController::setDevice(int value)
{
    devNr = value;
    refresh();
    emit deviceChanged();
}

void
VolumePanelController::setVolume(int value)
{
    volNr = value;
    refresh();
    emit volumeChanged();
}

void
VolumePanelController::setBlock(int value)
{
    if (const auto* fv = model->currentVolume())
    {
        auto tmp = fv->describe();
        value = std::clamp(value, 0, std::max(0, 42)); //   get numBlocks() - 1));

        if (blkNr != value)
        {
            blkNr = value;
            emit blockChanged();
            tableModel.refresh(devNr, volNr, blkNr);
        }
    }
}

void
VolumePanelController::setName(QString value)
{
    name = value;
    emit nameChanged();
}

void
VolumePanelController::setImageFmt(QString value)
{
    imageFmt = value;
    emit imageFmtChanged();
}

void
VolumePanelController::setIcon(QString value)
{
    printf("VolumePanelController: setIcon(%s)\n", value.toStdString().c_str());
    icon = value;
    emit iconChanged();
}

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
    printf("VolumePanelController::refresh dev: %d vol: %d blk: %d\n", devNr, volNr, blkNr);

    QVariantList list;

    if (auto* fv = model->currentVolume())
    {
        auto stat = fv->stat();
        auto info = fv->describe();
        auto mp = fv->getMountPoint();
        auto title = mp.filename().string();

        setNumBlocks(int(stat.blocks));
        setBsize(int(stat.bsize));

        if (title.empty())
        {
            // auto *image = fuseDevice(devNr)->getImage();
            // title = image->path.string();
            title = "Logical Volume " + std::to_string(volNr + 1);
        }


        // auto &path = image->path;

        setName(QString::fromStdString(title)); //  mp.filename().string()));
        setImageFmt(ImageFormatEnum::key(model->currentImage()->format()));

        updateIcon();

        auto txt1 = QString::fromStdString(info.size() > 0 ? info[0] : "");
        auto txt2 = QString::fromStdString(info.size() > 1 ? info[1] : "");
        auto txt3 = "";

        list << txt1;
        list << "Blocks:" << qint64(stat.blocks) << "Cached:" << qint64(stat.cachedBlocks);
        list << txt2;
        list << "Used:" << qint64(stat.usedBlocks) << "Dirty:" << qint64(stat.dirtyBlocks);
        list << txt3;
        list << "Read:" << qint64(fv->reads()) << "Write:" << qint64(fv->writes());

        tableModel.refresh(devNr, volNr, blkNr);

        emit legendDataChanged();
    }

    setVolumeInfo(list);
}

QVariantList
VolumePanelController::computeLegend() const
{
    QVariantList dataList;

    auto fmt = imageFmt.toStdString();

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

    if (auto it = formatSuffixes.find(imageFmt.toStdString()); it != formatSuffixes.end())
    {
        setIcon(Assets::getIconUrl(it->second).toString());
    }
    else
    {
        setIcon("");
    }
}
