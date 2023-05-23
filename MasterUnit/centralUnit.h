#include "moduleSettings.h"
#include "unitUARTdriver.h"


class centralUnit
{
public:
    centralUnit(unitUARTdriver* UART);
    void startConfig();
    void endConfig();
    void initIO();
    
    void setSavedArray(int number);
private:
    moduleSettings savedArray[5][4];
	  moduleSettings unitConfig_[4];
    unitUARTdriver* UART_;
};

