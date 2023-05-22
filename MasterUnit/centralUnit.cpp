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
    DDRB = 0xFF;
    //DDRA = DDRA & 0b11111110;
    DDRE = DDRE & 0b11101111;
    //PORTE = 0b00010000;
    DDRA = 0;
  // Sluk alle lysdioderne
    PORTB = 0;
    //PORTE |= (1<<PE4);
    EIMSK = EIMSK | 0b00010000;
    EICRB = 0b00000011;


}
