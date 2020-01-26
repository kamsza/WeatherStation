// Enable debug prints
//#define MY_DEBUG
//#define MY_DEBUG_VERBOSE

// Enable and select radio type attached
#define MY_RADIO_RF24

#define MY_BAUD_RATE 9600

#define MY_RF24_CE_PIN 9
#define MY_RF24_CS_PIN 10

#define MY_NODE_ID 22

#include <SPI.h>
#include <MySensors.h>
#include "TemperatureAndHumidity.h"
#include "TemperatureAndPressure.h"
#include "Motion.h"


// Set this offset if the sensor has a permanent small offset to the real temperatures.
// In Celsius degrees (as measured by the device)
#define SENSOR_TEMP_OFFSET 0

// Sleep time between sensor updates (in milliseconds)
// Must be >1000ms for DHT22 and >2000ms for DHT11
static const uint64_t UPDATE_INTERVAL = 2000;
static const uint64_t LOOP_UPDATE_INTERVAL = (uint64_t)UPDATE_INTERVAL / 5;

// Force sending an update of the temperature after n sensor reads, so a controller showing the
// timestamp of the last update doesn't show something like 3 hours in the unlikely case, that
// the value didn't change since;
// i.e. the sensor would force sending an update every UPDATE_INTERVAL*FORCE_UPDATE_N_READS [ms]
static const uint8_t FORCE_UPDATE_N_READS = 2;

#define CHILD_ID_HUM 0
#define CHILD_ID_TEMP 1
#define CHILD_ID_PRES 2
#define CHILD_ID_MOT 3

float lastTemp = 0.0;
float lastHum = 0.0;
float lastPres = 0.0;
uint8_t nNoUpdatesTemp = 0;
uint8_t nNoUpdatesHum = 0;
uint8_t nNoUpdatesPres = 0;
bool metric = true;
TemperatureAndHumiditySensor dhtSensor(6);
TemperatureAndPressureSensor bmpSensor;
MotionSensor hcSensor(4);

MyMessage msgHum(CHILD_ID_HUM, V_HUM);
MyMessage msgTemp(CHILD_ID_TEMP, V_TEMP);
MyMessage msgPres(CHILD_ID_PRES, V_PRESSURE);
MyMessage msgMov(CHILD_ID_MOT, V_TRIPPED);

void presentation()
{
    // Send the sketch version information to the gateway
    sendSketchInfo("TemperatureAndHumidity", "1.1");

    // Register all sensors to gw (they will be created as child devices)
    present(CHILD_ID_HUM, S_HUM);
    present(CHILD_ID_TEMP, S_TEMP);
    present(CHILD_ID_PRES, S_BARO);
    present(CHILD_ID_MOT, S_MOTION);
    
    metric = getControllerConfig().isMetric;
}

void setup()
{  Serial.begin(9600);
  Serial.println("a");
    if (UPDATE_INTERVAL <= dhtSensor.getMinimumUpdateInterval())
    {
       Serial.println("Warning: UPDATE_INTERVAL is smaller than supported by the sensor!");
    }

    // init BMP180 sensor
    bmpSensor.setup();
    
    // Sleep for the time of the minimum sampling period to give the sensor time to power up
    // (otherwise, timeout errors might occure for the first reading)
    sleep(UPDATE_INTERVAL);
}

void loop()
{     

	temperatureMesurement();
	
	// Sleep for a while to save energy
	sleep(LOOP_UPDATE_INTERVAL);
	pressureMesurement();
	
	sleep(LOOP_UPDATE_INTERVAL);

	movementMesurement();
	
	sleep(LOOP_UPDATE_INTERVAL);

	humidityMesurement();
	
	sleep(LOOP_UPDATE_INTERVAL);

  // movement measured twice to not miss a signal
	movementMesurement();
	
	sleep(LOOP_UPDATE_INTERVAL);
}

void temperatureMesurement() {
	// Get temperature from DHT library
    float temperature = dhtSensor.readTemperature();
    if (temperature != lastTemp || nNoUpdatesTemp == FORCE_UPDATE_N_READS)
    {
        // Only send temperature if it changed since the last measurement or if we didn't send an update for n times
        lastTemp = temperature;

        // apply the offset before converting to something different than Celsius degrees
        temperature += SENSOR_TEMP_OFFSET;

        // Reset no updates counter
        nNoUpdatesTemp = 0;
        send(msgTemp.set(temperature, 1));
    }
    else
    {
        // Increase no update counter if the temperature stayed the same
        nNoUpdatesTemp++;
    }
}

void humidityMesurement() {
	// Get humidity from DHT library
    float humidity = dhtSensor.readHumidity();
    if (humidity != lastHum || nNoUpdatesHum == FORCE_UPDATE_N_READS)
    {
       // Only send humidity if it changed since the last measurement or if we didn't send an update for n times
       lastHum = humidity;
       // Reset no updates counter
       nNoUpdatesHum = 0;
       send(msgHum.set(humidity, 1));
    }
    else
    {
        // Increase no update counter if the humidity stayed the same
        nNoUpdatesHum++;
    }
}

void pressureMesurement() {
	// Get pressure from SFE_BMP180 liblary
    float pressure = bmpSensor.getSeaLevelPressure();
    if (pressure - lastPres > 0.5 || pressure - lastPres  < -0.5 || nNoUpdatesPres == FORCE_UPDATE_N_READS)
    {
       // Only send pressure if it changed since the last measurement or if we didn't send an update for n times
       lastPres = pressure;
	   
       // Reset no updates counter
       nNoUpdatesPres = 0;
       send(msgPres.set(pressure, 1));
    }
    else
    {
       // Increase no update counter if the humidity stayed the same
       nNoUpdatesPres++;
    }    
}

void movementMesurement() {
	int movement = hcSensor.wasMovement();
    send(msgMov.set(movement));
}
