//
// Created by Dirk Hoffmann on 06.03.26.
//

#include "DevicePanelController.h"
#include "Assets.h"

//
// Table View
//

int
DeviceBlockViewModel::rowCount(const QModelIndex &) const
{
    if (auto *dev = controller->model->currentDevice())
    {
        return (int)dev->bsize() / 16;
    }
    return 0;
}

int
DeviceBlockViewModel::columnCount(const QModelIndex &) const
{
    return 18;
}

QVariant
DeviceBlockViewModel::data(const QModelIndex& index, int role) const
{
    auto row = index.row();
    auto col = index.column();

    auto *image = controller->model->currentImage();

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

                    auto offset = *m_blk * image->bsize() + row * 16 + i;
                    unsigned char byte = image->readByte(offset);

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

            auto offset = *m_blk * image->bsize() + row * 16 + (col - 1);
            return QString::asprintf("%02X", image->readByte(offset));
        }
    }

    return QVariant();
}

void
DeviceBlockViewModel::refresh(int dev, int blk)
{
    m_dev = dev;
    m_blk = blk;

    printf("BlockTableModel::refresh: %d:%d\n", dev, blk);
    beginResetModel();
    endResetModel();
}


//
// Controller
//

void
DevicePanelController::setDevice(int value)
{
    m_device = value;
    refresh();
    emit deviceChanged();
}

void
DevicePanelController::setCylinder(int value)
{
    if (const auto *img = model->currentImage()) {

        value = std::clamp(value, 0, std::max(0, numCylinders - 1));

        auto c = value;
        auto h = m_head;
        auto t = numHeads * c + h;
        auto s = std::clamp(m_sector, 0, (int)img->maxSector(t));
        auto b = img->bindex(TrackDevice::CHS(c, h, s));

        set(int(c), int(h), int(t), int(s), int(b));
    }
}

void
DevicePanelController::setHead(int value)
{
    if (const auto *img = model->currentImage()) {

        value = std::clamp(value, 0, std::max(0, numHeads - 1));

        auto h = value;
        auto c = m_cylinder;
        auto t = numHeads * c + h;
        auto s = std::clamp(m_sector, 0, (int)img->maxSector(t));
        auto b = img->bindex(TrackDevice::CHS(c, h, s));

        set(int(c), int(h), int(t), int(s), int(b));
    }
}

void
DevicePanelController::setTrack(int value)
{
    if (const auto *img = model->currentImage()) {

        value = std::clamp(value, 0, std::max(0, numTracks - 1));

        auto t = value;
        auto c = t / numHeads;
        auto h = t % numHeads;
        auto s = std::clamp(m_sector, 0, (int)img->maxSector(t));
        auto b = img->bindex(TrackDevice::CHS(c, h, s));

        set(int(c), int(h), int(t), int(s), int(b));
    }
}

void
DevicePanelController::setSector(int value)
{
    if (const auto *img = model->currentImage()) {

        auto c = m_cylinder;
        auto h = m_head;
        auto t = m_track;
        auto s = std::clamp(value, 0, (int)img->maxSector(t));
        auto b = img->bindex(TrackDevice::CHS(c, h, s));

        set(int(c), int(h), int(t), int(s), int(b));
    }
}

void
DevicePanelController::setBlock(int value)
{
    if (const auto *img = model->currentImage()) {

        value = std::clamp(value, 0, std::max(0, numBlocks - 1));

        auto b = value;
        auto c = img->b2chs(b).cylinder;
        auto h = img->b2chs(b).head;
        auto t = img->b2ts(b).track;
        auto s = img->b2chs(b).sector;

        set(int(c), int(h), int(t), int(s), int(b));
    }
}

void
DevicePanelController::setDeviceInfo(const QVariantList &info)
{
    if (m_deviceInfo != info)
    {
        m_deviceInfo = info;
        emit deviceInfoChanged();
    }
}

void
DevicePanelController::set(int c, int h, int t, int s, int b)
{
    bool cChanged = c != m_cylinder;
    bool hChanged = h != m_head;
    bool tChanged = t != m_track;
    bool sChanged = s != m_sector;
    bool bChanged = b != m_block;

    m_cylinder = c;
    m_head = h;
    m_track = t;
    m_sector = s;
    m_block = b;

    if (cChanged || hChanged || tChanged || sChanged || bChanged)
    {
        if (cChanged) { emit cylinderChanged(); }
        if (hChanged) { emit headChanged(); }
        if (tChanged) { emit trackChanged(); }
        if (sChanged) { emit sectorChanged(); }
        if (bChanged) { emit blockChanged(); }

        m_tableModel.refresh(m_device, m_block);
    }
}

void
DevicePanelController::refresh()
{
    printf("DevicePanelController::refresh device: %d block: %d\n", m_device, m_block);

    QVariantList list;

    if (auto *device =  model->currentDevice())
    {
        auto *image = device->getImage();
        auto info = image->describeImage();
        auto &path = image->path;

        setName(QString::fromStdString(path.string()));
        setNumCylinders(int(image->numCyls()));
        setNumTracks(int(image->numTracks()));
        setNumHeads(int(image->numHeads()));
        setNumSectors(int(image->numSectors(m_track)));
        setNumBlocks(int(image->numBlocks()));
        setBsize(int(image->bsize()));
        setFormat(ImageFormatEnum::key(image->format()));

        updateIcon();

        // Device description
        auto txt1 = QString::fromStdString(info.size() > 0 ? info[0] : "");
        auto txt2 = QString::fromStdString(info.size() > 1 ? info[1] : "");
        auto txt3 = "";

        list << txt1 << "Cylinders:" << numCylinders << "     Blocks:" << numBlocks;
        list << txt2 << "Heads:" << numHeads << "      Block size:" << bsize;
        list << txt3 << "Sectors:" << "TODO" << "" << "";

        m_tableModel.refresh(m_device, m_block);
    }

    setDeviceInfo(list);
}

void
DevicePanelController::updateIcon()
{
    static const std::unordered_map<string, Assets::Icon> formatSuffixes = {
        {"ADF", Assets::Floppy35DD},
        {"ADZ", Assets::Floppy35DD},
        {"EADF", Assets::Floppy35DD},
        {"DMS", Assets::Floppy35DD},
        {"IMG", Assets::Floppy35DD},
        {"ST", Assets::Floppy35DD},
        {"D64", Assets::Floppy525DD}
    };

    if (auto it = formatSuffixes.find(m_format.toStdString()); it != formatSuffixes.end())
    {
        setIcon(Assets::getIconUrl(it->second).toString());
    }
    else
    {
        setIcon("");
    }
}
