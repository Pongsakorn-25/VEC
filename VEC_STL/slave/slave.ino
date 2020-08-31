#include <Wire.h>                   
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <SoftwareSerial.h>
#include <Adafruit_NeoPixel.h>
#define nleds 2
#define pleds 10 
#define OLED_RESET -1

//com3
Adafruit_SSD1306 OLED(OLED_RESET);
Adafruit_NeoPixel leds=Adafruit_NeoPixel(nleds,pleds,NEO_RGB
+NEO_KHZ800);
SoftwareSerial _s2(14,12,false,4096);
uint32_t _off = leds.Color(0,0,0);
uint32_t _red = leds.Color(255,0,0);
uint32_t _green = leds.Color(0,255,0);
uint32_t _blue = leds.Color(0,0,255);
uint64_t color[] ={_off,_green,_red,_blue};
byte c=0;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  _s2.begin(115200);
  Wire.begin();
  OLED.begin(SSD1306_SWITCHCAPVCC, 0x3C); 
  delay(10);
  OLED.clearDisplay();
  leds.begin();
  leds.setPixelColor(0,color[0]);
  leds.show();
  OLED.setTextColor(WHITE);
  OLED.setCursor(0,0);
  OLED.setTextSize(2);
  CC(c);
  OLED.display();
  
}
void CC (byte c)
{
  OLED.clearDisplay();
  OLED.setCursor(0,0);
  OLED.setTextColor(WHITE);
  OLED.setTextSize(2);
  switch(c){
    case 0: Serial.println("off");
            OLED.println("off");
           break;
    case 1: Serial.println("red");
            OLED.println("red");
           break;
    case 2: Serial.println("green");
            OLED.println("green");
           break;
    case 3: Serial.println("blue");
            OLED.println("blue");
           break; 
    default:break;      
    }
}
void loop() {
  // put your main code here, to run repeatedly:
  if(_s2.available()>0){
    String x =_s2.readString();
    //x.remove
    //x.remove(0,1);
    yield();
    //Serial.print(x);
    c++;
    if(c>3)c=0;
    CC(c);
    leds.setPixelColor(0,color[c]);
    leds.show();
    OLED.display();
    //_s2.write('0');
  }
}
