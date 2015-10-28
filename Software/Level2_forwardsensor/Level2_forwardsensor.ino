#include <Motor.h>

#include <IRremote.h>

#include <Infraroodsensor.h>

#include <Ultrasoonsensor.h>
 
Motor m(9,7,8,4); 
Ultrasoonsensor f(A0,A1);
//Ultrasoonsensor l(A2,A3);
//Ultrasoonsensor r(11,12);
long forwarddistance;
long leftdistance;
long rightdistance;
long reversedistance;

boolean level1 = false;
boolean level2 = false;
boolean brake = false;

int IRpin = 5;
IRrecv irrecv(IRpin);
decode_results results;

int draaitijd = 590;


void setup() {
  Serial.begin(9600);
  irrecv.enableIRIn();
}

void loop() {
  // put your main code here, to run repeatedly:
  
forwarddistance = f.Measure();
//leftdistance = l.Measure();
//rightdistance = r.Measure();

if(irrecv.decode(&results))
  {
    Serial.println(results.value, DEC);
     if(results.value == 16738455)
      {
        Level1();
        level1 = true;
        level2 = false;
        brake = false;
      }
      if(results.value == 16750695)
      {
        level1 = false;
        level2 = true;
        brake = false;
      }
      if(results.value = 16712445)
      {
        brake = true;
      }
      
      irrecv.resume();
  }
  if(level1)
  {
    Level1();
  }
  else if (level2)
  {
    Level2();
  }
  else if (brake)
  {
    m.Stop();
  }
      
}

void Level1 ()
{
  if(level1)
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
void Level2()
{
  if(level2)
  {
    if(forwarddistance < 5)
    {
      
      m.Stop();
      Printonscreen("Ik ben gestopt");

    }
    else        
    {
      m.Forward(0);
      Printonscreen("Ik rij voorruit");

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
