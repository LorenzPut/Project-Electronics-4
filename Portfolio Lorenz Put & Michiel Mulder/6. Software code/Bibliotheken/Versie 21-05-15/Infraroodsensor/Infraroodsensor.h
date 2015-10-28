#ifndef Infraroodsensor_h
#define Infraroodsensor_h

#include "Arduino.h"

class Infraroodsensor
{
	public://constructor
		Infraroodsensor(int distpin);
		void ReadVoltage();
		int Calculate();

	private://Declareeren van alle gebruikte variabelen.
		int _distpin;
		int _read;
		double _volt;
		int _distance;

};
#endif