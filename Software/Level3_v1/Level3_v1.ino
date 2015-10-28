#include <Ultrasoonsensor.h>

#include <Motor.h>

#include <IRremote.h>
#include <IRremoteInt.h>

Motor m(9,7,8,4); 
Ultrasoonsensor f(A0,A1);
Ultrasoonsensor l(A2,A3);
Ultrasoonsensor r(11,12);
long forwarddistance;
long leftdistance;
long rightdistance;
long reversedistance;

boolean level1 = false;
boolean level2 = false;
boolean level3 = false;

int IRpin = 5;
IRrecv irrecv(IRpin);
decode_results results;

int draaitijd = 500;



void setup() {
  // put your setup code here, to run once:
  
}

void loop() {
  // put your main code here, to run repeatedly:
  
}

void Level3(boolean level)
{
  if(level)
  {
    if(forwarddistance < 5)
    {
      if(leftdistance > 5)
      {
        m.TurnRight();
        Printonscreen("Naar rechts draaien");
      }
    }
  }
}
