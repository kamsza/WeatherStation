#ifndef TemperatureAndHumiditySensor_h
#define TemperatureAndHumiditySensor_h

#include "Arduino.h"
#include "DHT.h"

class TemperatureAndHumiditySensor {
  private:
    const uint8_t type = DHT22;
    const byte pin;
    float humidity;
    float temperature;
    DHT dht;

  public:
    TemperatureAndHumiditySensor(byte attachTo);
    float readHumidity();
    float readTemperature();
    int getMinimumUpdateInterval();
};

#endif
