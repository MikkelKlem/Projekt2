#include "userIF.h"
#include "PC.h"
#include "pcSettings.h"
#include "stdlib.h"
#include <conio.h>
#include <windows.h>
#include <iostream>

#define SERIAL_PORT "\\\\.\\COM3"

int main(void)
{
	userIF UI;
	serialib serial;
	pcUARTdriver UART(&serial);

	PC testPC(&UART, &UI);
	
	// Connection to serial port
	char errorOpening = serial.openDevice(SERIAL_PORT, 9600);


	// If connection fails, return the error code otherwise, display a success message
	if (errorOpening != 1) 
		return errorOpening;
	printf("Successful connection to %s\n", SERIAL_PORT);


	//ART.recieveConfig(testPC.unitConfig_);

	testPC.startConfig();


	testPC.endConfig();

	std::cout << "\n\nDu kan nu fjerne DE2 Boardet\n\n"


	//testPC.startConfig();

	return 0;
}