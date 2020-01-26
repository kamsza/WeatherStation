# Sensors

## Arduino Uno/Nano Connections

Connections shown below are default connections used in the project, some of them can be changed in Sensor.ino file.

### Radio - nRF24l01

nRF24l01 pins numbers

Name | Num | Num | Name
:-----:|:-----:|:-----:|:-----:
GND|1|2|3.3V
CE|3|4|CS
SCK|5|6|MOSI
MISO|7|8|IRQ

SPI Connections

nRF24l01|Mega
:--------:|:----:
1|GND
2|3.3V
3|D9
4|D10
5|D13
6|D11
7|D12
8|-


### Temperature and humidity - DHT22

DHT22| Arduino
:------:|:--------:
VCC|5V
DATA|D6
NC|-
GND|GND



### Temperature and pressure - BMP180

BMP180 | Arduino
:------:|:--------:    
VCC|5V
GND|GND 
SCL|A5
SDA|A4


### Movement sensor - HC-SR501

HC-SR501 | Arduino
:------:|:--------:
GND|GND
DATA|D4
VCC|5V

