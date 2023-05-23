	#pragma once
	#include "pcSettings.h"
	#include "pcUARTdriver.h"
	#include "userIF.h"


	class PC
	{
	public:
		PC(pcUARTdriver* UART, userIF* UI);
		void setUART(pcUARTdriver * UART);
		void setUI(userIF * UI);
		void setConfig(pcSettings*  config);
		char startConfig();
		void setSavedArray(pcSettings savedArray[5][4]);
		void endConfig(char choice);
		pcSettings unitConfig_[4];
		pcSettings savedArray_[5][4];
		


		private:
		pcUARTdriver* UART_;
		userIF* UI_;
	};

