#include "Arduino.h"
#include <Wire.h>
#include "string.h"
using namespace std;

#define ALARMADDRESS 0b01110000
#define BLINDERADDRESS 0b01110010
#define COFFEEADDRESS 0b01110100
#define LIGHTSADDRESS 0b01110110

class X10protoMaster
{
private:
    bool alarm_;
    bool blinders_;
    bool coffee_;
    bool lights_;
public:
    X10protoMaster();
    ~X10protoMaster();
    void sendChar(unsigned char Char, int address);
    void searchForUnits();
    unsigned char getUnits();
};
