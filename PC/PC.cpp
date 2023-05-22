#include "PC.h"
#include <iostream>
#include <fstream>
#include <windows.h>

PC::PC(pcUARTdriver* UART, userIF* UI)
{
	UART_ = UART;

	UI_ = UI;
}

void PC::setUART(pcUARTdriver* UART)
{
	UART_ = UART;
}

void PC::setUI(userIF* UI)
{
	UI_ = UI;
}

void PC::setConfig(pcSettings* config)
{
	for (size_t i = 0; i < 4; i++)
	{
		if (config[i].getStatus() == true)
			unitConfig_[i] = config[i];
	}
}

void PC::startConfig()
{
	system("cls");
	std::cout << "Waiting for Smart home central unit to be unlocked\n";
	UART_->recieveConfig(unitConfig_);

	for (size_t i = 0; i < 5; i++)
	{
		UART_->recieveConfig(savedArray_[i]);
	}

	UI_->setCopy(unitConfig_, savedArray_);
	UI_->displayMain();
}

void PC::setSavedArray(pcSettings savedArray[5][4])
{
	for (size_t i = 0; i < 5; i++)
	{
		for(size_t j = 0; j < 4; j++)
		{
			savedArray_[i][j] = savedArray[i][j];
		};
	}
}

void PC::endConfig()
{
	setConfig(UI_->getConfig());
		
	setSavedArray(UI_->getSavedArray());

	

	UART_->sendConfig(unitConfig_);
	
	
	for (size_t i = 0; i < 5; i++)
	{
		UART_->sendConfig(savedArray_[i]);
	}
	

}

pcSettings* PC::getSavedArray() const
{
	return nullptr;
}

