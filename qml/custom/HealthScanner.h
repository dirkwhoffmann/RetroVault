#include "BaseScanner.h"

class HealthScanner : public BaseScanner
{
    Q_OBJECT
    QML_ELEMENT

public:
    void startScan() override;
};
