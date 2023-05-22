#include "unitUARTdriver.h"
#include "centralUnit.h"
#include <stdlib.h>
#define FCPU 16000000
#include <util/delay.h>
#include <avr/io.h>
#include <avr/interrupt.h>


volatile char mode;


ISR (INT4_vect)
{
  mode = '4';
}



int main(void)
{
  unitUARTdriver UART(9600, 8);
  centralUnit centralUnit(&UART);
  mode = '0';
  centralUnit.initIO();
  sei();
  
while (true)
{
  //if ((~PINA) & 0b10000000)
    //mode = '4';
  //if ((PINE) & 0b00010000)
    //mode = '4';

  switch (mode)
  {
    case '1':
    {
      //Pinging the network
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

