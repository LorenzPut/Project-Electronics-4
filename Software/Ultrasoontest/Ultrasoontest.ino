#include <Ultrasoonsensor.h>

Ultrasoonsensor s(A2,A3);
int afstand = 0;
void setup()
{
  Serial.begin(9600);
}
void loop()
{
  afstand = s.Measure();
  Serial.println(afstand);
  
}


