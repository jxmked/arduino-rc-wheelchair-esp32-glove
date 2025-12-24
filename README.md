# arduino-rc-wheelchair-esp32-glove

> This project will be compiled and push to the ESP32 C3 Super Mini using Arduino IDE by the client.
> That is the reason why all files remain in the ./src folder

> This is the repository to remote the [Wheelchair](https://github.com/jxmked/arduino-rc-wheelchair-esp32). Salamuch 💖

## How to use? 
1. Just turn it on. :)

# Modules & Hardwares
 - ESP32 C3 Super Mini
 - MPU-6050 Accelerometer
 - MT3608 DC to DC Converter
 - TP4056 BMS with type c/micro usb port
 - Switch
 - LED (2 Pieces w/ unique colors)
 - Lithium 18650 Battery

# Wirings and connnections

| ESP32 Pin | Type | Output Pin | Mode |
|:---:|:---:|:---:|:---:|
| 2 | Digital | LED RED + | Output |
| 3 | Digital | LED GREEN + | Output |
| 8 | SDA | MPU-6050 (SDA) | Data |
| 9 | SCL | MPU-6050 (SCL) | Clock |

# Circuit Diagram

![Glove Circuit Diagram](./schematic/diagram%20-%20wire%20colored.svg)

This is the circuit diagram with black and white only.

![Glove Circuit Diagram](./schematic/diagram%20-%20b&w.svg)

