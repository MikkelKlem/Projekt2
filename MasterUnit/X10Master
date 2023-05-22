#include "X10protoMaster.h"

//funktioner underlæggende til den simulerede transmition:
String manchesterEncode(unsigned char n) {
  String encoded = "";
  for (int i = 0; i < 8; i++) {
    int bit = (n >> (7 - i)) & 1;
    if (bit == 0) {
      encoded += "01";
    } else {
      encoded += "10";
    }
  }
  return encoded;
}

unsigned char binaryStringToUnsignedChar(String binaryString) {
  unsigned char result = 0;
  int length = binaryString.length();

  for (int i = 0; i < length; i++) {
    result = (result << 1);
    if (binaryString[i] == '1') {
      result = (result | 0x01);
    } else if (binaryString[i] != '0') {
      // Hvis strengen indeholder andet end 0 og 1
      return 0;
    }
  }
  return result;
}
//funktioner til X10protoMaster klassen:

X10protoMaster::X10protoMaster()
{
    coffee_ = false;
    alarm_ = false;
    lights_ = false;
    blinders_ = false;
}

X10protoMaster::~X10protoMaster()
{
}

void X10protoMaster::sendChar(unsigned char Char, int address)
{

  _delay_ms(1000);
    String s, sb1, sb2;
    unsigned char b1, b2;

    s = manchesterEncode(Char);

    for (size_t i = 0; i < s.length()/2; i++)
    {
        sb1 += s[i] ;
    }

    for (size_t i = 8; i < s.length(); i++)
    {
        sb2 += s[i];
    }

    b1 = binaryStringToUnsignedChar(sb1);
    b2 = binaryStringToUnsignedChar(sb2);

    Wire.beginTransmission(address);
    Wire.write(b1);             // sends one char  
    Wire.write(b2);             // sends one char
    Wire.endTransmission();    // stop transmitting
}

void X10protoMaster::searchForUnits() {
    bool attributes[] = {false, false, false, false};

    for (int address = 0; address < 4; address++) {
        int calcAddress = (address + 56) << 1;
        Wire.beginTransmission(calcAddress);
        byte error = Wire.endTransmission();
        _delay_ms(100);
        if (error == 0) {
            attributes[address] = true;
        } else  {
          PORTB = error;
          _delay_ms (200);
          PORTB = 0;
          _delay_ms(100);          
        }
    }
    alarm_ = attributes[0];
    blinders_ = attributes[1];
    coffee_ = attributes[2];
    lights_ = attributes[3];
}


unsigned char X10protoMaster::getUnits()
{
    unsigned char units = 0;

    if (alarm_ == true)
    {
        units |= 0b00000001;
    }
    if (blinders_ == true)
    {
        units |= 0b00000010;
    }   
    if (coffee_ == true)
    {
        units |= 0b00000100;
    }
    if (lights_ == true)
    {
        units |= 0b00001000;
    }
    return units;
}
