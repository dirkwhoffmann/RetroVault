#pragma once

#include "Controller.h"
#include <QAbstractItemModel>

class DeviceBlockViewModel : public QAbstractTableModel
{
public:

    Controller *controller = nullptr;

    std::optional<isize> m_dev {};
    std::optional<isize> m_blk {};

    // DeviceBlockViewModel() { }

    int rowCount(const QModelIndex & = QModelIndex()) const override;
    int columnCount(const QModelIndex & = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role) const override;

    void refresh(int dev, int blk);
};

class DevicePanelController : public Controller
{
    Q_OBJECT

    QString m_name = "MY_NAME";
    int m_device = 0;
    int m_cylinder = 0;
    int m_head = 0;
    int m_track = 0;
    int m_sector = 0;
    int m_block = 0;

    QVariantList m_deviceInfo;
    DeviceBlockViewModel m_tableModel;

public:

    // using Controller::Controller;
    explicit DevicePanelController(QObject *parent = nullptr) : Controller(parent)
    {
        m_tableModel.controller = this;
    }

    Q_PROPERTY(QString name READ name NOTIFY nameChanged)
    Q_PROPERTY(int device READ device WRITE setDevice NOTIFY deviceChanged)
    Q_PROPERTY(int cylinder READ cylinder WRITE setCylinder NOTIFY cylinderChanged)
    Q_PROPERTY(int head READ head WRITE setHead NOTIFY headChanged)
    Q_PROPERTY(int track READ track WRITE setTrack NOTIFY trackChanged)
    Q_PROPERTY(int sector READ sector NOTIFY sectorChanged)
    Q_PROPERTY(int block READ block NOTIFY blockChanged)
    Q_PROPERTY(QVariantList deviceInfo READ deviceInfo NOTIFY deviceInfoChanged)
    Q_PROPERTY(DeviceBlockViewModel* tableModel READ tableModel NOTIFY tableModelChanged)

    QString name() const { return m_name; }
    int device() const { return m_device; }
    int cylinder() const { return m_cylinder; }
    int head() const { return m_head; }
    int track() const { return m_track; }
    int sector() const { return m_sector; }
    int block() const { return m_block; }
    QVariantList deviceInfo() const { return m_deviceInfo; }
    DeviceBlockViewModel* tableModel() { return &m_tableModel; }

    void setDevice(int device);
    void setCylinder(int cylinder);
    void setHead(int head);
    void setTrack(int track);
    void setSector(int sector);
    void setBlock(int block);

signals:
    void deviceChanged();
    void nameChanged();
    void cylinderChanged();
    void headChanged();
    void trackChanged();
    void sectorChanged();
    void blockChanged();
    void deviceInfoChanged();
    void tableModelChanged();

public slots:
    void refresh();
};
