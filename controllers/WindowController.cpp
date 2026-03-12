//
// Created by Dirk Hoffmann on 07.03.26.
//

#include "WindowController.h"
#include "FuseDevice.h"
#include "FuseVolume.h"
#include <QFile>
void
WindowController::addImage(const QUrl &url) {

    QFile file(url.toLocalFile());

    /*
    if (!file.open(QIODevice::ReadOnly)) {
        qDebug() << "Error Code:" << file.error();
        qDebug() << "Error String:" << file.errorString();
    }
    */

    try
    {
        printf("addImage(%s)\n", url.toLocalFile().toStdString().c_str());
        model->manager->add(url.toLocalFile().toStdString());
        model->select(model->getNumDevices() - 1);
        emit model->numDevicesChanged();
    }
    catch (std::exception& e)
    {
        rethrow(e);
    }
}
