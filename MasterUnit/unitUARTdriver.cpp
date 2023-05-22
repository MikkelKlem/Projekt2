#include <avr/io.h>
#include <stdlib.h>
#include "unitUARTdriver.h"
#define FCPU 16000000
#include <util/delay.h>
#include <string.h>

unitUARTdriver::unitUARTdriver(unsigned long BaudRate, unsigned char DataBit) 
{
    if ((BaudRate >= 300) && (BaudRate <= 115200) && (DataBit >=5) && (DataBit <= 8))
    { 
        // No interrupts enabled
        // Receiver enabled
        // Transmitter enabled
        // No 9 bit operation
        UCSR0B = 0b00011000;    
        // Asynchronous operation, 1 stop bit
        // Bit 2 and bit 1 controls the number of data bits
        UCSR0C = (DataBit-5)<<1;
        // Set Baud Rate according to the parameter BaudRate
        UBRR0 = XTAL/(16*BaudRate) - 1;
    }  

   
}

bool unitUARTdriver::charReady() {
    return UCSR0A & (1<<7);
}

char unitUARTdriver::readChar() {
    // Wait for new character received
    while ( (UCSR0A & (1<<7)) == 0 )
    {}                        
    // Then return it
    return UDR0;
}

void unitUARTdriver::readBytes(char* buffer, int numBytes) {
    for (int i = 0; i < numBytes; i++) {
        // Wait for new character received
        while ((UCSR0A & (1 << 7)) == 0) {}
        // Read the character and store it in the buffer
        buffer[i] = UDR0;
    }
}


void unitUARTdriver::sendBytes(const char* data, int numBytes) {
    for (int i = 0; i < numBytes; i++) {
        // Wait for the transmit buffer to be empty
        while ((UCSR0A & (1 << 5)) == 0) {}
        // Send the byte
        UDR0 = data[i];
    }
}

void unitUARTdriver::readString(char* receivedString, int maxLength) {
  int index = 0;

  // Read characters until a newline ('\n') is received or the maximum length is reached
  char receivedChar;
  while (true) {
    // Wait for new character received
    while ((UCSR0A & (1 << 7)) == 0) {}

    // Read the character
    receivedChar = UDR0;

    // Break the loop if a newline is received or maximum length is reached
    if (receivedChar == '\n' || index >= maxLength - 1) {
      receivedString[index] = '\0'; // Null-terminate the received string
      break;
    }

    // Append the character to the received string
    receivedString[index++] = receivedChar;
  }
}



void unitUARTdriver::sendChar(char Tegn) {
    // Wait for transmitter register empty (ready for new character)
    while ( (UCSR0A & (1<<5)) == 0 )
    {}
    // Then send the character
    UDR0 = Tegn;
}

void unitUARTdriver::sendString(char* Streng) {
    // Repeat until zero-termination
    while (*Streng != 0)
    {
        // Send the character pointed to by "Streng"
        sendChar(*Streng);
        // Advance the pointer one step
        Streng++;
    }
}

void unitUARTdriver::sendInteger(int Tal) {
    char array[7];
    // Convert the integer to an ASCII string (array), radix = 10 
    itoa(Tal, array, 10);
    // - then send the string
    sendString(array);
}


