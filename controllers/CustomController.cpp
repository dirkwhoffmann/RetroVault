//
// Created by Dirk Hoffmann on 14.03.26.
//

#include "CustomController.h"

void
CustomController::setWC(WindowController* value)
{
    wc = value;
    emit wcChanged();
}