#include "TemperatureAndPressure.h"
#include "Arduino.h"
#include <SFE_BMP180.h>
#include <Wire.h>


TemperatureAndPressureSensor::TemperatureAndPressureSensor(double currentAltitude) : currentAltitude(currentAltitude) {}

void TemperatureAndPressureSensor::setup() {
    if (!sensor.begin()) {
      Serial.println("BMP180 init fail\n\n");
      while(1) {};
    }
}

float TemperatureAndPressureSensor::getTemperature() {
  status = sensor.startTemperature();
  if (status == 0) {
    Serial.println("error starting temperature measurement\n");
    return 0;
  }

  delay(status);
  status = sensor.getTemperature(temperature);
  if (status == 0) {
    Serial.println("error retrieving temperature measurement\n");
    return 0;
  }

  return (float)temperature;
}

float TemperatureAndPressureSensor::getPressure() {
  getTemperature();
  status = sensor.startPressure(3);
  if (status == 0) {
    Serial.println("error starting pressure measurement\n");
    return 0;
  }

  delay(status);
  status = sensor.getPressure(pressure, temperature);
  if (status == 0) {
    Serial.println("error retrieving pressure measurement\n");
    return 0;
  }

   return (float)pressure;
}

float TemperatureAndPressureSensor::getSeaLevelPressure() {
  getPressure();
  seaLevelPressure = sensor.sealevel(pressure, currentAltitude);
  return (float)seaLevelPressure;
}
