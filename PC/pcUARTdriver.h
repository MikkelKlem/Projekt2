#pragma once
#include "pcSettings.h"
#include "serialib.h"
class pcUARTdriver
{
public:
	pcUARTdriver(serialib* serialPtr);
	void initDriver();
	void recieveConfig(pcSettings* unitConfig);
	void sendConfig(pcSettings* unitConfig);
	void sendConfig(pcSettings(*unitConfig)[4]);


private:
	serialib* serial_;
};

