#pragma once

#include <QQuickPaintedItem>
#include <QPainter>
// #include <QtQml/qqmlregistration.h>

class UsageDisplay : public QQuickPaintedItem {

    Q_OBJECT
    QML_ELEMENT

public:

    void paint(QPainter *painter) override;
};