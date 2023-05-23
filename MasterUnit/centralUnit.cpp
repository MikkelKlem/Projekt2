#include "centralUnit.h"
#include <avr/io.h>



centralUnit::centralUnit(unitUARTdriver* UART ) : unitConfig_{moduleSettings('1'),moduleSettings('2'),moduleSettings('3'),moduleSettings('4')}
{
    UART_ = UART;

    for (size_t i = 0; i < 5; i++)
      for (size_t j = 0; j < 4; j++)
    {
        savedArray[i][j] = unitConfig_[j];
    }
    
}



void centralUnit::startConfig()
{
    UART_->sendConfig(unitConfig_);

    for(size_t i = 0; i < 5; i++) {
        UART_->sendConfig(savedArray[i]); //sending savedArray;
        }
}


void centralUnit::endConfig()
{


    UART_->receiveConfig(unitConfig_);
    
 for(size_t i = 0; i < 5; i++) {
        UART_->receiveConfig(savedArray[i]); //Revciving savedArray;
    }
}



void centralUnit::initIO()
{

    // Setting PORTB as output (IO shield LED's)
    DDRB = 0xFF;

    // Setting PORBE pin 4 as input
    DDRE = DDRE & 0b11101111;

    // Setting PORTA as input  (IO shield switches)
    DDRA = 0; //Sæt alle switces som inputs

    // Turn of LED's
    PORTB = 0;

    // Enable external interrupt on pin4 (interrupt 4)
    EIMSK = EIMSK | 0b00010000;

    // Interrupt on rising edge
    EICRB = 0b00000011;


}

void centralUnit::setSavedArray(int number)
{

    for (size_t i = 0; i < 4; i++)
    {
        unitConfig_[i] = savedArray[number][i];
    }


}
