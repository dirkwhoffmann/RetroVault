#pragma once

#include "Controller.h"
#include <QAbstractItemModel>

class DeviceBlockViewModel : public QAbstractTableModel
{
public:

    Controller *controller = nullptr;

    std::optional<isize> m_dev {};
    std::optional<isize> m_blk {};

    int rowCount(const QModelIndex & = QModelIndex()) const override;
    int columnCount(const QModelIndex & = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role) const override;

    void refresh(int dev, int blk);
};

class DevicePanelController : public Controller
{
    Q_OBJECT

    // Device properties
    int m_device = 0;
    QString m_name = "";
    QString m_format = "";
    QString m_icon = "";
    QVariantList m_deviceInfo;

    // Device layout
    int numCylinders = 0;
    int numHeads = 0;
    int numTracks = 0;
    int numSectors = 0;
    int numBlocks = 0;
    int bsize = 0;

    // Block view selection
    int m_cylinder = 0;
    int m_head = 0;
    int m_track = 0;
    int m_sector = 0;
    int m_block = 0;

    // Block view data
    DeviceBlockViewModel m_tableModel;

public:

    // using Controller::Controller;
    explicit DevicePanelController(QObject *parent = nullptr) : Controller(parent)
    {
        m_tableModel.controller = this;
    }

    //
    // Properties
    //

    Q_PROPERTY(int device READ getDevice WRITE setDevice NOTIFY deviceChanged)
    Q_PROPERTY(QString name READ getName NOTIFY nameChanged)
    Q_PROPERTY(QString format READ getFormat NOTIFY formatChanged)
    Q_PROPERTY(QString icon READ getIcon NOTIFY iconChanged)
    Q_PROPERTY(QVariantList deviceInfo READ getDeviceInfo NOTIFY deviceInfoChanged)

    Q_PROPERTY(int numCylinders READ getNumCylinders NOTIFY numCylindersChanged)
    Q_PROPERTY(int numHeads READ getNumHeads NOTIFY numHeadsChanged)
    Q_PROPERTY(int numTracks READ getNumTracks NOTIFY numTracksChanged)
    Q_PROPERTY(int numSectors READ getNumSectors NOTIFY numSectorsChanged)
    Q_PROPERTY(int numBlocks READ getNumBlocks NOTIFY numBlocksChanged)
    Q_PROPERTY(int bsize READ getBsize NOTIFY bsizeChanged)

    Q_PROPERTY(int cylinder READ getCylinder WRITE setCylinder NOTIFY cylinderChanged)
    Q_PROPERTY(int head READ getHead WRITE setHead NOTIFY headChanged)
    Q_PROPERTY(int track READ getTrack WRITE setTrack NOTIFY trackChanged)
    Q_PROPERTY(int sector READ getSector WRITE setSector NOTIFY sectorChanged)
    Q_PROPERTY(int block READ getBlock WRITE setBlock NOTIFY blockChanged)

    Q_PROPERTY(DeviceBlockViewModel* tableModel READ getTableModel NOTIFY tableModelChanged)

private:

    //
    // Getter
    //

    int getDevice() const { return m_device; }
    QString getName() const { return m_name; }
    QString getFormat() const { return m_format; }
    QString getIcon() const { return m_icon; }
    QVariantList getDeviceInfo() const { return m_deviceInfo; }

    int getNumCylinders() const { return numCylinders; }
    int getNumHeads() const { return numHeads; }
    int getNumTracks() const { return numTracks; }
    int getNumSectors() const { return numSectors; }
    int getNumBlocks() const { return numBlocks; }
    int getBsize() const { return bsize; }

    int getCylinder() const { return m_cylinder; }
    int getHead() const { return m_head; }
    int getTrack() const { return m_track; }
    int getSector() const { return m_sector; }
    int getBlock() const { return m_block; }
    DeviceBlockViewModel* getTableModel() { return &m_tableModel; }

    //
    // Getter
    //

    void setDevice(int value);
    void setName(QString value) { m_name = value; emit nameChanged(); }
    void setFormat(QString value) { m_format = value; emit formatChanged(); }
    void setIcon(QString value) { printf("setIcon(%s)\n", value.toStdString().c_str()); m_icon = value; emit iconChanged(); }

    void setNumCylinders(int value) { numCylinders = value; emit numCylindersChanged(); }
    void setNumHeads(int value) { numHeads = value; emit numHeadsChanged();}
    void setNumTracks(int value) { numTracks = value; emit numTracksChanged();}
    void setNumSectors(int value) { numSectors = value; emit numSectorsChanged();}
    void setNumBlocks(int value) { numBlocks = value; emit numBlocksChanged(); }
    void setBsize(int value) { bsize = value; emit bsizeChanged();}

    void setCylinder(int value);
    void setHead(int value);
    void setTrack(int value);
    void setSector(int value);
    void setBlock(int value);
    void setDeviceInfo(const QVariantList &info);

    //
    // Convenience wrappers
    //

    int getMaxCylinder() const { return std::max(0, numCylinders - 1); }
    int getMaxHead() const { return std::max(0, numHeads - 1); }
    int getMaxTrack() const { return std::max(0, numTracks - 1); }
    int getMaxSector() const { return std::max(0, numSectors - 1); }
    int getMaxBlock() const { return std::max(0, numBlocks - 1); }

private:

    void set(int c, int h, int t, int s, int b);

signals:
    void deviceChanged();
    void nameChanged();
    void formatChanged();
    void iconChanged();

    void numCylindersChanged();
    void numHeadsChanged();
    void numTracksChanged();
    void numSectorsChanged();
    void numBlocksChanged();
    void bsizeChanged();

    void cylinderChanged();
    void headChanged();
    void trackChanged();
    void sectorChanged();
    void blockChanged();
    void deviceInfoChanged();
    void tableModelChanged();

public slots:
    void refresh();

private:

    void updateIcon();
};
