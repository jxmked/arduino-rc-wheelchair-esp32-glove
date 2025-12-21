#include "gyro.h"

#include <Arduino.h>
#include <MPU6050.h>
#include <Wire.h>

#include "TimeInterval.h"
#include "constants.h"

Gyro::Gyro()
    : mpu(),
      axis{0, 0, 0},
      x(0),
      y(0),
      z(0),
      __interval(SAMPLING_INTERVAL_MS, 0, true) {}

void Gyro::begin() {
  mpu.initialize();

  pinMode(LED_ERROR_PIN, OUTPUT);

  digitalWrite(LED_ERROR_PIN, HIGH);

  while (!mpu.testConnection()) {
    Serial.println("MPU6050 connection failed");
    Serial.println("Retrying to connect to MPU6050...");
    delay(500);
  }

  Serial.println("MPU6050 connection successful");

  digitalWrite(LED_ERROR_PIN, LOW);
}

void Gyro::loop() {
  int16_t ax = mpu.getAccelerationX();
  int16_t ay = mpu.getAccelerationY();
  int16_t az = mpu.getAccelerationZ();

  axis.x += ax;
  axis.y += ay;
  axis.z += az;

  __sample_take++;

  if (__interval.marked()) {
    x = static_cast<float>(axis.x) / static_cast<float>(__sample_take);
    y = static_cast<float>(axis.y) / static_cast<float>(__sample_take);
    z = static_cast<float>(axis.z) / static_cast<float>(__sample_take);

    axis.x = 0;
    axis.y = 0;
    axis.z = 0;

    __sample_take = 0;
  }
}
