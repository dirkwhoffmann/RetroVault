#pragma once

#include "Controller.h"
#include <QAbstractItemModel>

class VolumePanelController : public Controller
{
    Q_OBJECT

    class BlockViewModel : public QAbstractTableModel
    {
    public:
        Controller* controller = nullptr;

        int devNr = -1;
        int volNr = -1;
        int blkNr = 0;

        BlockViewModel(Controller* c) : controller(c)
        {
        }

        int rowCount(const QModelIndex& = QModelIndex()) const override;
        int columnCount(const QModelIndex& = QModelIndex()) const override;
        QVariant data(const QModelIndex& index, int role) const override;

        void refresh(int d, int v, int b);
    };

    int numBlocks = 0;
    int bsize = 0;
    int devNr = -1;
    int volNr = -1;
    int blkNr = 0;
    QString name = "";
    QVariantList volumeInfo;
    BlockViewModel tableModel = BlockViewModel(this);

public:
    // using Controller::Controller;
    explicit VolumePanelController(QObject* parent = nullptr) : Controller(parent)
    {
        tableModel.controller = this;
    }

    Q_PROPERTY(int numBlocks READ getNumBlocks NOTIFY numBlocksChanged)
    Q_PROPERTY(int bsize READ getBsize NOTIFY bsizeChanged)
    Q_PROPERTY(int device READ getDevice WRITE setDevice NOTIFY deviceChanged)
    Q_PROPERTY(int volume READ getVolume WRITE setVolume NOTIFY volumeChanged)
    Q_PROPERTY(QString name READ getName NOTIFY nameChanged)
    Q_PROPERTY(QVariantList volumeInfo READ getVolumeInfo NOTIFY volumeInfoChanged)
    Q_PROPERTY(BlockViewModel* tableModel READ getTableModel NOTIFY tableModelChanged)
    Q_PROPERTY(int block READ getBlock WRITE setBlock NOTIFY blockChanged)

    int getNumBlocks() const { return numBlocks; }
    int getBsize() const { return bsize; }
    int getDevice() const { return devNr; }
    int getVolume() const { return volNr; }
    int getBlock() const { return blkNr; }
    QString getName() const { return name; }
    QVariantList getVolumeInfo() const { return volumeInfo; }
    BlockViewModel* getTableModel() { return &tableModel; }

    void setNumBlocks(int value) { numBlocks = value; emit numBlocksChanged(); }
    void setBsize(int value) { bsize = value; emit bsizeChanged(); }
    void setDevice(int value);
    void setVolume(int value);
    void setBlock(int value);
    void setName(QString value);
    void setVolumeInfo(const QVariantList& info);

signals:
    void numBlocksChanged();
    void bsizeChanged();
    void deviceChanged();
    void volumeChanged();
    void blockChanged();
    void nameChanged();
    void volumeInfoChanged();
    void tableModelChanged();

public slots:
    void refresh();
};
