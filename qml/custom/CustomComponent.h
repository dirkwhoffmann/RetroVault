#pragma once

#include <QQuickPaintedItem>
#include <QPainter>

#include "WindowController.h"

class CustomComponent : public QQuickPaintedItem {

    Q_OBJECT

protected:

    WindowController* wc;

public:

    Q_PROPERTY(WindowController* windowController READ getWC WRITE setWC NOTIFY wcChanged)

    explicit CustomComponent(QQuickItem *parent = nullptr) : QQuickPaintedItem(parent) {}

    WindowController* getWC() const { return wc; }

    void setWC(WindowController* value);

    // Wrappers
    DeviceManager* manager() const { return wc->getManager(); }
    FuseDevice *fuseDevice(isize dev) const { return wc->fuseDevice(dev); }
    FuseVolume *fuseVolume(isize dev, isize vol) const { return wc->fuseVolume(dev, vol); }
    DiskImage *diskImage(isize dev) const { return wc->diskImage(dev); }

signals:
    void wcChanged();
};