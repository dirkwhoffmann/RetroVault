//
// Created by Dirk Hoffmann on 06.03.26.
//

#include "VolumePanelController.h"


//
// Table View
//

int
VolumePanelController::BlockViewModel::rowCount(const QModelIndex &) const
{
    if (devNr >= 0 && controller)
      if (const auto *fd = controller->fuseDevice(devNr))
            return (int)fd->bsize() / 16;

    return 0;
}

int
VolumePanelController::BlockViewModel::columnCount(const QModelIndex &) const
{
    return 18;
}

QVariant
VolumePanelController::BlockViewModel::data(const QModelIndex& index, int role) const
{
    auto row = index.row();
    auto col = index.column();

    auto *v = controller->fuseVolume(devNr, volNr);
    auto bsize = v->stat().bsize;

    // auto image = controller->fuseDevice(*m_dev)->getImage();

    if (role == Qt::DisplayRole) {

        switch (col)
        {
        case 0:

            return QString::asprintf("%02X", row);

        case 17:
            {
                QString ascii;
                ascii.reserve(16);

                for (int i = 0; i < 16; ++i) {

                    auto offset = blkNr * bsize + row * 16 + i;
                    unsigned char byte = v->getVolume().readByte(offset);

                    // isprint() requires <cctype> or <ctype.h>
                    if (isprint(byte)) {
                        ascii.append(QChar(byte));
                    } else {
                        ascii.append('.');
                    }
                }
                return ascii;
            }

        default:

            auto offset = blkNr * bsize + row * 16 + (col - 1);
            return QString::asprintf("%02X", v->getVolume().readByte(offset));
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
    printf("setDevice: %d\n", value);
    devNr = value;
    refresh();
    emit deviceChanged();
}

void
VolumePanelController::setVolume(int value)
{
    printf("setVolume: %d\n", value);
    volNr = value;
    refresh();
    emit volumeChanged();
}

void
VolumePanelController::setBlock(int value)
{
    if (const auto* fv = fuseVolume(devNr, volNr))
    {
        auto tmp = fv->describe();
        value = std::clamp(value, 0, std::max(0, 42)); //   get numBlocks() - 1));

        if (blkNr != value)
        {
            blkNr = value;
            emit blockChanged();
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
VolumePanelController::setVolumeInfo(const QVariantList &info)
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

    if (auto *fv = fuseVolume(devNr, volNr))
    {
        auto stat = fv->stat();
        auto info = fv->describe();
        auto mp = fv->getMountPoint();
        auto title = mp.filename().string();

        if (title.empty())
        {
            // auto *image = fuseDevice(devNr)->getImage();
            // title = image->path.string();
            title = "Logical Volume " + std::to_string(volNr + 1);
        }
    /*
    manager()->vol
    let description = proxy!.describe()
        info = app.manager.info(device: device!, volume: volume!)

        icon.image = info.icon()
        icon.mountPoint = info.mountPoint
        mainTitle.stringValue = info.name
        subTitle1.stringValue = description?[safe: 0] ?? ""
        subTitle2.stringValue = description?[safe: 1] ?? ""
        subTitle3.stringValue = description?[safe: 2] ?? ""

        blockStepper.minValue = Double(0)
        blockStepper.maxValue = Double(info.blocks - 1)
        blockSlider.minValue = 0
        blockSlider.maxValue = Double(info.blocks - 1)
        allocSlider.minValue = 0
        allocSlider.maxValue = Double(info.blocks - 1)
        diagnoseSlider.minValue = 0
        diagnoseSlider.maxValue = Double(info.blocks - 1)
    */

        // auto *image = device->getImage();

        // auto &path = image->path;

        setName(QString::fromStdString(title)); //  mp.filename().string()));

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
    }

    setVolumeInfo(list);
}
