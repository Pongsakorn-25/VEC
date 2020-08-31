#include <IRremote.h>

int rev_pin = 3;
IRrecv irrecv(rev_pin);
decode_results results;
void setup() {
  Serial.begin(115200);
  irrecv.enableIRIn();
  
}

void loop() {  
  if(irrecv.decode(&results))
  {
     Serial.println(results.value);
     irrecv.resume();
  }
}
