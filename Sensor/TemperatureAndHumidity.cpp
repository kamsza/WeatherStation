#include "TemperatureAndHumidity.h"
#include "Arduino.h"
#include "DHT.h"

TemperatureAndHumiditySensor::TemperatureAndHumiditySensor(byte attachTo) :pin(attachTo), dht(attachTo, type){
    dht.begin();
}

float TemperatureAndHumiditySensor::readHumidity() {
    humidity = dht.readHumidity();
      
    if (isnan(humidity)) {
        Serial.println("Failed to read humidity from DHT sensor!");
        return 0;
    }

    return humidity;
}
float TemperatureAndHumiditySensor::readTemperature() {
    temperature = dht.readTemperature();

    if (isnan(temperature)) {
        Serial.println("Failed to read temperature from DHT sensor!");
        return 0;
    }

    return temperature;
}

int TemperatureAndHumiditySensor::getMinimumUpdateInterval() {
    return 2000;
}
