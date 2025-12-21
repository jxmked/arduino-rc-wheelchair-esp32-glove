#include <Arduino.h>
// #include <BLE2902.h>
// #include <BLEDevice.h>
// #include <BLEServer.h>
// #include <BLEUtils.h>

#include "TimeInterval.h"
#include "constants.h"
#include "gyro.h"

Gyro gyro;

TimeInterval update_hz(20, 0, true);

bool is_connected = false;

void setup() {
  Wire.begin();

  Serial.begin(115200);

  while (!Serial);

  gyro.begin();

  is_connected = true;
}

void loop() {
  gyro.loop();

  if (!is_connected) {
    // Attempt to connect
    return;
  }

  if (!update_hz.marked()) return;

  const float x = gyro.x;
  const float y = gyro.y;

  // Prevent sending the same command over and over again
  static uint8_t last_command = 0x0;

  uint8_t command = 0x0;  // We're only using 4-bit bitwise here. ;)

  // Serial.print("X : Y : Z | ");
  // Serial.print(gyro.x);
  // Serial.print(" : ");
  // Serial.print(gyro.y);
  // Serial.print(" : ");
  // Serial.println(gyro.z);

  if (x >= 6500.0) {          // Left
    command |= 0x8;           // 1000
  } else if (x <= -4200.0) {  /// Right
    command |= 0x4;           // 0100
  } else {                    // Center
    command &= ~0xC;          // 1100
  }

  if (y >= 4100.0) {          // Forward
    command |= 0x1;           // 0001
  } else if (y <= -4600.0) {  // Reverse
    command |= 0x2;           // 0010
  } else {                    // Center
    command &= ~0x3;          // 0011
  }

  // Only send the new command. :)
  if (last_command == command) return;
  last_command = command;

  Serial.println(command, BIN);
  // Send Command

  // Serial.print("BX : BY | ");
  // Serial.print(bx);
  // Serial.print(" : ");
  // Serial.println(by);

  // String command = "";

  // if (ay > 15000)
  //   command = "FORWARD";
  // else if (ay < -15000)
  //   command = "REVERSE";
  // else if (ax > 15000)
  //   command = "RIGHT";
  // else if (ax < -15000)
  //   command = "LEFT";
  // else
  //   command = "STOP";

  // if (deviceConnected && millis() - lastSend > debounceTime) {
  //   lastSend = millis();
  //   pCharacteristic->setValue(command.c_str());
  //   pCharacteristic->notify();

  //   // LED stays ON while connected, but we can blink it when sending
  //   digitalWrite(LED_PIN, HIGH);
  //   Serial.println("\033[32mSent: " + command +
  //                  "\033[0m");  // green text in Serial Monitor
  // }
}
