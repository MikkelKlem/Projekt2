#ifndef MYCLASS_H
#define MYCLASS_H
#include "string.h"

// Slavernes forskellige addresser
#define ALARMADDRESS 0b01110000
#define BLINDERADDRESS 0b01110010
#define COFFEEADDRESS 0b01110100
#define LIGHTSADDRESS 0b01110110

void receiveEvent(int howMany);

class X10ProtoSlave {
public:
    X10ProtoSlave(int slaveDevice = ALARMADDRESS);
    char readChar();
private:
    
};

#endif  // MYCLASS_H



