#ifndef Ultrasoonsensor_h
#define Ultrasoonsensor_h

#include "Arduino.h"

class Ultrasoonsensor
{
	public:
		Ultrasoonsensor(int trigPin, int echoPin);
		long Measure();
	private:
		int _echoPin;
		int _trigPin;
		long _duration;
		long _distance;


};
#endif