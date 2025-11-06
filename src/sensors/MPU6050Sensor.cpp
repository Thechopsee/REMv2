#include "MPU6050Sensor.hh"

MPU6050Sensor::MPU6050Sensor(std::string name, unsigned long updateInterval, int sdaPin, int sclPin)
  : Sensor(name, updateInterval),
    _sdaPin(sdaPin),
    _sclPin(sclPin),
    _mpu()
{}

void MPU6050Sensor::Begin() {
  Serial.println("[MPU6050] Initializing...");

  Wire.begin();
  delay(200);

  _mpu.initialize();

  if (!_mpu.testConnection()) {
    Serial.println("[MPU6050] Connection failed! Check wiring.");
    _initialized = false;
    return;
  }

  Serial.println("[MPU6050] Connected successfully!");
  _initialized = true;

  _mpu.CalibrateAccel(6);
  _mpu.CalibrateGyro(6);
}

void MPU6050Sensor::ReadValue() {
  if (!_initialized) return;

  if (millis() - lastUpdate >= updateInterval) {
    int16_t ax, ay, az;
    int16_t gx, gy, gz;
    _mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);

    char buf[128];
    snprintf(buf, sizeof(buf),
      "AX:%d AY:%d AZ:%d | GX:%d GY:%d GZ:%d",
      ax, ay, az, gx, gy, gz
    );

    lastValue = buf;
    Serial.print("[MPU6050] New Update:");
    Serial.println(lastValue.c_str());
    lastUpdate = millis();
  }
}
