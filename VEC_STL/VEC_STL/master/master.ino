#include <SoftwareSerial.h>
#include <Adafruit_NeoPixel.h>
#define nleds 2
#define pleds 10 
Adafruit_NeoPixel leds=Adafruit_NeoPixel(nleds,pleds,NEO_RGB
+NEO_KHZ800);
//com29
SoftwareSerial _s1(14,12,false,4096);
void setup() {
  // put your setup code here, to run once:
  _s1.begin(115200);
  Serial.begin(115200);
  delay(10);
  _s1.print("Hello world");
  pinMode(D1,INPUT);
  leds.begin();
  leds.setPixelColor(0,0);
  leds.show();
}

void loop() {
  // put your main code here, to run repeatedly:
  if(!digitalRead(D1)==HIGH)
  {
    delay(10);
    while(!digitalRead(D1)==HIGH){delay(0);};
    delay(10);
    _s1.println('1');
    Serial.println('1');
    //while(!_s1.available()>0){delay(0);};
    yield();
  }
}
