#include "moduleSettings.h"
#include "unitUARTdriver.h"


class centralUnit
{
public:
    centralUnit(unitUARTdriver* UART);
    void startConfig();
    void endConfig();
    void initIO();
private:
    moduleSettings savedArray[5][4];
	moduleSettings unitConfig_[4];
    unitUARTdriver* UART_;
};


/*for (size_t i = 0; i < 5; i++) {
  for (size_t j = 0; j < 4; j++) {
    moduleSettings newUnitConfig = unitConfig[j];
    savedArray[i][j] = newUnitConfig;
  }*/
