#include <IRremote.h>
#include <IRremoteInt.h>

int RECV_PIN = 2;

IRrecv irrecv(RECV_PIN);

decode_results results;

void setup()
{
  Serial.begin(9600);
  attachInterrupt(0,CHECK_IR,CHANGE);
  irrecv.enableIRIn(); // Start the receiver

}

void loop() {
 delay(500);
}

void CHECK_IR(){
  while(irrecv.decode(&results)){
  Serial.println(results.value, HEX);
  irrecv.resume();
  }
}
