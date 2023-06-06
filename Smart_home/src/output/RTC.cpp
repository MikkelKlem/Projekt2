#include "RTC.h"
#include <Arduino.h>
#include <Wire.h>
#define RTC_ADDRESS 0x68 // I2C address of the RTC module

// Set the date and time and send it to the RTC module using I2C
void setDateTime(uint16_t year, uint8_t month, uint8_t day, uint8_t hour, uint8_t minute, uint8_t second) 
{
  Wire.write(0); // set starting register address to 0x00
  Wire.write(decToBcd(second));
  Wire.write(decToBcd(minute));
  Wire.write(decToBcd(hour));
  Wire.write(decToBcd(0)); 
  Wire.write(decToBcd(day));
  Wire.write(decToBcd(month));
  Wire.write(decToBcd(year - 2000));
  Wire.endTransmission();
}

void printDateTime() //prints date and time to serial monitor
{ 
  Wire.beginTransmission(RTC_ADDRESS);
  Wire.write(0); // set the starting register address to 0x00 
  Wire.endTransmission();
 
  Wire.requestFrom(RTC_ADDRESS, 7); // Request 7 bytes from the RTC module

  uint8_t second = bcdToDec(Wire.read() & 0x7F);
  uint8_t minute = bcdToDec(Wire.read());
  uint8_t hour = bcdToDec(Wire.read() & 0x3F);
  Wire.read(); // Ignore the 4th byte as it contains the day of week (not needed)
  uint8_t day = bcdToDec(Wire.read()); 
  uint8_t month = bcdToDec(Wire.read());
  uint16_t year = 2000 + bcdToDec(Wire.read()); 

  //print the date and time to the serial monitor
  Serial.print(year);
  Serial.print("-");
  printDigits(month);
  Serial.print("-");
  printDigits(day);
  Serial.print(" ");
  printDigits(hour);
  Serial.print(":");
  printDigits(minute);
  Serial.print(":");
  printDigits(second);
  Serial.println();
}

uint8_t decToBcd(uint8_t dec) {
  return (dec / 10 * 16) + (dec % 10); // Convert normal decimal numbers to binary coded decimal
}

uint8_t bcdToDec(uint8_t bcd) {
  return (bcd / 16 * 10) + (bcd % 16); // Convert binary coded decimal to normal decimal numbers
}

void printDigits(uint8_t digits) { 
  if (digits < 10)
    Serial.print("0"); // print leading zero if the number is smaller than 10
  Serial.print(digits); // print the actual number
}
