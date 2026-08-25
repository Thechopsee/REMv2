# REMv2 — Remote Effect Manager

REMv2 is a firmware application running on an **ESP32 (NodeMCU-32S)** that lets users control lighting effects and collect telemetry data from RC models (boats, cars, etc.) over Wi-Fi.

## Core Capabilities

- **Effect control** — Toggle lights/LEDs, run blink sequences, and drive servos from a browser-based UI served directly by the ESP32.
- **Sensor telemetry** — Read and expose data from sensors (e.g. MPU6050 gyro/accelerometer, GPS) via HTTP endpoints.
- **OLED display** — Shows status info (IP address, model name) on a small I2C OLED at startup and during operation.
- **Model profiles** — RC model-specific configurations (pin assignments, block groups) are isolated in profile classes, making it easy to swap between models.
- **OTA updates** — Firmware can be updated over the air via ElegantOTA at `/update`.
- **SD card logging** — Optional sensor data logging to SD card via `StorageService`.

## Target Hardware

- Board: NodeMCU-32S (ESP32)
- Display: SSD1306 OLED (I2C, various sizes supported)
- Sensors: MPU6050 (gyro/accelerometer), optional GPS (UART)
- Outputs: GPIO pins for LEDs, relays, servos
