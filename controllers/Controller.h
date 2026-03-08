#pragma once

#include <QtQml>
#include "Model.h"

class Controller : public QObject {

    Q_OBJECT

protected:

    Model *m_model = nullptr;
    DeviceManager *m_manager = nullptr;

public:

    Q_PROPERTY(Model* model READ model WRITE setModel NOTIFY modelChanged)

    explicit Controller(QObject *parent = nullptr) : QObject(parent) {}

    Model* model() const { return m_model; }
    DeviceManager* manager() const { return m_manager; }

    void setModel(Model* model);

    // Convenience wrappers
    FuseDevice *fuseDevice(isize dev) const;
    FuseVolume *fuseVolume(isize dev, isize vol) const;
    DiskImage *image(isize dev) const;

    signals:
        void modelChanged();
};