#include "BaseScanner.h"

class AllocScanner : public BaseScanner
{
    Q_OBJECT
    QML_ELEMENT

public:
    void startScan() override;
};
