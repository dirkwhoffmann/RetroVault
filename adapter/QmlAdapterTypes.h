#pragma once

#include <qqml.h>
#include <QObject>
#include <QString>
#include <QAbstractTableModel>
#include <QVariantList>


class DeviceInfo : public QObject {

    Q_OBJECT

public:

    enum Format { ADF, ADZ, EADF, DMS, HDF, HDZ, IMG, ST, D64, UNKNOWN };

    // Members
    QString m_name;
    int m_numBlocks = 0;
    int m_bsize = 512;
    int m_numCyls = 0;
    int m_numHeads = 0;
    Format m_format = UNKNOWN;

    // QML Properties
    Q_PROPERTY(QString name READ name CONSTANT)
    Q_PROPERTY(int numBlocks READ numBlocks CONSTANT)
    Q_PROPERTY(int bsize READ bsize CONSTANT)
    Q_PROPERTY(int numCyls READ numCyls CONSTANT)
    Q_PROPERTY(int numHeads READ numHeads CONSTANT)
    Q_PROPERTY(int format READ format CONSTANT) // Use an Enum

    // Computed QML Properties
    Q_PROPERTY(long long totalBytes READ totalBytes CONSTANT)

    Q_ENUM(Format)

public:

    explicit DeviceInfo(QObject *parent = nullptr) : QObject(parent) {}

    // Getters
    QString name() const { return m_name; }
    int numBlocks() const { return m_numBlocks; }
    int bsize() const { return m_bsize; }
    int numCyls() const { return m_numCyls; }
    int numHeads() const { return m_numHeads; }
    int format() const { return m_format; }
    long long totalBytes() const { return (long long)m_numBlocks * m_bsize; }
};

enum ItemType { DeviceItem, VolumeItem };

// Tree node for the sidebar
struct SidebarItem {
    ItemType type;                  // Device or Volume
    QString iconSource;             // Image name
    QString title;                  // Display name
    QString subtitle;               // Optional extra info
    int deviceId;                   // Device number
    int volumeId;                   // Volume number
    QVector<SidebarItem> children;  // Holds volumes for devices

    // Optional: default constructor
    SidebarItem() = default;
};

class BlockTableModel : public QAbstractTableModel
{
    Q_OBJECT
    QML_ELEMENT

    int dev = 0;
    int blk = 0;

public:

    explicit BlockTableModel(QObject *parent = nullptr);

    int rowCount(const QModelIndex & = QModelIndex()) const override;
    int columnCount(const QModelIndex & = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    QHash<int, QByteArray> roleNames() const override;

    void refresh(class QmlAdapter &backend, int dev, int blk);
};

class SidebarModel : public QAbstractItemModel
{
    Q_OBJECT

public:
    enum DeviceRoles {
        IconSourceRole = Qt::UserRole + 1,
        TitleRole,
        SubtitleRole,
        DeviceIdRole,
        VolumeIdRole,
        IsDeviceRole
    };

    explicit SidebarModel(QObject *parent = nullptr);

    QModelIndex index(int row, int column,  const QModelIndex &parent = QModelIndex()) const override;
    QModelIndex parent(const QModelIndex &child) const override;
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &) const override { return 1; }
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QHash<int, QByteArray> roleNames() const override;
    bool hasChildren(const QModelIndex &parent) const override;

    void refresh(class QmlAdapter &backend);

private:

    QVector<SidebarItem> m_devices;
};
