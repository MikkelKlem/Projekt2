#include "centralUnit.h"
#include <avr/io.h>
#include <string.h>
#include <avr/interrupt.h>
#define FCPU 16000000
#include <util/delay.h>

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
    PORTB = 0b00001111;
    while (PINE & 0b00010000) //Waiting for DE-2 board to disconnect
      {
      }
      PORTB = 0;
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

void centralUnit::quickRutinePressed()
{
    PORTB = 0b00011111;
    _delay_ms(500);
    while (((~PINA) & 0b11111111) == 0b00000000)
      {
      }
    chooseRutine();
      
}

void centralUnit::chooseRutine()
{

    char choice;
    int number = 10;

    PORTB = ~PINA;
    choice = ~PINA; //input from the switches

    switch (choice)
      {
      case 0b00000001:
      {
        number = 0;
        break;
      }
      case 0b00000010:
      {
        number = 1;
        break;
      }
      case 0b00000100:
      {
        number = 2;
        break;
      }
      case 0b00001000:
      {
        number = 3;
        break;
      }
      case 0b00010000:
      {
        number = 4;
        break;
      }
      default:  //if anything else i pressed, quit quickRutine
      {
        PORTB = 0;
  
        break;
      } 
      }
      if (number != 10 )
      {
        setSavedArray(number);
        _delay_ms(2500);
        PORTB = 0;
 
      }
}
