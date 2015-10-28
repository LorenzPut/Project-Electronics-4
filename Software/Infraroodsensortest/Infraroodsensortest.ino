#include <Infraroodsensor.h>

Infraroodsensor i(9);
int afstand;
void setup()
{
  Serial.begin(9600);
}
void loop()
{
  afstand  = i.Calculate();
  Serial.println(afstand);
}
