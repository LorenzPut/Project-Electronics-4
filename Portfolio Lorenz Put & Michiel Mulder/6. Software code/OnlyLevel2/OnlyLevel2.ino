#include <Motor.h>


#include <IRremote.h>


#include <Ultrasoonsensor.h>
 
Motor m(4,5,6,7); 
Ultrasoonsensor f(A0,A1);
Ultrasoonsensor r(A2,A3);
Ultrasoonsensor l(11,12);
long forwarddistance;
long leftdistance;
long rightdistance;
long reversedistance;

const int draaitijd = 0;

const int distanceF = 14;
const int distanceS = 7;

void setup() {
  // put your setup code here, to run once:
    Serial.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:
  
  forwarddistance = f.Measure();
  rightdistance = r.Measure();
  leftdistance = l.Measure();
  
  Level2();
}
void Level2()
{
  
  Printonscreen("");
if(forwarddistance <= distanceF)
      {
        m.Stop();
        if(leftdistance > distanceS || rightdistance > distanceS)
        {
        
          if(leftdistance > rightdistance)
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
        }
       
           else
           {
             m.Stop();
             digitalWrite(13, HIGH);
             Printonscreen("Ik zit vast");
           }
       }
       
       
       else if(leftdistance < distanceS)
       {
         m.TurnRight(20);
         Printonscreen("Ik stuur bij naar rechts");
       }
       else if(rightdistance < distanceS)
       {
         m.TurnLeft(20);
         Printonscreen("Ik stuur bij naar links");
       }
        
       else
       {
         m.Forward(draaitijd);
         Printonscreen("Ik rijd vooruit");
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
