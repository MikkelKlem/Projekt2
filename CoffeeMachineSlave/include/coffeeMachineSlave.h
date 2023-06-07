#ifndef COFFEE_MACHINE_SLAVE_H
#define COFFEE_MACHINE_SLAVE_H

#include <Wire.h>
#include "Arduino.h"
#define slaveAddress1 0b01110000 // I2C address of the coffee machine slave unit

const int ledPin1 = 13;  // The onboard LED
const int ledPin2 = 12;  // Custom LED connected to pin 12
const int ledPin3 = 11;  // Custom LED connected to pin 11
const int ledPin4 = 10;  // Custom LED connected to pin 10

const char recievedchars[] = {
  'A', // Character for ROUTINE1
  'B', // Character for ROUTINE2
  'C', // Character for ROUTINE3
  'D',  // Character for ROUTINE4
};

void receiveCommand(int numBytes); // Function to receive commands from master
void handleCommand(char command); // Function to handle commands from master
void setup();

#endif // COFFEE_MACHINE_SLAVE_H
