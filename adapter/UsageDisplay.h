#pragma once

#include <QQuickPaintedItem>
#include <QPainter>

class UsageDisplay : public QQuickPaintedItem {

    Q_OBJECT

public:

    void paint(QPainter *painter) override;
};