#pragma once
#include "pcSettings.h"
#include "serialib.h"
class pcUARTdriver
{
public:
	pcUARTdriver(serialib* serialPtr);
	
	void recieveConfig(pcSettings* unitConfig);
	void sendConfig(pcSettings* unitConfig);

private:
	serialib* serial_;
};

