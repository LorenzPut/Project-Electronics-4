#include "Arduino.h"
#include "Infraroodsensor.h"

Infraroodsensor::Infraroodsensor(int distpin)
{
	pinMode(distpin,INPUT);

}

int Infraroodsensor::Calculate()
{
	_read = (analogRead(_distpin));
	  //De bekomen waarde wordt geconverteerd naar volt.
	_volt = (_read)*(5.0/1023.0);
	_distance = ((-3.21118*(pow(_volt,5)))+(30.287*pow(_volt,4))-(111.22*pow(_volt,3))+(200.92*pow(_volt,2))-(185.9*_volt)+81.847);
	return _distance;

}
