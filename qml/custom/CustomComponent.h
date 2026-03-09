#pragma once

#include <QQuickPaintedItem>
#include <QPainter>
#include "../backend/Model.h"

class CustomComponent : public QQuickPaintedItem {

    Q_OBJECT

protected:

    Model *m_model = nullptr;
    DeviceManager *m_manager = nullptr;

public:

    Q_PROPERTY(Model* model READ model WRITE setModel)

    explicit CustomComponent(QQuickItem *parent = nullptr) : QQuickPaintedItem(parent) {}

    Model* model() const { return m_model; }
    DeviceManager* manager() const { return m_manager; }

    void setModel(Model* model);

    // Convenience wrappers
    FuseDevice *fuseDevice(isize dev) const;
    FuseVolume *fuseVolume(isize dev, isize vol) const;
    DiskImage *image(isize dev) const;
};