#include <Motor.h>

#include <IRremote.h>

#include <Infraroodsensor.h>

#include <Ultrasoonsensor.h>
 
Motor m(9,7,8,4); 
Ultrasoonsensor f(A0,A1);
Ultrasoonsensor r(A2,A3);
Ultrasoonsensor l(11,12);
long forwarddistance;
long leftdistance;
long rightdistance;
long reversedistance;

boolean level1 = false;
boolean level2 = false;
boolean level3 = false;
boolean carStop = false;
    boolean gevonden = false;

int LDRpinLeft = A4;
int LDRpinRight = A5;
int LDRLeft = 0;
int LDRRight = 0;
int IRpin = 5;
IRrecv irrecv(IRpin);
decode_results results;

const int draaitijd = 0;

const int distanceF = 14;
const int distanceS = 7;

int LDRvalue = 0;

void setup() {
  Serial.begin(9600);
  irrecv.enableIRIn();
}

void loop() {
  // put your main code here, to run repeatedly:
  
forwarddistance = f.Measure();
rightdistance = r.Measure();
leftdistance = l.Measure();

if(irrecv.decode(&results))
  {
    Serial.println(results.value, DEC);
     
     if(results.value == 16738455)
      {
        level1 = true;
        level2 = false;
        carStop = false;
      }
      if(results.value == 16750695)
      {
        level1 = false;
        level2 = true;
        carStop = false;
      }
      
            if(results.value == 16756815)
      {
        level1 = false;
        level2 = false;
        level3 = true;
        gevonden = false;
        carStop = false;
      }
      
      if(results.value == 16712445)
      {
        carStop = true;
      }
      
      
      irrecv.resume();
  }
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
    else if (level3)
    {
      Level3();
    }
    
  }
  else
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

  m.TurnLeft(0);
  //MeasureLDR();
  /*Printonscreen("");
  if (forwarddistance <= distanceF)
  {
    m.Stop();
    
    if (forwarddistance <= distanceF && leftdistance <= distanceS && rightdistance <= distanceS)
    {
      m.Stop();
      Serial.println('STOP = 1e if');
    }
    
    else if (rightdistance > distanceS && leftdistance > distanceS)
    {
          if (leftdistance > rightdistance)
          {
            m.TurnLeft(draaitijd);
            
          }
          else if (rightdistance > leftdistance)
          {
            m.TurnRight(draaitijd);
          }
    }
    
    else if (rightdistance <= distanceS)
    {
      m.TurnLeft(draaitijd);
      Serial.println('Correctie naar links');
    }
    else if (leftdistance <= distanceS)
    {
      m.TurnRight(draaitijd);
      Serial.println('Correctie naar rechts');
    }
    
    else if (leftdistance == rightdistance)
    {
      m.TurnRight(draaitijd);
    }
    
    else
    {
      m.Stop();
    }
  }

  else if (rightdistance <= distanceS)
  {
    m.TurnLeft(draaitijd);
  }
  
  else if (leftdistance <= distanceS)
  {
    m.TurnRight(draaitijd);
  }
  
    else
  {
    m.Forward(draaitijd);
  }*/
  
}

void Level3()
{
  MeasureLDR();
  
  Printonscreen("");
  if (forwarddistance <= distanceF && gevonden == false)
  {
    m.Stop();
    
    if (forwarddistance <= distanceF && leftdistance <= distanceS && rightdistance <= distanceS)
    {
      m.Stop();
      Serial.println('STOP = 1e if');
    }
    
    else if (rightdistance > distanceS && leftdistance > distanceS)
    {
          if (leftdistance > rightdistance)
          {
            m.TurnLeft(draaitijd);
            
          }
          else if (rightdistance > leftdistance)
          {
            m.TurnRight(draaitijd);
          }
    }
    
    else if (rightdistance <= distanceS)
    {
      m.TurnLeft(draaitijd);
      Serial.println('Correctie naar links');
    }
    else if (leftdistance <= distanceS)
    {
      m.TurnRight(draaitijd);
      Serial.println('Correctie naar rechts');
    }
    
    else if (leftdistance == rightdistance)
    {
      m.TurnRight(draaitijd);
    }
    
    else
    {
      
      m.Stop();
    }
  }

  else if (rightdistance <= distanceS && gevonden == false)
  {
    m.TurnLeft(draaitijd);
  }
  
  else if (leftdistance <= distanceS && gevonden == false)
  {
    m.TurnRight(draaitijd);
  }
  
    else if (gevonden == false)
  {
    m.Forward(draaitijd);
    if (LDRRight < 100 && LDRLeft < 100)
    {
        if (LDRRight >= (LDRLeft + 10))
        {
          m.TurnRight(draaitijd);
          Serial.println("Draai naar rechts (rechts is groter)");
          Serial.println(LDRRight);
        }
        else if (LDRLeft >= (LDRRight + 10))
        {
          m.TurnLeft(draaitijd);
          Serial.println("Draai naar links (left is groter)");
          Serial.println(LDRLeft);
        }
        else
        {
          m.Forward(draaitijd);
          Serial.println("Rijd vooruit.");
          Serial.println(LDRRight);
          Serial.println(LDRLeft);
        }
    }
    else
    {
      gevonden = true;
      Serial.println("Gevonden!");
      Serial.println(LDRRight);
      Serial.println(LDRLeft);
      m.Stop();
    }
  }
  
  
  
  /*if (LDRRight < 150 && LDRLeft < 150)
  {
      if (LDRRight >= (LDRLeft + 10))
      {
        m.TurnRight(draaitijd);
        Serial.println("Draai naar rechts (rechts is groter)");
        Serial.println(LDRRight);
      }
      else if (LDRLeft >= (LDRRight + 10))
      {
        m.TurnLeft(draaitijd);
        Serial.println("Draai naar links (left is groter)");
        Serial.println(LDRLeft);
      }
      else
      {
        m.Forward(draaitijd);
        Serial.println("Rijd vooruit.");
        Serial.println(LDRRight);
        Serial.println(LDRLeft);
      }
  }
  else
  {
    Serial.println("Gevonden!");
    Serial.println(LDRRight);
    Serial.println(LDRLeft);
    m.TurnLeft(100);
    m.TurnRight(100);
    m.TurnLeft(100);
    m.TurnRight(100);
    m.TurnLeft(100);
    m.TurnRight(100);
  }*/
}
     
            


void MeasureLDR()
{
  LDRLeft = analogRead(LDRpinLeft);
  LDRRight = analogRead(LDRpinRight);
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
