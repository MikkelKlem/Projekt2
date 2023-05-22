#ifndef MASTER_H
#define MASTER_H

#include <Wire.h>

#define RTC_ADDRESS 0x68 // I2C address of the RTC module

#define ALARMADDRESS 0b01110000
#define BLINDERADDRESS 0b01110010
#define COFFEEADDRESS 0b01110100
#define LIGHTSADDRESS 0b01110110

enum Routine {
  ROUTINE1,
  ROUTINE2,
  ROUTINE3,
  ROUTINE4
};

enum Command {
  CMD_COFFEE,
  CMD_CURTAINS,
  CMD_LIGHTS,
  CMD_TOAST
};

void executeRoutine(Routine routine);
void executeCommands(const byte* commands, size_t numCommands);
void sendCommandToSlave(byte slaveAddress, byte command);
void getTimeFromRTC(uint8_t& hour, uint8_t& minute, uint8_t& second);
bool isTimeReached(uint8_t targetHour, uint8_t targetMinute);

#endif // MASTER_H
