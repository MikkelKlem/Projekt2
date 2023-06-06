	#pragma once
	#include "pcSettings.h"
	#include "pcUARTdriver.h"
	#include "userIF.h"


	class UC2_configureRutine
	{
	public:
		UC2_configureRutine(pcUARTdriver* UART, userIF* UI);
		void setUART(pcUARTdriver * UART);
		void setUI(userIF * UI);
		void setConfig(pcSettings*  config);
		char startConfig();
		void setSavedArray(pcSettings savedArray[5][4]);
		void endConfig(char choice);
		
		private:
		pcSettings unitConfig_[4];
		pcSettings savedArray_[5][4];
		pcUARTdriver* UART_;
		userIF* UI_;
	};

