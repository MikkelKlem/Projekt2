#ifndef MASTER_H
#define MASTER_H

#include <Wire.h>

#define RTC_ADDRESS 0x68 // I2C address of the RTC module

#define slaveAddress1 0b01110000 // I2C address of the slave units
#define slaveAddress2 0b01110010
#define slaveAddress3 0b01110100
#define slaveAddress4 0b01110110

enum Rutine {
  Rutine1,
  Rutine2,
  Rutine3,
  Rutine4
};

enum Command {
  CMD_AMERICANO = 'A',
  CMD_ESPRESSO = 'B',
  CMD_LATTE = 'C',
  CMD_CAPPUCINO = 'D',
  CMD_TURNON = 'E',
  CMD_DIMLIGHT = 'F',
  CMD_BRIGHT = 'G',
  CMD_TURNOFF = 'H',
};

void executeRutine(Rutine Rutine);
void executeCommands(const char* commands, size_t numCommands);
void sendCommandToSlave(byte slaveAddress, char command);
void getTimeFromRTC(uint8_t& hour, uint8_t& minute, uint8_t& second);
bool isTimeReached(uint8_t targetHour, uint8_t targetMinute);

#endif // MASTER_H
