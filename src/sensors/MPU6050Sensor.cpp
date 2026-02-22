#include "MPU6050Sensor.hh"

MPU6050Sensor::MPU6050Sensor(std::string name, unsigned long updateInterval, int sdaPin, int sclPin, bool enableLogging)
  : Sensor<GyroAcceleratorDataStruct>(name, updateInterval, enableLogging),
    _sdaPin(sdaPin),
    _sclPin(sclPin),
    _mpu()
{}

void MPU6050Sensor::Begin() {
  Serial.println("[MPU6050] Initializing...");

  Wire.begin();
  delay(200);

  Serial.println("Scanning I2C bus...");
  for (byte i = 1; i < 127; i++) {
    Wire.beginTransmission(i);
    if (Wire.endTransmission() == 0) {
      Serial.print("Device found at 0x");
      Serial.println(i, HEX);
    }
  }

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

void MPU6050Sensor::ReadValueInternal() {
  if (!_initialized) return;

  int16_t ax, ay, az;
  int16_t gx, gy, gz;
  _mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);

  char buf[128];
  snprintf(buf, sizeof(buf),
    "AX:%d AY:%d AZ:%d | GX:%d GY:%d GZ:%d",
    ax, ay, az, gx, gy, gz
  );

  lastValue = buf;
  lastOriginalValue = {ax, ay, az, gx, gy, gz};
  Serial.print("[MPU6050] New Update:");
  Serial.println(lastValue.c_str());
}
