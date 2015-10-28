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
boolean level3 = false;
boolean carStop = false;

int LDRpin = A5;
int IRpin = 5;
IRrecv irrecv(IRpin);
decode_results results;

const int draaitijd = 500;

const int distanceF = 10;
const int distanceS = 7;

int LDRvalue = 0;

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
     
//     Level 1 afspelen
     if(results.value == 16738455)
      {
        level1 = true;
        level2 = false;
        carStop = false;
      }
      
//      Level 2 afspelen
      if(results.value == 16750695)
      {
        level1 = false;
        level2 = true;
        carStop = false;
      }
      
//      Level 3 afspelen
      if(results.value == 16756815)
      {
        level1 = false;
        level2 = false;
        level3 = true;
        carStop = false;
      }
      
//      Stoppen
      if(results.value == 16712445)
      {
        level1 = false;
        level2 = false;
        level3 = false;
        carStop = true;
        
      }
      
      
      irrecv.resume();
  }
  
  // LEVEL AANROEP
  if(!carStop)
  {
    if(level1)
    {
      Level1();
    }
    else if (level2)
    {
      Level2();
    }
  }
  else
  {
    m.Stop();
  }
}

void Level1 ()
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

void Level2()
{


    if(forwarddistance < distanceF)
      {
        m.Stop();
        if(leftdistance > distanceS || rightdistance > distanceS)
        {
        
          if(leftdistance > rightdistance  )
          {
            
              m.TurnLeft(0);
              Printonscreen("Ik draai 90 graden naar links");
          }
          
          else if(rightdistance > leftdistance)
          {
              m.TurnRight(0);
              Printonscreen("Ik draai 90 graden naar rechts");
          }
          
          else if (rightdistance == leftdistance)
          {
            m.TurnLeft(0);
            Printonscreen("Ik draai 90 graden naar links");
          }
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
       
       
       else if(leftdistance < distanceS)
       {
         m.TurnRight(0);
         Printonscreen("Ik stuur bij naar rechts");
       }
       else if(rightdistance < distanceS)
       {
         m.TurnLeft(0);
         Printonscreen("Ik stuur bij naar links");
       }
        
       else
       {
         m.Forward(0);
         Printonscreen("Ik rijd vooruit");
       }
    }

void Level3()
{
  MeasureLDR();
  Printonscreen("");
  if(LDRvalue < 600)
  {
    Level2();
  }
       else
    {
      m.Stop();
      m.TurnLeft(5000);
    } 
}

void MeasureLDR()
{
  LDRvalue = analogRead(LDRpin);
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
  
  Serial.print("LDRwaarde : ");
  Serial.println(LDRvalue);
  
}
