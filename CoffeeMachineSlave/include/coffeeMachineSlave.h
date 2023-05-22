
#ifndef COFFEE_MACHINE_SLAVE_H
#define COFFEE_MACHINE_SLAVE_H

#include <Arduino.h>
#include <Wire.h>

#define slaveAddress1 0b01110000 // I2C address of the coffee machine slave unit

const int ledPin1 = 13;  // The onboard LED
const int ledPin2 = 12;  // Custom LED connected to pin 12
const int ledPin3 = 11;  // Custom LED connected to pin 11
const int ledPin4 = 10;  // Custom LED connected to pin 10
// Define commands
#define CMD_COFFEE 0x01
#define CMD_CAPPUCCINO 0x02
#define CMD_ESPRESSO 0x03
#define CMD_CHOCOLATE_MILK 0x04

void receiveCommand(int numBytes);
void handleCommand(byte command);
void setup();

#endif // COFFEE_MACHINE_SLAVE_H
