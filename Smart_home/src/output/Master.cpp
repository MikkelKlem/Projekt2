#include <Wire.h>
#include <arduino.h>
#include "RTC.h"
#include "Master.h"

#define RTC_ADDRESS 0x68 // I2C address of the RTC module
#define slaveAddress1 0b01110000 // I2C address of the slave units
#define slaveAddress2 0b01110010
#define slaveAddress3 0b01110100
#define slaveAddress4 0b01110110
#define CMD_COFFEE 0x11 // Commands for the slave units

Routine currentRoutine = ROUTINE1;

void setup() {
  Wire.begin();
  Serial.begin(9600);
  delay(2000); 
  // setDateTime(2023, 5, 22, 10, 22, 10); // Sets the date and time, only used at the start for the RTC unit
}

struct RoutineData { // Struct to hold the data for each routine
  Routine routine;
  uint8_t targetHour;
  uint8_t targetMinute;
}; 

// Specify the target times for each routine as variables has to go before the const routinedata array
uint8_t routine1TargetHour = 13;
uint8_t routine1TargetMinute = 21;
uint8_t routine2TargetHour = 13;
uint8_t routine2TargetMinute = 23;
uint8_t routine3TargetHour = 18;
uint8_t routine3TargetMinute = 45;
uint8_t routine4TargetHour = 22;
uint8_t routine4TargetMinute = 30;

// Define the routines with their target times
const RoutineData routines[] = {
  { ROUTINE1, routine1TargetHour, routine1TargetMinute },
  { ROUTINE2, routine2TargetHour, routine2TargetMinute },
  { ROUTINE3, routine3TargetHour, routine3TargetMinute },
  { ROUTINE4, routine4TargetHour, routine4TargetMinute }
};

const char* routineNames[] = { // Array of routine names
  "Morning",
  "Afternoon",
  "Evening",
  "Night"
};

// Commands for each routine
const byte morningRoutine[] = {
  CMD_COFFEE,
  CMD_CURTAINS,
  CMD_LIGHTS,
  CMD_TOAST
};

const byte afternoonRoutine[] = {
  CMD_LIGHTS,
  CMD_COFFEE
};

const byte eveningRoutine[] = {
  CMD_CURTAINS
};

const byte nightRoutine[] = {
  CMD_COFFEE,
  CMD_CURTAINS,
  CMD_LIGHTS
};

Routine getCurrentRoutine(uint8_t hour, uint8_t minute) {
  for (const auto& routineData : routines) {
    if (routineData.targetHour == hour && routineData.targetMinute == minute) {
      return routineData.routine;
    }
  }
  return ROUTINE1; // Default to morning routine if no match is found
}

Routine getNextRoutine(Routine currentRoutine) {
  // Find the index of the current routine
  int currentRoutineIndex = -1;
  for (size_t i = 0; i < sizeof(routines) / sizeof(routines[0]); i++) {
    if (routines[i].routine == currentRoutine) {
      currentRoutineIndex = i;
      break;
    }
  }

  // Determine the index of the next routine
  int nextRoutineIndex = (currentRoutineIndex + 1) % (sizeof(routines) / sizeof(routines[0]));

  // Return the next routine
  return routines[nextRoutineIndex].routine;
}

void executeRoutine(Routine routine) {
  // Print the name of the current routine
  Serial.print("Executing routine: ");
  Serial.println(routineNames[routine]);

  switch (routine) { // Switch case for the different routines
    case ROUTINE1:
      executeCommands(morningRoutine, sizeof(morningRoutine));
      break;
    case ROUTINE2:
      executeCommands(afternoonRoutine, sizeof(afternoonRoutine));
      break;
    case ROUTINE3:
      executeCommands(eveningRoutine, sizeof(eveningRoutine));
      break;
    case ROUTINE4:
      executeCommands(nightRoutine, sizeof(nightRoutine));
      break;
  }
}

void executeCommands(const byte* commands, size_t numCommands) {
  for (size_t i = 0; i < numCommands; i++) {
    byte command = commands[i];
    // Send the command to the respective slave unit
    switch (command) {
      case CMD_COFFEE:
        sendCommandToSlave(slaveAddress1, CMD_COFFEE);
        break;
      case CMD_CURTAINS:
        sendCommandToSlave(slaveAddress2, CMD_CURTAINS);
        break;
      case CMD_LIGHTS:
        sendCommandToSlave(slaveAddress3, CMD_LIGHTS);
        break;
      case CMD_TOAST:
        sendCommandToSlave(slaveAddress4, CMD_TOAST);
        break;
      default:
        // Invalid command
        break;
    }
    delay(100); // Delay between sending commands (adjust as needed)
  }
}

void sendCommandToSlave(byte slaveAddress, byte command) {
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

bool isTimeReached(uint8_t targetHour, uint8_t targetMinute) {
  uint8_t currentHour, currentMinute, currentSecond;
  getTimeFromRTC(currentHour, currentMinute, currentSecond);

  if (currentHour == targetHour && currentMinute == targetMinute) {
    return true;
  } else {
    return false;
  }
}

void loop() {
  static unsigned long lastTime = 0;
  uint8_t currentHour, currentMinute, currentSecond;
  unsigned long currentTime = millis();

  if (currentTime - lastTime >= 1000) { // Delay of 1 second for the RTC
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

    // Check if the current time matches any of the routine target times
    for (const auto& routineData : routines) {
      if (routineData.targetHour == currentHour && routineData.targetMinute == currentMinute) {
        Serial.println("Executing routine");

        // Execute the current routine
        executeRoutine(routineData.routine);
        
        // Switch to the next routine
        currentRoutine = getNextRoutine(routineData.routine);
        break; // Exit the loop after finding a matching routine
      }
    }
  }
}