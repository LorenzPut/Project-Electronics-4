#include "Arduino.h"
#include "Ultrasoonsensor.h"

Ultrasoonsensor::Ultrasoonsensor(int trigPin, int echoPin)
{
	pinMode(trigPin,OUTPUT);
	pinMode(echoPin,INPUT);
	

	_trigPin = trigPin;
	_echoPin = echoPin;
}
long Ultrasoonsensor::Measure()
{
  digitalWrite(_trigPin, LOW); 
  delayMicroseconds(2); 
  digitalWrite(_trigPin, HIGH);

  delayMicroseconds(10);
  digitalWrite(_trigPin, LOW);
  _duration = pulseIn(_echoPin, HIGH);
  _distance = (_duration/2) / 29.1;
  return _distance;
}