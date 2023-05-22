#include "header.h"
#include <Wire.h>
#include "string.h"
#include "Arduino.h"

char readData;

unsigned short int charsToUnsignedShort(unsigned char highByte, unsigned char lowByte) // Laver chars om til unsigned short int
{
    unsigned short int result = (static_cast<unsigned short int>(highByte) << 8) | static_cast<unsigned short int>(lowByte);
    
    return result;
}

unsigned char manchesterDecode(unsigned short int encoded) // Dekoder manchesterkoden til en char
{
  unsigned char decoded = 0;
  for (int i = 0; i < 8; i++) {
    unsigned short int bitPair = (encoded >> (i * 2)) & 3;
    if (bitPair == 1) {
      decoded |= (static_cast<unsigned char>(0) << i);
    } else if (bitPair == 2) {
      decoded |= (static_cast<unsigned char>(1) << i);
    }
  }
  return decoded;
}

String manchesterEncode(char n) // Laver en string med manchesterkode
{
  String encoded = "";
  for (int i = 0; i < 8; i++) {
    int bit = (n >> (8 - i)) & 1;
    if (bit == 0) {
      encoded += "01";
    } else {
      encoded += "10";
    }
  }
  return encoded;
}

char binaryStringToChar(String binaryString)   // Laver den binære streng om til en char
    {
    char result = 0;
    int length = binaryString.length(); 

    for (int i = 0; i < length; i++) 
    {
    result = result << 1;
    if (binaryString.charAt(i) == '1') {
      result = result | 0x01;
    } else if (binaryString.charAt(i) != '0') {
      // Hvis strengen indeholder andet end 0 og 1
      return 0;
    }
  }
  return result;
}

void receiveEvent(int howMany) // Interrupt der kører når slaven modtager data fra master
{
    unsigned char readchar = 0;
    while (Wire.available() >= 1) 
    {
      unsigned char b1, b2;
      b1 = Wire.read();
      
      b2 = Wire.read();
      // PORTB = b2;
      unsigned short int samlet = charsToUnsignedShort(b1,b2);
     
      readchar = manchesterDecode(samlet);

      PORTB = readchar;
      readData = readchar;
  }
}

X10ProtoSlave::X10ProtoSlave(int slaveDevice) // Constructor med setup, modtager slavens addresse
{
  Wire.setClock(50);            // Sætter clock frekvensen
  Wire.begin(slaveDevice);             // join i2c bus with address
  Wire.onReceive(receiveEvent);
  DDRB = 0xFF;
  
}

char X10ProtoSlave::readChar() // Funktion der kan læse på slaven
{
  return readData;
}


