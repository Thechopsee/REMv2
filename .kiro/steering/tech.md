# Tech Stack

## Build System

- **PlatformIO** — project config in `platformio.ini`
- Target environment: `nodemcu-32s` (ESP32)
- Framework: Arduino
- Simulator: Wokwi (config in `wokwi.toml`, uses built ELF from `.pio/build/`)

## Libraries (lib_deps)

| Library | Purpose |
|---|---|
| ESPAsyncWebServer (me-no-dev) | Async HTTP server serving the control UI |
| AsyncTCP (me-no-dev) | Async TCP layer required by ESPAsyncWebServer |
| I2Cdevlib-MPU6050 (jrowberg) | MPU6050 gyro/accelerometer driver |
| U8g2 (olikraus) | OLED display driver (SSD1306 and others) |
| TinyGPSPlus (mikalhart) ^1.0.3 | GPS NMEA parsing |
| ElegantOTA (ayushsharma82) ^3.1.7 | OTA firmware update UI at `/update` |

Build flag: `-DELEGANTOTA_USE_ASYNC_WEBSERVER=1` (required for ElegantOTA + async server integration)

## Serial / Upload Settings

- Monitor baud: `9600`
- Upload speed: `921600`
- Monitor filters: `time, colorize`

## Common Commands

```bash
# Build firmware
pio run

# Upload to connected board
pio run --target upload

# Open serial monitor
pio device monitor

# Build + upload + monitor in one step
pio run --target upload && pio device monitor

# Clean build artifacts
pio run --target clean
```

## Configuration Files

- `src/config/env.hh` — hostname, display I2C pins, timezone
- `src/config/secret.hh` — Wi-Fi SSID and password (**git-ignored, never commit**)
- `src/config/PinConfig.hh` — GPIO pin assignments (currently placeholder)
