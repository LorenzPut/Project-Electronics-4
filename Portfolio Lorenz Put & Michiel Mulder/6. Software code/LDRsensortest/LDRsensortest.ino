int ldrpin = A5;
int ldrvalue = 0;

void setup()
{
  Serial.begin(9600);
  pinMode(ldrpin, INPUT);

}

void loop()
{
    ldrvalue = analogRead(ldrpin);
    Serial.print("LDR value : ");
    Serial.println(ldrvalue);
    delay(100);
}
