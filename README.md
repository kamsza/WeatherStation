# Weather station based on MySensors network

The purpose of the engineering task was to design and build a weather station using commercially available sensors. All messages between the sensor and the station are sent by radio using the SPI interface and the MySensors protocol, operating in the 2.4 GHz band.

### Sensor

The sensor is a device based on Arduino Nano, with an attached nrf24l01 radio module. The following sensors were used:
* DHT22 - temperature and humidity sensor,
* BMP 180 - temperature and pressure sensor,
* HC-SR501 - motion detector.

### Station

The station is a device based on Arduino Mega, with an attached nrf24l01 radio module and TFT LCD 1.8" SPI display.

## Used liblaries

The following liblaries were used in a project:

* [MySensors](https://www.mysensors.org/)
* [DHT.h](https://github.com/adafruit/DHT-sensor-library)
* [SFE_BMP180.h](https://github.com/LowPowerLab/SFE_BMP180)
* [Adafruit_GFX](https://github.com/adafruit/Adafruit-GFX-Library)
* [Adafruit_ST7735](https://github.com/adafruit/Adafruit-ST7735-Library)
