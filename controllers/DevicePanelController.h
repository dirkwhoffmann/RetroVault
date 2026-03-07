#pragma once

#include "Controller.h"
#include "BlockTableModel.h"

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
    BlockTableModel m_blockTableModel;

public:
    // using Controller::Controller;
    DevicePanelController() : Controller()
    {
        printf("DevicePanelController\n");
    }

    Q_PROPERTY(QString name READ name NOTIFY nameChanged)
    Q_PROPERTY(int device READ device WRITE setDevice NOTIFY deviceChanged)
    Q_PROPERTY(int cylinder READ cylinder WRITE setCylinder NOTIFY cylinderChanged)
    Q_PROPERTY(int head READ head WRITE setHead NOTIFY headChanged)
    Q_PROPERTY(int track READ track WRITE setTrack NOTIFY trackChanged)
    Q_PROPERTY(int sector READ sector NOTIFY sectorChanged)
    Q_PROPERTY(int block READ block NOTIFY blockChanged)
    Q_PROPERTY(QVariantList deviceInfo READ deviceInfo NOTIFY deviceInfoChanged)
    Q_PROPERTY(BlockTableModel* blockTableModel READ blockTableModel NOTIFY blockTableModelChanged)

    QString name() const { return m_name; }
    int device() const { return m_device; }
    int cylinder() const { return m_cylinder; }
    int head() const { return m_head; }
    int track() const { return m_track; }
    int sector() const { return m_sector; }
    int block() const { return m_block; }
    QVariantList deviceInfo() const { return m_deviceInfo; }
    BlockTableModel* blockTableModel() { return &m_blockTableModel; }

    void setDevice(int device) { m_device = device; }
    void setCylinder(int cylinder) { m_cylinder = cylinder; }
    void setHead(int head) { m_head = head; }
    void setTrack(int track) { m_track = track; }
    void setSector(int sector) { m_sector = sector; }
    void setBlock(int block)
    {
        printf("setBlock %d\n", block);
        if (m_block != block)
        {
            m_block = block;
            emit blockChanged();
            refresh(m_device);
        }
    }

signals:
    void deviceChanged();
    void nameChanged();
    void cylinderChanged();
    void headChanged();
    void trackChanged();
    void sectorChanged();
    void blockChanged();
    void deviceInfoChanged();
    void blockTableModelChanged();

public slots:
    void refresh(int deviceId);
};
