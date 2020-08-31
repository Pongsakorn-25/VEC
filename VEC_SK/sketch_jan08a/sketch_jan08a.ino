#include <Psx.h>
#define dataPin 8 
#define cmdPin 9  
#define clkPin 10
#define attPin 11
Psx Psx;
unsigned int data = 0;

void setup() {
Psx.setupPins(dataPin,cmdPin,attPin,clkPin,10);
Serial.begin(9600);
}

void loop() {
  data = Psx.read();

    Serial.println(data);
}  

