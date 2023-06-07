#include "CoffeeMachineSlave.h"

String responseMessage;

int main() {
  setup();
  while (true) {
    // Your main logic here
  }
}

void setup() {
  Serial.begin(9600);
  Wire.begin(slaveAddress1); // join I2C bus with address #112
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
    char command = Wire.read(); // Read the received character
    
    // Handle the command based on the received character
    handleCommand(command);
  }
  
  // Send the response message back to the master unit
  Wire.write(responseMessage.c_str());
}

void handleCommand(char command) {
  switch (command) {
    case 'A':
      // Turn on LED 1
      digitalWrite(ledPin1, HIGH);
      delay(1000);  // Wait for 1 second

      // Turn off LED 1
      digitalWrite(ledPin1, LOW);
      delay(1000);  // Wait for 1 second
      
      responseMessage = "Coffeemachine done";
      break;

    case 'B':
      // Turn on LED 2
      digitalWrite(ledPin2, HIGH);
      delay(1000);  // Wait for 1 second

      // Turn off LED 2
      digitalWrite(ledPin2, LOW);
      delay(1000);  // Wait for 1 second
      
      responseMessage = "Coffeemachine done";
      break;

    case 'C':
      // Turn on LED 3
      digitalWrite(ledPin3, HIGH);
      delay(1000);  // Wait for 1 second

      // Turn off LED 3
      digitalWrite(ledPin3, LOW);
      delay(1000);  // Wait for 1 second
      
      responseMessage = "Coffeemachine done";
      break;

    case 'D':
      // Turn on LED 4
      digitalWrite(ledPin4, HIGH);
      delay(1000);  // Wait for 1 second

      // Turn off LED 4
      digitalWrite(ledPin4, LOW);
      delay(1000);  // Wait for 1 second
      
      responseMessage = "Coffeemachine done";
      break;

    default:
      // Invalid command
      responseMessage = "invalid command";
      break;
  }
}
