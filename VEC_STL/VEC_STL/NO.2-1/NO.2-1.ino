//COM30
#include <Adafruit_NeoPixel.h>
#include <SoftwareSerial.h>
#define nleds 2
#define pleds 10 
Adafruit_NeoPixel leds=Adafruit_NeoPixel(nleds,pleds,NEO_RGB
+NEO_KHZ800);
SoftwareSerial _s1(13,12,false,4096);
uint32_t _red = leds.Color(0,255,0);
uint32_t _off = leds.Color(0,0,0);
String COMCMD;
bool _toggle0=false;
bool _toggle1=false;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  _s1.begin(115200);
  leds.begin();
  leds.setPixelColor(0,_off);
  leds.setPixelColor(0,_off);
  leds.show();
  leds.setPixelColor(0,_off);
  leds.setPixelColor(0,_off);
  leds.show();
  delay(10);
}
void drive_led(bool toggle,uint32_t _color,byte ch)
{
  if(toggle==true){
    leds.setPixelColor(ch,_color);
    delay(10);
    leds.show();
    toggle==false;
     
  }else {
    leds.setPixelColor(ch,_off);
    delay(10);
    leds.show();
  }
}  
void loop() {
  
if(_s1.available()>0)
  {
    COMCMD =_s1.readString();
    _s1.flush();
    Serial.println();
    
   //_s1.println(COMCMD);
    
  }
  
  if(COMCMD.indexOf("B1")!=-1)
  {
   Serial.println(COMCMD);
   _toggle0=!_toggle0;
   drive_led(_toggle0,_red,0);
   COMCMD.remove(0);
    
  }else if(COMCMD.indexOf("B2")!=-1)
  {
    Serial.println(COMCMD);
    _toggle1=!_toggle1;
    drive_led(_toggle1,_red,1);
    COMCMD.remove(0);
  }else if(COMCMD.indexOf("B3")!=-1)
  {
    Serial.println(COMCMD);
    analogWrite(D8,512);
    delay(500);
    analogWrite(D8,0);
    COMCMD.remove(0);
  }
}
