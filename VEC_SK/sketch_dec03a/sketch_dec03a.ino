#include <IRremote.h>

int lacth = 8;
int clockp = 12;
int datap = 11;
int RECV_PIN = 3;
unsigned long last = millis();
int on = 0;
int j =0x00;
IRrecv irrecv(RECV_PIN);

decode_results results;
void setup() {
Serial.begin(115200);
while(!Serial)
{
  ;
}
irrecv.enableIRIn();
pinMode(lacth,OUTPUT);
pinMode(clockp,OUTPUT);
pinMode(datap,OUTPUT);
digitalWrite(lacth,HIGH);
delay(1000);
digitalWrite(lacth,LOW);
shiftOut(datap,clockp,MSBFIRST,j);
digitalWrite(lacth,HIGH);
}

void DATAOUT(byte data)
{
  digitalWrite(lacth,LOW);
  shiftOut(datap,clockp,MSBFIRST,data);
  digitalWrite(lacth,HIGH);
}

void loop() {
if (irrecv.decode(&results)) {
    // If it's been at least 1/4 second since the last
    // IR received, toggle the relay
    if (millis() - last > 250) {
      on = !on;
      //digitalWrite(RELAY_PIN, on ? HIGH : LOW);
      //digitalWrite(13, on ? HIGH : LOW);
      Serial.println(results.value, HEX);
      
      j<<=1;
      if(j==0)
      {
        j=0x01;
      }
      if(j>0x80)
      {
        j=0x00;
      }
      DATAOUT(j);
      
    }
    last = millis();      
    irrecv.resume(); // Receive the next value
  }
}
