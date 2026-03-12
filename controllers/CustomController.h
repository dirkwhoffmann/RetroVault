#pragma once

/*
#include "WindowController.h"

class CustomController : public Controller
{
    Q_OBJECT

protected:
    WindowController* windowController = nullptr;

public:
    Q_PROPERTY(
        WindowController* windowController
        READ getWindowController WRITE setWindowController NOTIFY windowControllerChanged)

    explicit CustomController(QObject* parent = nullptr) : Controller(parent)
    {
    }

    WindowController* getWindowController() const { return windowController; }
    void setWindowController(WindowController* model);

    DeviceManager* getManager() { return windowController ? windowController->getManager() : nullptr; }

    // Convenience wrappers
    // DeviceManager *manager() const { return windowController->getManager(); }
    FuseDevice* fuseDevice(isize dev) const { return windowController->fuseDevice(dev); }
    FuseVolume* fuseVolume(isize dev, isize vol) const { return windowController->fuseVolume(dev, vol); }
    DiskImage* image(isize dev) const { return windowController->image(dev); }

    signals:
    void windowControllerChanged();
};
*/