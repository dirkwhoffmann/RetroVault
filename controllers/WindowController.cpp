//
// Created by Dirk Hoffmann on 07.03.26.
//

#include "WindowController.h"

void
WindowController::addImage(const QUrl &url) {

    QFile file(url.toLocalFile());

    if (!file.open(QIODevice::ReadOnly)) {
        qDebug() << "Error Code:" << file.error();
        qDebug() << "Error String:" << file.errorString();
    }

    try
    {
        printf("addImage(%s)\n", url.toLocalFile().toStdString().c_str());
        manager->add(url.toLocalFile().toStdString());
    }
    catch (std::exception& e)
    {
        // rethrow(e);
    }
}