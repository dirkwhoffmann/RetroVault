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

    // Selected volume
    int devNr = -1;
    int volNr = -1;

    // Volume properties
    QString name = "";
    QString imageFmt = "";
    QString icon = "";
    QVariantList volumeInfo;

    // Volume layout
    int numBlocks = 0;
    int bsize = 0;

    // Block view selection
    int blkNr = 0;

    // Block view data
    BlockViewModel tableModel = BlockViewModel(this);

public:
    // using Controller::Controller;
    explicit VolumePanelController(QObject* parent = nullptr) : Controller(parent)
    {
        tableModel.controller = this;
    }

    //
    // Properties
    //

    Q_PROPERTY(int device READ getDevice WRITE setDevice NOTIFY deviceChanged)
    Q_PROPERTY(int volume READ getVolume WRITE setVolume NOTIFY volumeChanged)
    Q_PROPERTY(QString name READ getName NOTIFY nameChanged)
    Q_PROPERTY(QString imageFmt READ getImageFmt NOTIFY imageFmtChanged)
    Q_PROPERTY(QString icon READ getIcon NOTIFY iconChanged)
    Q_PROPERTY(QVariantList volumeInfo READ getVolumeInfo NOTIFY volumeInfoChanged)

    Q_PROPERTY(int numBlocks READ getNumBlocks NOTIFY numBlocksChanged)
    Q_PROPERTY(int bsize READ getBsize NOTIFY bsizeChanged)

    Q_PROPERTY(int block READ getBlock WRITE setBlock NOTIFY blockChanged)
    Q_PROPERTY(BlockViewModel* tableModel READ getTableModel NOTIFY tableModelChanged)

    Q_PROPERTY(QVariantList legendData READ getLegendData NOTIFY legendDataChanged)

private:

    //
    // Getter
    //

    int getDevice() const { return devNr; }
    int getVolume() const { return volNr; }
    QString getName() const { return name; }
    QString getImageFmt() const { return imageFmt; }
    QString getIcon() const { return icon; }
    QVariantList getVolumeInfo() const { return volumeInfo; }

    int getNumBlocks() const { return numBlocks; }
    int getBsize() const { return bsize; }

    int getBlock() const { return blkNr; }
    BlockViewModel* getTableModel() { return &tableModel; }

    QVariantList getLegendData() const { return computeLegend(); }

    //
    // Getter
    //

    void setDevice(int value);
    void setVolume(int value);
    void setName(QString value);
    void setImageFmt(QString value);
    void setIcon(QString value);
    void setVolumeInfo(const QVariantList& info);

    void setNumBlocks(int value) { numBlocks = value; emit numBlocksChanged(); }
    void setBsize(int value) { bsize = value; emit bsizeChanged(); }

    void setBlock(int value);

    //
    // Colors and labels for the layout views
    //

    Q_INVOKABLE QVariantList computeLegend() const;

signals:
    void deviceChanged();
    void volumeChanged();
    void nameChanged();
    void imageFmtChanged();
    void iconChanged();
    void volumeInfoChanged();
    void numBlocksChanged();
    void bsizeChanged();
    void blockChanged();
    void tableModelChanged();
    void legendDataChanged();

public slots:
    void refresh();

private:
    void updateIcon();
};
