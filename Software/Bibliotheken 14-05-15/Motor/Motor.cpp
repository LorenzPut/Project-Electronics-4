#include "Arduino.h"
#include "Motor.h"

Motor::Motor(int leftOne, int leftTwo, int rightOne, int rightTwo)
{
	pinMode(leftOne,OUTPUT);
	pinMode(leftTwo,OUTPUT);
	pinMode(rightOne,OUTPUT);
	pinMode(rightTwo,OUTPUT);

	_leftOne = leftOne;
	_leftTwo = leftTwo;
	_rightOne = rightOne;
	_rightTwo = rightTwo;

}

void Motor::Forward(int delaytime)
{
	digitalWrite(_leftOne, HIGH);
	digitalWrite(_leftTwo, LOW);
	digitalWrite(_rightOne, HIGH);
	digitalWrite(_rightTwo, LOW);
	delay(delaytime);
}
void Motor::TurnLeft(int delaytime)
{
	digitalWrite(_leftOne, LOW);
	digitalWrite(_leftTwo, HIGH);
	digitalWrite(_rightOne, HIGH);
	digitalWrite(_rightTwo, LOW);
		delay(delaytime);

	
}
void Motor::TurnRight(int delaytime)
{
	digitalWrite(_leftOne, HIGH);
	digitalWrite(_leftTwo, LOW);
	digitalWrite(_rightOne, LOW);
	digitalWrite(_rightTwo, HIGH);
	delay(delaytime);

}
void Motor::BackWards(int delaytime)
{
	digitalWrite(_leftOne, LOW);
	digitalWrite(_leftTwo, HIGH);
	digitalWrite(_rightOne, LOW);
	digitalWrite(_rightTwo, HIGH);
	delay(delaytime);
}
void Motor::Stop()
{
	digitalWrite(_leftOne, HIGH);
	digitalWrite(_leftTwo, HIGH);
	digitalWrite(_rightOne, HIGH);
	digitalWrite(_rightTwo, HIGH);
}
