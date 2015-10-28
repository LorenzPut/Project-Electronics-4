#include <Motor.h>

#include <IRremote.h>


Motor m(9,7,8,4);
int IRpin = 5;
IRrecv irrecv(IRpin);
decode_results results;
boolean manualcontrol = true;

void setup() {
  // put your setup code here, to run once:
    Serial.begin(9600);
      irrecv.enableIRIn();
}

void loop() {
  // put your main code here, to run repeatedly:
 ManualControl();
}

void ManualControl()
{
  //Serial.println("MANUAL CNTROL().");
  if(manualcontrol)
  {
    
    if(irrecv.decode(&results))
  {
    Serial.println(results.value, DEC);
     if(results.value == 16736925)
      {
        m.Forward(225);
      }
      else if(results.value == 16712445)
      {
        m.Stop();
      }  
      else if(results.value == 16761405)
      {
        m.TurnRight();
      }
      else if(results.value == 16720605)
      {
        m.TurnLeft();
      }
      else if(results.value == 16754775)
      {
        m.BackWards();
      }
    
    irrecv.resume(); 
  }
  }
  
}
