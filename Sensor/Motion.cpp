#include "Motion.h"


MotionSensor::MotionSensor(byte attachTo) :pin(attachTo){}

int MotionSensor::wasMovement() {
  return digitalRead(pin);
}
