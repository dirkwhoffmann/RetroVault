//
// Created by Dirk Hoffmann on 06.03.26.
//

#include "CustomController.h"

void
CustomController::setWindowController(WindowController* ptr)
{
    printf("CustomController::setWindowController(%p) %p\n", ptr, ptr ? ptr->getManager() : nullptr);
    if (windowController != ptr)
    {
        windowController = ptr;
        emit windowControllerChanged();
    }
}
