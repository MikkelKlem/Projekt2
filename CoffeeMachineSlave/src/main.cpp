
#include "CoffeeMachineSlave.h"
void setup() {
  Wire.begin();
  Serial.begin(9600);
  Wire.begin(slaveAddress1);
  Wire.onReceive(receiveCommand);
  delay(2000); // Delay to allow the serial monitor to initialize
  // Initialize the LED pins as output    

  pinMode(ledPin1, OUTPUT);
  pinMode(ledPin2, OUTPUT);
  pinMode(ledPin3, OUTPUT);
  pinMode(ledPin4, OUTPUT);
}
void receiveCommand(int numBytes) {
  while (Wire.available()) {
    byte command = Wire.read();
    handleCommand(command);
  }
}

void handleCommand(byte command) {
  switch (command) {
    case CMD_COFFEE:
      // Turn on LED 1
      digitalWrite(ledPin1, HIGH);
      delay(1000);  // Wait for 1 second

      // Turn off LED 1
      digitalWrite(ledPin1, LOW);
      delay(1000);  // Wait for 1 second
      break;

    case CMD_CAPPUCCINO:
      // Turn on LED 2
      digitalWrite(ledPin2, HIGH);
      delay(1000);  // Wait for 1 second

      // Turn off LED 2
      digitalWrite(ledPin2, LOW);
      delay(1000);  // Wait for 1 second
      // Turn on LED 1
      break;

    case CMD_ESPRESSO:
      digitalWrite(ledPin3, HIGH);
      delay(1000);  // Wait for 1 second

      // Turn off LED 1
      digitalWrite(ledPin3, LOW);
      delay(1000);  // Wait for 1 second
      break;

    case CMD_CHOCOLATE_MILK:
      // Turn on LED 2
      digitalWrite(ledPin4, HIGH);
      delay(1000);  // Wait for 1 second

      // Turn off LED 2
      digitalWrite(ledPin4, LOW);
      delay(1000);  // Wait for 1 second
      break;

    default:
      // Invalid command
      break;
  }
}

int main() {
  setup();
  while (true) {
    
  }
} 