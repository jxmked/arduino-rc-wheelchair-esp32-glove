#include <Arduino.h>
#include <BLE2902.h>
#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>

#include "TimeInterval.h"
#include "constants.h"
#include "gyro.h"

Gyro gyro;

TimeInterval update_hz(30, 0, true);

BLECharacteristic* ble_chartic;

bool is_connected = false;

class ServerCallback : public BLEServerCallbacks {
  void onConnect(BLEServer* ble_server) {
    is_connected = true;

    Serial.println("Server Connected");
  };

  void onDisconnect(BLEServer* ble_server) {
    is_connected = false;

    Serial.println("Client Disconnected");

    ble_server->getAdvertising()->start();
    Serial.println("Bluetooth advertised");
  }
};

void setup() {
  Wire.begin();

  pinMode(LED_RED_PIN, OUTPUT);
  pinMode(LED_GREEN_PIN, OUTPUT);

  // Turn Red Light On To notify
  digitalWrite(LED_RED_PIN, HIGH);

  Serial.begin(115200);

  while (!Serial);

  Serial.println("Glove is booting...");
  Serial.println("Connecting to client...");

  BLEDevice::init("esp32-glove-server");

  BLEServer* ble_server = BLEDevice::createServer();
  ble_server->setCallbacks(new ServerCallback());

  BLEService* ble_service = ble_server->createService(SERVICE_UUID);

  ble_chartic = ble_service->createCharacteristic(
      CHARACTERISTIC_UUID, BLECharacteristic::PROPERTY_READ |
                               BLECharacteristic::PROPERTY_WRITE |
                               BLECharacteristic::PROPERTY_NOTIFY);

  ble_chartic->addDescriptor(new BLE2902());

  ble_service->start();

  BLEAdvertising* ble_advertz = BLEDevice::getAdvertising();

  ble_advertz->addServiceUUID(SERVICE_UUID);
  ble_advertz->setScanResponse(true);
  ble_advertz->setMinPreferred(0x06);
  ble_advertz->setMinPreferred(0x12);

  BLEDevice::startAdvertising();

  Serial.println("Waiting for client connection...");

  gyro.begin();

  digitalWrite(LED_RED_PIN, LOW);
  digitalWrite(LED_GREEN_PIN, HIGH);
}

void loop() {
  gyro.loop();

  if (!is_connected) {
    digitalWrite(LED_GREEN_PIN, LOW);
    digitalWrite(LED_RED_PIN, HIGH);
    return;  // Attempt to connect
  }

  digitalWrite(LED_RED_PIN, LOW);
  digitalWrite(LED_GREEN_PIN, HIGH);

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

  // Make sure we remain connected before sending anything
  if (!is_connected) return;

  // Send Command
  ble_chartic->setValue(&command, 1);
  ble_chartic->notify();

  digitalWrite(LED_GREEN_PIN, LOW);
}
