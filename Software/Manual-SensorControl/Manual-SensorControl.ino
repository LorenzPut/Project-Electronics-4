#include <Ultrasoonsensor.h>

#include <Infraroodsensor.h>

#include <Motor.h>

#include <IRremote.h>


Motor m(9,7,8,4);
Ultrasoonsensor f(A0,A1);
Ultrasoonsensor l(A2,A3);
Ultrasoonsensor r(11,12);
Infraroodsensor i(A5);
int IRpin = 2;
//volatile int state = RISING;

IRrecv irrecv(IRpin);
decode_results results;
long forwarddistance;
long leftdistance;
long rightdistance;
long reversedistance;

int draaitijd = 900;

//KEUZE LEVEL BOOLEANS
boolean level1 = false;
boolean level2 = false;
boolean level3 = false;
boolean manualcontrol = false;


void setup() {
  // put your setup code here, to run once:
    Serial.begin(9600);
      irrecv.enableIRIn();
      attachInterrupt(0, InterruptTest, CHANGE);
}

void loop() {
  // put your main code here, to run repeatedly:
  
}


void InterruptTest()
{
  ChooseLevel();
  
  if(manualcontrol){
    ManualControl();
  }
  
  else if(!manualcontrol)
  {
//    forwarddistance = f.Measure();
//    leftdistance = l.Measure();
//    rightdistance = r.Measure();
//    reversedistance = i.Calculate();
    
    if(level1)
    {
      Level1();
    }
  }
}

void ManualControl()
{
  //Serial.println("MANUAL CNTROL().");
    if(irrecv.decode(&results))
  {
    Serial.println(results.value, DEC);
     if(results.value == 16736925)
      {
        m.Forward(0);
      }
      else if(results.value == 16712445)
      {
        m.Stop();
      }  
      else if(results.value == 16761405)
      {
        m.TurnRight(0);
      }
      else if(results.value == 16720605)
      {
        m.TurnLeft(0);
      }
      else if(results.value == 16754775)
      {
        m.BackWards(0);
      }
    
    irrecv.resume(); 
  }
}

void ChooseLevel()
{
   if(irrecv.decode(&results))
   {
     Serial.println(results.value, DEC);
     if(results.value == 16730805)
     {
       //CHOOSE MANUAL CONTROLS
       //ManualControl();
       manualcontrol = true;
       level1 = false;
       level2 = false;
       level3 = false;
     }
     
     //CHOOSE LEVEL 1
     if(results.value == 16738455)
     {
       ManualControl();
       manualcontrol = false;
       level1 = true;
       level2 = false;
       level3 = false;
     }
     
     //CHOOSE LEVEL 2
     if(results.value == 16750695)
     {
       ManualControl();
       manualcontrol = false;
       level1 = false;
       level2 = true;
       level3 = false;
     }
     
     //CHOOSE LEVEL 3
     if(results.value == 16756815)
     {
       ManualControl();
       manualcontrol = false;
       level1 = false;
       level2 = false;
       level3 = true;
     }
     
     irrecv.resume();
   }
}

   void Printonscreen(String message)
   {
     Serial.println(message);
     Serial.print("Afstand voorruit : ");
     Serial.print(forwarddistance);
     Serial.println(" cm");
     
     Serial.print("Afstand links : ");
     Serial.print(leftdistance);
     Serial.println(" cm");
     
     Serial.print("Afstand rechts : ");
     Serial.print(rightdistance);
     Serial.println(" cm");
   }
   
   void Level1 ()
   {
     if(irrecv.decode(&results))
     {
       Serial.println(results.value, DEC);
       if(results.value == 16712445)
       {
         m.Stop();
       }
       m.TurnLeft(draaitijd);
       m.Forward(5000);
       m.TurnRight(draaitijd);
       m.Forward(5000);
     }
   }
