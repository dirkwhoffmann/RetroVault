#include <QObject>
#include <QStringList>
#include <QUrl>
#include "FuseDevice.h" // Your backend

#pragma once

class VaultProxy : public QObject {
    Q_OBJECT
public:
    explicit VaultProxy(QObject *parent = nullptr) : QObject(parent) {}

    // --- The "Pull" API ---

    Q_INVOKABLE int deviceCount() {
        return 4;
        // return Backend::instance()->numberOfDevices();
    }

    Q_INVOKABLE QString deviceTitle(int deviceIdx)
    {
        switch (deviceIdx)
        {
        case 0: return QStringLiteral("Batman");
        case 1: return QStringLiteral("Return of the Mutan Camals");
        case 2: return QStringLiteral("Popeye's adventure");
        case 3: return QStringLiteral("Summer games");
        default: return QStringLiteral("Unknown");
        }
        // auto* dev = Backend::instance()->getDevice(deviceIdx);
        // return dev ? QString::fromStdString(dev->imageInfo().filename) : "";
    }

    Q_INVOKABLE QStringList volumeNames(int deviceIdx) {
        QStringList list;

        list << QStringLiteral("Partion 1");
        if (deviceIdx >= 2) list << QStringLiteral("Partion 2");
        if (deviceIdx >= 3) list << QStringLiteral("Partion 3");
        /*
        auto* dev = Backend::instance()->getDevice(deviceIdx);
        if (dev) {
            for (int i = 0; i < dev->count(); ++i) {
                // Here is your type conversion: std::string -> QString
                list << QString::fromStdString(dev->getVolume(i).getName());
            }
        }
        */
        return list;
    }

    // --- The "Action" API ---

    Q_INVOKABLE void addDevice(const QUrl &url) {
        /*
        std::string path = url.toLocalFile().toStdString();
        Backend::instance()->loadDevice(path);
        */
        emit dataChanged(); // Notify UI to refresh
    }

    Q_INVOKABLE void mount(int devIdx, int volIdx) {
        /*
        auto* dev = Backend::instance()->getDevice(devIdx);
        if (dev) dev->mount(volIdx);
        */
        emit dataChanged();
    }

    signals:
        void dataChanged(); // The "Bat-Signal" for the UI
};