#pragma once

#include "Controller.h"

class BlockViewController : public Controller
{
    Q_OBJECT

public:

    explicit BlockViewController(QObject *parent = nullptr);

public slots:

    void refresh();

};
