#include "Arduino.h"

class MotionSensor {
	private:
	const byte pin;
	
	public:
	MotionSensor(byte attachTo);
	int wasMovement();
};
