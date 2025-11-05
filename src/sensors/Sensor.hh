class Sensor {
public:
  Sensor(String name, std::function<float(void)> readValue, unsigned long updateInterval);
  String name;
  std::function<float(void)> readValue;
  float lastValue;
  unsigned long lastUpdate;
  unsigned long updateInterval;
};