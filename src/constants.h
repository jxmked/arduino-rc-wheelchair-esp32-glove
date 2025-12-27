#ifndef CONSTANTS_H
#define CONSTANTS_H

#define SERVICE_UUID "c973126d-5afe-4aec-ab49-f8ffbd14f059"
#define CHARACTERISTIC_UUID "9ca77c0d-14a4-403d-9677-0c2bf42b8194"

#define BLE_HOST_NAME "esp32-glove-server"

#define LED_GREEN_PIN 3
#define LED_RED_PIN 2

#define SAMPLING_INTERVAL_MS \
  100  // Instead of sample every loop, do it every ms

#endif  // CONSTANTS_H