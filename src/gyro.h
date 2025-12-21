#ifndef GYRO_H
#define GYRO_H

#include <Arduino.h>
#include <MPU6050.h>
#include <Wire.h>

#include "TimeInterval.h"
#include "constants.h"

struct axis_t {
  int32_t x;
  int32_t y;
  int32_t z;
};

class Gyro {
 public:
  Gyro();

  void begin();
  void loop();

  float x;
  float y;
  float z;

 private:
  MPU6050 mpu;
  axis_t axis;
  unsigned long __sample_take;
  TimeInterval __interval;
};

#endif  // GYRO_H