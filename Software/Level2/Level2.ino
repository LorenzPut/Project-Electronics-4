#include <Motor.h>

#include <IRremote.h>

#include <Infraroodsensor.h>

#include <Ultrasoonsensor.h>
 
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

int IRpin = 5;
IRrecv irrecv(IRpin);
decode_results results;

int draaitijd = 500;


void setup() {
  Serial.begin(9600);
  irrecv.enableIRIn();
}

void loop() {
  // put your main code here, to run repeatedly:
  
forwarddistance = f.Measure();
leftdistance = l.Measure();
rightdistance = r.Measure();

if(irrecv.decode(&results))
  {
    Serial.println(results.value, DEC);
     if(results.value == 16738455)
      {
        Level1();
        level1 = true;
        level2 = false;
      }
      if(results.value == 16750695)
      {
        Level2();
        level1 = false;
        level2 = true;
      }
      
      irrecv.resume();
  
  }
  
  Level1(level1);
  
  Level2(level2);

      
}

void Level1 (boolean level)
{
  if(level)
  {  
        m.TurnLeft(draaitijd);
        Serial.println("Ik draai");
        m.Stop();
        Serial.println("Ik stop");
        m.TurnLeft(draaitijd);
        m.Stop();
        m.Forward(1000);
        m.Stop();
        m.TurnRight(draaitijd);
        m.Stop();
        m.Forward(1000);
   }
}
void Level2(boolean level)
{
  if(level)
  {
    if(forwarddistance < 5)
    {
      m.Stop();
      if(leftdistance > 5 || rightdistance > 5)
      {
      
        if(leftdistance > rightdistance )
        {
          m.TurnLeft(draaitijd);
         Printonscreen("Ik draai 90 graden naar links");
        }
        else if(rightdistance > leftdistance)
        {
          m.TurnRight(draaitijd);
          Printonscreen("Ik draai 90 graden naar rechts");
        }
        else if (rightdistance == leftdistance)
        {
          m.TurnLeft(draaitijd);
          Printonscreen("Ik draai 90 graden naar links");
        }
      /*else if(backwarddistance > 5)
      {
           m.BackWards(1500);       
           Printonscreen("Ik rijd achteruit voor een halve meterr");
           //delay(2000);
           if(leftdistance > rightdistance )
           {
            m.TurnLeft(draaitijd);
            Printonscreen("Ik draai 90 graden naar links");
           }
           else if(rightdistance  >  leftdistance)
           {
            m.TurnRight(draaitijd);
            Printonscreen("Ik draai 90 graden naar rechts");
           } 
              
         }*/
         else
         {
           m.Stop();
           digitalWrite(13, HIGH);
           Printonscreen("Ik zit vast");
         }
      }
     }
     else if(leftdistance < 5)
     {
       m.TurnRight(295);
       Printonscreen("Ik stuur bij naar rechts");
     }
     else if(rightdistance < 5)
     {
       m.TurnLeft(295);
       Printonscreen("Ik stuur bij naar links");
     }
      
     else
     {
       m.Forward(0);
       Printonscreen("Ik rijd vooruit");
     }   
      
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
