/* #include <Arduino.h>
#include <Wire.h>
// Pin numbers for the LEDs
const int ledPin1 = 13;  // The onboard LED
const int ledPin2 = 12;  // Custom LED connected to pin 12
const int ledPin3 = 11;  // Custom LED connected to pin 11
const int ledPin4 = 10;  // Custom LED connected to pin 10

void setup() {
  // Initialize the LED pins as output    
  pinMode(ledPin1, OUTPUT);
  pinMode(ledPin2, OUTPUT);
  pinMode(ledPin3, OUTPUT);
  pinMode(ledPin4, OUTPUT);
}

void loop() {
  // Turn on LED 1
  digitalWrite(ledPin1, HIGH);
  delay(1000);  // Wait for 1 second

  // Turn off LED 1
  digitalWrite(ledPin1, LOW);
  delay(1000);  // Wait for 1 second

  // Turn on LED 2
  digitalWrite(ledPin2, HIGH);
  delay(1000);  // Wait for 1 second

  // Turn off LED 2
  digitalWrite(ledPin2, LOW);
  delay(1000);  // Wait for 1 second
  // Turn on LED 1
  
  digitalWrite(ledPin3, HIGH);
  delay(1000);  // Wait for 1 second

  // Turn off LED 1
  digitalWrite(ledPin3, LOW);
  delay(1000);  // Wait for 1 second

  // Turn on LED 2
  digitalWrite(ledPin4, HIGH);
  delay(1000);  // Wait for 1 second

  // Turn off LED 2
  digitalWrite(ledPin4, LOW);
  delay(1000);  // Wait for 1 second
  
}
