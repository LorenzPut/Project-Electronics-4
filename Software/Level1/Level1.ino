#include <Motor.h>

#include <IRremote.h>

 
Motor m(9,7,8,4); 


int IRpin = 5;
IRrecv irrecv(IRpin);
decode_results results;


void setup() {
  Serial.begin(9600);
  irrecv.enableIRIn();
}

void loop() {
  // put your main code here, to run repeatedly:
if(irrecv.decode(&results))
  {
    Serial.println(results.value, DEC);
     if(results.value == 16736925)
      {
        Level1();
      }
      irrecv.resume();
  }
      
}

void Level1 ()
{
        m.TurnLeft(590);
        Serial.println("Ik draai");
        m.Stop();
        Serial.println("Ik stop");
        m.TurnLeft(590);
        m.Stop();
        m.Forward(1000);
        m.Stop();
        m.TurnRight(590);
        m.Stop();
        m.Forward(1000);
}
