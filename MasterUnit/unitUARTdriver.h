#pragma once
#include "moduleSettings.h"

class unitUARTdriver {
public:
    unitUARTdriver(unsigned long BaudRate, unsigned char DataBit);
    bool charReady();
    char readChar();
    void readString(char* receivedString, int maxLength);
    void readBytes(char* buffer, int numBytes);
    void sendBytes(const char* data, int numBytes);
    void sendChar(char Tegn);
    void sendString(char* Streng);
    void sendInteger(int Tal);
    void sendConfig(moduleSettings* unitConfig);
    void receiveConfig(moduleSettings* unitConfig);
    //void addConfig(moduleSettings unitConfig);
    
private:
    const unsigned long XTAL = 16000000;
   
};
