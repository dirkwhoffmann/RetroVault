#pragma once

#include "CustomController.h"
#include <QAbstractItemModel>
#include <QColor>

class VolumePanelController : public CustomController
{
    Q_OBJECT

    class BlockViewModel : public QAbstractTableModel
    {
    public:
        VolumePanelController* controller = nullptr;

        int blkNr = 0;

        BlockViewModel(VolumePanelController* c) : controller(c)
        {
        }

        int rowCount(const QModelIndex& = QModelIndex()) const override;
        int columnCount(const QModelIndex& = QModelIndex()) const override;
        QVariant data(const QModelIndex& index, int role) const override;

        void refresh(int b);
    };

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

    using CustomController::CustomController;
    /*
    explicit VolumePanelController(QObject* parent = nullptr) : Controller(parent)
    {
        tableModel.controller = this;
    }
    */

    //
    // Properties
    //

    Q_PROPERTY(QString name READ getName NOTIFY nameChanged)
    Q_PROPERTY(QString imageFmt READ getImageFmt NOTIFY imageFmtChanged)
    Q_PROPERTY(QString icon READ getIcon NOTIFY iconChanged)
    Q_PROPERTY(QVariantList volumeInfo READ getVolumeInfo NOTIFY volumeInfoChanged)

    Q_PROPERTY(int numBlocks READ getNumBlocks NOTIFY numBlocksChanged)
    Q_PROPERTY(int bsize READ getBsize NOTIFY bsizeChanged)

    Q_PROPERTY(int block READ getBlock WRITE setBlock NOTIFY blockChanged)
    Q_PROPERTY(BlockViewModel* tableModel READ getTableModel NOTIFY tableModelChanged)

    Q_PROPERTY(QVariantList legendData READ getLegendData NOTIFY legendDataChanged)

    Q_PROPERTY(QColor bootBlockColor READ getBootBlockColor CONSTANT)
    Q_PROPERTY(QColor rootBlockColor READ getRootBlockColor CONSTANT)
    Q_PROPERTY(QColor bitmapBlockColor READ getBitmapBlockColor CONSTANT)
    Q_PROPERTY(QColor bitmapExtBlockColor READ getBitmapExtBlockColor CONSTANT)
    Q_PROPERTY(QColor directoryBlockColor READ getDirectoryBlockColor CONSTANT)
    Q_PROPERTY(QColor headerBlockColor READ getHeaderBlockColor CONSTANT)
    Q_PROPERTY(QColor listBlockColor READ getListBlockColor CONSTANT)
    Q_PROPERTY(QColor dataBlockColor READ getDataBlockColor CONSTANT)
    Q_PROPERTY(QColor okColor READ getOkColor CONSTANT)
    Q_PROPERTY(QColor warnColor READ getWarnColor CONSTANT)
    Q_PROPERTY(QColor errorColor READ getErrorColor CONSTANT)

    Q_PROPERTY(QList<QColor> usagePanelColors READ getUsagePanelColors NOTIFY usagePanelColorsChanged)
    Q_PROPERTY(QList<QColor> allocPanelColors READ getAllocPanelColors NOTIFY allocPanelColorsChanged)
    Q_PROPERTY(QList<QColor> healthPanelColors READ getHealthPanelColors NOTIFY healthPanelColorsChanged)

private:

    //
    // Getter
    //

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
    // Setter
    //

    void setName(QString &value);
    void setImageFmt(QString &value);
    void setIcon(QString &value);
    void setVolumeInfo(const QVariantList& info);

    void setNumBlocks(int value) { numBlocks = value; emit numBlocksChanged(); }
    void setBsize(int value) { bsize = value; emit bsizeChanged(); }

    void setBlock(int value);

    //
    // Colors and labels for the layout views
    //

    Q_INVOKABLE QVariantList computeLegend() const;

    QColor getBootBlockColor() const { return QColor("#ffb266"); }
    QColor getRootBlockColor() const { return QColor("#ff6666"); }
    QColor getBitmapBlockColor() const { return QColor("#b266ff"); }
    QColor getBitmapExtBlockColor() const { return QColor("#ff66ff"); }
    QColor getDirectoryBlockColor() const { return QColor("#ffff66"); }
    QColor getHeaderBlockColor() const { return QColor("#66b2ff"); }
    QColor getListBlockColor() const { return QColor("#009900"); }
    QColor getDataBlockColor() const { return QColor("#66ff66"); }
    QColor getOkColor() const { return QColor("#66ff66"); }
    QColor getWarnColor() const { return QColor("#ffff66"); }
    QColor getErrorColor() const { return QColor("#ff6666"); }

    QList<QColor> getUsagePanelColors() const;
    QList<QColor> getAllocPanelColors() const;
    QList<QColor> getHealthPanelColors() const;

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
    void usagePanelColorsChanged();
    void allocPanelColorsChanged();
    void healthPanelColorsChanged();

public slots:
    void refresh();

private:
    void updateIcon();
};
