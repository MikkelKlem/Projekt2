#include "unitUARTdriver.h"
#include "centralUnit.h"
#include "X10Master.h"
#include "moduleSettings.h
#include <Wire.h>
#include <stdlib.h>
#define FCPU 16000000
#include <util/delay.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include "string.h"
using namespace std;

volatile char mode;


ISR (INT4_vect)
{
  mode = '4';
}



int main(void)
{
  void setup()
  {
    Wire.setClock(50);
    Wire.begin();
    DDRB = 0xFF;
  }
  unitUARTdriver UART(9600, 8);
  centralUnit centralUnit(&UART);
  mode = '0';
  centralUnit.initIO();
  sei();
  
  X10protoMaster x10;
  
while (true)
{
  

  switch (mode)
  {
    case '1':
    {
      //Pinging the network
      x10.searchForUnits();
      break;
    }
    case '2':
    {
      //Change in network
      break;
    }
    case '3':
    {
      //Execute rutine
      break;

    }
    case '4':
    {
      cli();
      PORTB = 0b01010101;
      
      centralUnit.startConfig();

      centralUnit.endConfig();
      PORTB = 0b00001111;
      while (PINE & 0b00010000)
      {
      }
      PORTB = 0;
      mode = '0';
      _delay_ms(10);
      sei();
      break;
    }
    default:
    {
      //error in main...
      break;
    }
    
  }
}
  return 0;
}

