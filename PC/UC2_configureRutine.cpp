#include "UC2_configureRutine.h"
#include <iostream>
#include <fstream>
#include <windows.h>

UC2_configureRutine::UC2_configureRutine(pcUARTdriver* UART, userIF* UI)
{
	UART_ = UART;

	UI_ = UI;
}

void UC2_configureRutine::setUART(pcUARTdriver* UART)
{
	UART_ = UART;
}

void UC2_configureRutine::setUI(userIF* UI)
{
	UI_ = UI;
}

void UC2_configureRutine::setConfig(pcSettings* config)
{
	for (size_t i = 0; i < 4; i++)
	{
		if (config[i].getStatus() == true)
			unitConfig_[i] = config[i];
	}
}

char UC2_configureRutine::startConfig()
{
	system("cls");
	std::cout << "Waiting for Smart home central unit to be unlocked\n";
	UART_->recieveConfig(unitConfig_);

	for (size_t i = 0; i < 5; i++)
	{
		UART_->recieveConfig(savedArray_[i]);
	}

	UI_->setCopy(unitConfig_, savedArray_);
	char choice = UI_->displayMain();		//If user is quitting and saving or quitting without saving

	return choice;
}

void UC2_configureRutine::setSavedArray(pcSettings savedArray[5][4])
{
	for (size_t i = 0; i < 5; i++)
	{
		for(size_t j = 0; j < 4; j++)
		{
			savedArray_[i][j] = savedArray[i][j];
		};
	}
}

void UC2_configureRutine::endConfig(char isUserSaving)
{

	if (isUserSaving == 'g')		//Checking if saved config should be sent
	{
		setConfig(UI_->getConfig());

		setSavedArray(UI_->getSavedArray());
	}
	

	UART_->sendConfig(unitConfig_);
	
	
	for (size_t i = 0; i < 5; i++)
	{
		UART_->sendConfig(savedArray_[i]);
	}


	std::cout << "\n\nDu kan nu fjerne DE2 Boardet\n\n";

}
