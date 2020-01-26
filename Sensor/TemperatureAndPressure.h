#ifndef TemperatureAndPressureSensor_h
#define TemperatureAndPressureSensor_h

#include "Arduino.h"
#include <SFE_BMP180.h>
#include <Wire.h>

class TemperatureAndPressureSensor {
  private:
  SFE_BMP180 sensor;
  const double currentAltitude;
  char status;
  double temperature, pressure, seaLevelPressure;

  public:
  TemperatureAndPressureSensor(double currentAltitude = 225);
  // always call setup method before using getters
  void setup();
  float getTemperature();
  float getPressure();
  // needs correct current altitude 
  float getSeaLevelPressure();
};


#endif
