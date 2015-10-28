#ifndef Motor_h
#define Motor_h

#include "Arduino.h"

class Motor
{
	public:
		Motor(int leftOne, int leftTwo, int rightOne, int rightTwo);
		void Forward(int delaytime);
		void TurnLeft(int delaytime);
		void TurnRight(int delaytime);
		void BackWards(int delaytime);
		void Stop();
		

	private:
		int _leftOne;
		int _leftTwo;
		int _rightOne;
		int _rightTwo;
};
#endif