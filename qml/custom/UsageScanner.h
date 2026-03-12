#include "BaseScanner.h"

class UsageScanner : public BaseScanner
{
    Q_OBJECT
    QML_ELEMENT

    Q_PROPERTY(int device READ getDevice WRITE setDevice NOTIFY deviceChanged)
    Q_PROPERTY(int volume READ getVolume WRITE setVolume NOTIFY volumeChanged)

    int device = -1;
    int volume = -1;

    int getDevice() const { return device; }
    int getVolume() const { return volume; }

    void setDevice(int value)
    {
        device = value;
        emit deviceChanged();
    }

    void setVolume(int value)
    {
        volume = value;
        emit volumeChanged();
    }

signals:
    void deviceChanged();
    void volumeChanged();

public:
    void startScan() override
    {
        printf("startScan %d %d (%p)\n", device, volume, m_model);

        // Capture specific parameters for the lambda
        if (auto* fv = m_model->fuseVolume(device, volume))
        {
            runTask([fv]()
            {
                QByteArray data(1024 * 24, 0);
                printf("fv = %p\n", fv);
                fv->createUsageMap((u8*)data.data(), 1024);
                return data;
            });
        }
    }
};
