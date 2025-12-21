#include <Arduino.h>
// #include <BLE2902.h>
// #include <BLEDevice.h>
// #include <BLEServer.h>
// #include <BLEUtils.h>

#include "TimeInterval.h"
#include "constants.h"
#include "gyro.h"

Gyro gyro;

// BLEServer* pServer;
// BLECharacteristic* pCharacteristic;
// bool deviceConnected = false;

// // Sensor variables
// int16_t ax, ay, az;
// int16_t gx, gy, gz;

// // LED pin
// #define LED_PIN 2

// String lastCommand = "";
// unsigned long lastSend = 0;
// const unsigned long debounceTime = 200;  // ms

// // --- BLE Callbacks ---
// class MyServerCallbacks : public BLEServerCallbacks {
//   void onConnect(BLEServer* pServer) {
//     deviceConnected = true;
//     digitalWrite(LED_PIN, HIGH);  // turn LED ON when connected
//   };
//   void onDisconnect(BLEServer* pServer) {
//     deviceConnected = false;
//     digitalWrite(LED_PIN, LOW);  // turn LED OFF when disconnected
//   }
// };

TimeInterval blinkInterval(50, 0, true);

void setup() {
  Wire.begin();

  Serial.begin(115200);

  while (!Serial);

  gyro.begin();

  // pinMode(LED_PIN, OUTPUT);
  // digitalWrite(LED_PIN, LOW);

  // BLEDevice::init("GestureGlove");
  // pServer = BLEDevice::createServer();
  // pServer->setCallbacks(new MyServerCallbacks());

  // BLEService* pService = pServer->createService(SERVICE_UUID);
  // pCharacteristic = pService->createCharacteristic(
  //     CHARACTERISTIC_UUID, BLECharacteristic::PROPERTY_NOTIFY |
  //                              BLECharacteristic::PROPERTY_READ |
  //                              BLECharacteristic::PROPERTY_WRITE);
  // pCharacteristic->addDescriptor(new BLE2902());
  // pService->start();
  // pServer->getAdvertising()->start();

  // Serial.println("Setup complete, waiting for gestures...");
}

void loop() {
  // mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);

  gyro.loop();

  if (blinkInterval.marked()) {
    Serial.print("X : Y : Z | ");
    Serial.print(gyro.x);
    Serial.print(" : ");
    Serial.print(gyro.y);
    Serial.print(" : ");
    Serial.println(gyro.z);
  }

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
