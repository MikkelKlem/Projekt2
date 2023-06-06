#include <Wire.h>
#include "RTC.h"
#include "Master.h"
#include "moduleSettings.h"
#define RTC_ADDRESS 0x68 // I2C address of the RTC module
Rutine currentRutine = Rutine1;
moduleSettings settings;

const char targetReachedChars[] = {
  'A', // Character for Rutine1
  'B', // Character for Rutine2
  'C', // Character for Rutine3
  'D',  // Character for Rutine4
  'E', // Character for Rutine5
  'F', // Character for Rutine6
  'G', // Character for Rutine7
  'H'  // Character for Rutine8
};

void setup() {
  Wire.begin();
  Serial.begin(9600);
  delay(2000); 
}

struct RutineData { // Struct to hold the data for each Rutine
  Rutine rutine;
  uint8_t activationHour;
  uint8_t activationMinute;
}; 

// Specify the target times for each Rutine as variables have to go before the const Rutinedata array
uint8_t activationHour = 20;
uint8_t Rutine1activationMinute = 51;
uint8_t Rutine2activationHour = 20;
uint8_t Rutine2activationMinute = 52;
uint8_t Rutine3activationHour = 20;
uint8_t Rutine3activationMinute = 53;
uint8_t Rutine4activationHour = 20;
uint8_t Rutine4activationMinute = 54;

// Define the Rutines with their target times
const RutineData Rutines[] = {
  { Rutine1, activationHour, Rutine1activationMinute },
  { Rutine2, Rutine2activationHour, Rutine2activationMinute },
  { Rutine3, Rutine3activationHour, Rutine3activationMinute },
  { Rutine4, Rutine4activationHour, Rutine4activationMinute }
};

const char* RutineNames[] = { // Array of Rutine names
  "Morning",
  "Afternoon",
  "Evening",
  "Night"
};

const char morningRutine[] = {
  CMD_AMERICANO,
  CMD_TURNON
};

const char afternoonRutine[] = {
  CMD_LATTE,
  CMD_DIMLIGHT
};

const char eveningRutine[] = {
  CMD_CAPPUCINO,
  CMD_BRIGHT
};

const char nightRutine[] = {
  CMD_ESPRESSO,
  CMD_TURNOFF
};

Rutine getCurrentRutine(uint8_t hour, uint8_t minute) {
  for (const auto& RutineData : Rutines) {
    if (RutineData.activationHour == hour && RutineData.activationMinute == minute) {
      return RutineData.rutine;
    }
  }
  return Rutine1; // Default to morning Rutine if no match is found
}

Rutine getNextRutine(Rutine currentRutine) {
  // Find the index of the current Rutine
  int currentRutineIndex = -1;
  for (size_t i = 0; i < sizeof(Rutines) / sizeof(Rutines[0]); i++) {
    if (Rutines[i].rutine == currentRutine) {
      currentRutineIndex = i;
      break;
    }
  }

  // Determine the index of the next Rutine
  int nextRutineIndex = (currentRutineIndex + 1) % (sizeof(Rutines) / sizeof(Rutines[0]));

  // Return the next Rutine
  return Rutines[nextRutineIndex].rutine;
}

void executeRutine(Rutine Rutine) {
  // Print the name of the current Rutine
  Serial.print("Executing Rutine: ");
  Serial.println(RutineNames[Rutine]);

  switch (Rutine) { // Switch case for the different Rutines
    case Rutine1:
      executeCommands(morningRutine, sizeof(morningRutine));
      break;
    case Rutine2:
      executeCommands(afternoonRutine, sizeof(afternoonRutine));
      break;
    case Rutine3:
      executeCommands(eveningRutine, sizeof(eveningRutine));
      break;
    case Rutine4:
      executeCommands(nightRutine, sizeof(nightRutine));
      break;
  }
}

void executeCommands(const char* commands, size_t numCommands) {
  for (size_t i = 0; i < numCommands; i++) {
    char command = commands[i];
    // Send the command to the respective slave unit
    switch (command) {
      case CMD_AMERICANO:
        sendCommandToSlave(slaveAddress1, CMD_AMERICANO);
        break;
      case CMD_LATTE:
        sendCommandToSlave(slaveAddress2, CMD_LATTE);
        break;
      case CMD_CAPPUCINO:
        sendCommandToSlave(slaveAddress3, CMD_CAPPUCINO);
        break;
      case CMD_ESPRESSO:
        sendCommandToSlave(slaveAddress4, CMD_ESPRESSO);
        break;
      default:
        // Invalid command
        break;
    }
    //delay(100); Delay between sending commands (adjust as needed)
  }
}

void sendCommandToSlave(byte slaveAddress, char command) {
  Wire.beginTransmission(slaveAddress);
  Wire.write(command);
  Wire.endTransmission();
}

void getTimeFromRTC(uint8_t& hour, uint8_t& minute, uint8_t& second) {
  Wire.beginTransmission(RTC_ADDRESS);
  Wire.write(0);
  Wire.endTransmission();

  Wire.requestFrom(RTC_ADDRESS, 7);

  second = bcdToDec(Wire.read() & 0x7F); // 0x7F to remove the CH bit
  minute = bcdToDec(Wire.read());
  hour = bcdToDec(Wire.read() & 0x3F); // 0x3F to remove the 12/24 bit
}

bool isTimeReached(uint8_t activationHour, uint8_t activationMinute) {
  uint8_t currentHour, currentMinute, currentSecond;
  getTimeFromRTC(currentHour, currentMinute, currentSecond);

  if (currentHour == activationHour && currentMinute == activationMinute) {
    return true;
  } else {
    return false;
  }
}

void loop() {
  static unsigned long lastTime = 0;
  uint8_t currentHour, currentMinute, currentSecond;
  unsigned long currentTime = millis();

  if (currentTime - lastTime >= 5000) { // Delay of 1 second for the RTC
    lastTime = currentTime;

    getTimeFromRTC(currentHour, currentMinute, currentSecond); // Get the current time from the RTC
    String hourStr = currentHour < 10 ? "0" + String(currentHour) : String(currentHour); // Add a leading zero if the hour is less than 10
    String minuteStr = currentMinute < 10 ? "0" + String(currentMinute) : String(currentMinute); // Add a leading zero if the minute is less than 10
    String secondStr = currentSecond < 10 ? "0" + String(currentSecond) : String(currentSecond);// Add a leading zero if the second is less than 10

    Serial.print("Current Time: ");
    Serial.print(hourStr);
    Serial.print(":");
    Serial.print(minuteStr);
    Serial.print(":");
    Serial.println(secondStr);

    // Check if the current time matches any of the Rutine target times
    for (const auto& RutineData : Rutines) {
      if (isTimeReached(RutineData.activationHour, RutineData.activationMinute)) {
        currentRutine = RutineData.rutine;
        Serial.println("Target hour reached. Sending character: " + String(targetReachedChars[currentRutine]));
        executeRutine(currentRutine);
        break;
      }
    }
  }
}
