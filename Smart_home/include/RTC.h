
#ifndef RTC_H
#define RTC_H

#include <Arduino.h>
#include <Wire.h>


#define RTC_ADDRESS 0x68 // I2C address of the RTC module

void setDateTime(uint16_t year, uint8_t month, uint8_t day, uint8_t hour, uint8_t minute, uint8_t second);
void printDateTime();
uint8_t decToBcd(uint8_t dec);
uint8_t bcdToDec(uint8_t bcd);
void printDigits(uint8_t digits);
bool isTimeReached(uint8_t targetHour, uint8_t targetMinute);

#endif // RTC_H