void unitUARTdriver::sendConfig(moduleSettings* unitConfig)
{
    const size_t numUnits = 4;
    const char SOM = '@'; // Start-of-message marker
    const char RTS = '&'; // Ready-to-send marker
    const char RTR = '#'; // Ready-to-recieve marker
    char RTRmarker;

    sendBytes(&RTS, sizeof(char));

    while (true) {
        readBytes(&RTRmarker, sizeof(char));
        if (RTRmarker == RTR) {
            break; // Found RTR marker, proceed to read size
        }
    } //WAITING FOR PC TO RESPOND WITH Ready-to-recieve




    for (size_t j = 0; j < numUnits; j++)
    {
        
      

        // Calculate sizes including null-terminating character
        char sizeArray[8] = {
            static_cast<char>(sizeof(bool) + 1),
            strlen(unitConfig[j].unitName_) + 1 ,
            sizeof(char) + 1,
            strlen(unitConfig[j].activationTime_) + 1,
            strlen(unitConfig[j].rutine1_) + 1,
            strlen(unitConfig[j].rutine2_) + 1,
            strlen(unitConfig[j].rutine3_) + 1,
            strlen(unitConfig[j].rutine4_) + 1
        };

     

        //_delay_us(10);

        // Send SOM marker
        sendBytes(&SOM, sizeof(char));

        _delay_us(10); //A small delay to make the UART more stable

    

        // Send the size of the next element
        sendBytes(sizeArray, sizeof(sizeArray));
        //sendBytes(&IBI, sizeof(char));

        
        _delay_us(10); //A small delay to make the UART more stable

        // Sending relevant data

        
        // Sending connection status as char / converted from bool
        char connectionStatus = static_cast<char>(unitConfig[j].isConnected_);
        sendBytes(&connectionStatus, sizeof(connectionStatus) + 1);
        //sendBytes(&IBI, sizeof(char));
        
        // Sending unitName
        sendBytes(unitConfig[j].unitName_, strlen(unitConfig[j].unitName_) + 1 );
        //sendBytes(&IBI, sizeof(char));
        
    

        // Sending desired routine
        sendBytes(&unitConfig[j].desiredRutine_, sizeof(char) +1); //strlen(&unitConfig[j].desiredRutine_)
        //sendBytes(&IBI, sizeof(char));

        // Sending activation time
        sendBytes(unitConfig[j].activationTime_, strlen(unitConfig[j].activationTime_)+1);
        //sendBytes(&IBI, sizeof(char));

        //Sending rutine 1
        sendBytes(unitConfig[j].rutine1_, strlen(unitConfig[j].rutine1_)+ 1);
        //sendBytes(&IBI, sizeof(char));

        //Sending rutine 2
        sendBytes(unitConfig[j].rutine2_, strlen(unitConfig[j].rutine2_) + 1);
       // sendBytes(&IBI, sizeof(char));

        //Sending rutine 3
        sendBytes(unitConfig[j].rutine3_, strlen(unitConfig[j].rutine3_) + 1);
       // sendBytes(&IBI, sizeof(char));

        //Sending rutine 4
        sendBytes(unitConfig[j].rutine4_, strlen(unitConfig[j].rutine4_) + 1);
       // sendBytes(&IBI, sizeof(char));
      //  sendBytes(&EOM, sizeof(char));
    }
}

void unitUARTdriver::receiveConfig(moduleSettings* unitConfig)
{
    const size_t numUnits = 4;
    const size_t TIME_SIZE = 6;
    const char SOM = '@'; // Start-of-message marker
    const char RTS = '&'; // Ready-to-send marker
    const char RTR = '#'; // Ready-to-recieve marker
    char marker;
    char RTSmarker;
    

    while (true) {
        readBytes(&RTSmarker, sizeof(char));
        if (RTSmarker == RTS) {
            break; // Found RTS marker, proceed to read size
        }
    } 
    sendBytes(&RTR, sizeof(char));

    for (size_t j = 0; j < numUnits; j++)
    {
         char hours[2];
         char minutes[2];
         char desiredRutine;
         char time[TIME_SIZE];
        while (true) {
            readBytes(&marker, sizeof(char));
            if (marker == SOM) {
                break; // Found SOM marker, proceed to read data
            }
        }

        readBytes(time, TIME_SIZE); //Reading the time as string
        readBytes(hours, 3); //Reading the time
        readBytes(minutes, 3); //Reading the time

        readBytes(&desiredRutine, 1); //Reading the desired rutine

        strncpy(unitConfig[j].activationTime_, time, TIME_SIZE);

        unitConfig[j].activationHour_ = atoi(hours);
        unitConfig[j].activationMinute_ = atoi(minutes);
        unitConfig[j].desiredRutine_ = desiredRutine;

    }


}
