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
  mode = '3';
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
      unsigned char oldUnits = x10.getUnits();
      x10.searchForUnits();
      unsigned char newUnits = x10.getUnits();
      if (oldUnits != newUnits)
      {
        //Change in network, check what devices changed and set isConnected for devices
        bool units[] ={false, false, false, false};
        for(int i = 0; i < 4; i++)
        {
          units[i] = (c >> (4 - i - 1)) & 1;
        }
        centralUnit.setConfig_[3].isConnected_ = units[0];
        centralUnit.setConfig_[3].isConnected_ = units[1];
        centralUnit.setConfig_[3].isConnected_ = units[2];
        centralUnit.setConfig_[3].isConnected_ = units[3];
      }
      break;
    }
    case '2':
    {
      //Execute rutines
      
      break;

    }
    case '3':
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

