class Sensor {
public:
  Sensor(String name, unsigned long updateInterval);
  String name;
  String lastValue;
  unsigned long lastUpdate;
  unsigned long updateInterval;
  virtual void ReadValue();
  virtual void Begin();
};