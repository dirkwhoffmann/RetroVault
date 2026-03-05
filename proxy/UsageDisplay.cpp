#include "UsageDisplay.h"

void
UsageDisplay::paint(QPainter *painter)  {

    printf("UsageDisplay::paint\n");

    // Access your backend data here
    // painter->setRenderHint(QPainter::Antialiasing);
    painter->setBrush(QColor("#27ae60"));
    painter->drawRoundedRect(0, 0, width() * 1.0, height(), 5, 5);
}