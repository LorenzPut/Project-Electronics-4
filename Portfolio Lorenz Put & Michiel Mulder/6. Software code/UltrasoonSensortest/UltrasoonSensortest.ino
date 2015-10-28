#include <Ultrasoonsensor.h>

Ultrasoonsensor s(A0,A1);
Ultrasoonsensor d(A2,A3);
Ultrasoonsensor f(12,11);
int afstand = 0;
int afstandd = 0;
int afstandf = 0;
void setup()
{
  Serial.begin(9600);
}
void loop()
{
  afstand = s.Measure();
  afstandd = d.Measure();
  afstandf = f.Measure();
  
  Serial.println(afstand);
  Serial.println(afstandd);
  Serial.println(afstandf);
}


