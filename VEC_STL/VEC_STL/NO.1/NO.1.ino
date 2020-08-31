#include <Wire.h>                   
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#include <Adafruit_NeoPixel.h>
#define nleds 2
#define pleds 10 
#define OLED_RESET -1

//com3
Adafruit_SSD1306 OLED(OLED_RESET);
Adafruit_NeoPixel leds=Adafruit_NeoPixel(nleds,pleds,NEO_RGB
+NEO_KHZ800);
uint8_t _SL=0;
bool _ledtoggled =false ;
uint8_t _SW1 =D5;
uint8_t _SW2 =D6;
uint32_t _off = leds.Color(0,0,0);
uint32_t _green = leds.Color(255,0,0);
uint32_t _red = leds.Color(0,255,0);
uint32_t _blue = leds.Color(0,0,255);
uint32_t _white = leds.Color(255,255,255);
uint32_t _yellow = leds.Color(255,255,0);
long color[] ={_red,_green,_blue,_yellow,_white,_off};
byte ch=0;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Wire.begin();
  OLED.begin(SSD1306_SWITCHCAPVCC, 0x3C); 
  delay(10);
  OLED.clearDisplay();
  leds.begin();
  leds.setPixelColor(0,0);
  leds.show();
  /*OLED.setTextColor(WHITE);
  OLED.setCursor(0,0);
  OLED.setTextSize(2)*/;
  OLED.display();
  
  pinMode(_SW1,INPUT);
  pinMode(_SW2,INPUT);
  
}
void CC (byte c)
{
  OLED.clearDisplay();
  OLED.setCursor(40,0);
  OLED.setTextSize(2);
  OLED.println("Color");
  OLED.setTextColor(WHITE);
  
  
  OLED.setCursor(20,30);
  OLED.setTextSize(3);
  //OLED.println("Color");
  OLED.setTextColor(WHITE);
  //OLED.setTextSize(2);
  switch(c){
    case 0: Serial.println("RED");
            OLED.println("RED");
            drive_led(_ledtoggled,color[0],ch);
            break;
    case 1: Serial.println("GREEN");
            OLED.println("GREEN");
            drive_led(_ledtoggled,color[1],ch);
           break;
    case 2: Serial.println("BLUE");
            OLED.println("BLUE");
            drive_led(_ledtoggled,color[2],ch);
           break;
    case 3: Serial.println("YELLOW");
            OLED.println("YELLOW");
            drive_led(_ledtoggled,color[3],ch);
           break;
    case 4: Serial.println("WHITE");
            OLED.println("WHITE");
            drive_led(_ledtoggled,color[4],ch);
           break; 
    case 5: Serial.println("OFF");
            OLED.println("OFF");
            drive_led(_ledtoggled,color[5],ch);
           break; 
    default:break;      
    }
}
void drive_led(bool toggle,uint32_t _color,byte ch)
{
  if(toggle==true){
    leds.setPixelColor(ch,_color);
    delay(10);
    leds.show();
    toggle==false;
    _ledtoggled=false; 
  }else {
    return;
  }
}
void loop() {
  // put your main code here, to run repeatedly:
  int a =analogRead(A0);
  _SL=map(a,0,1024,0,5);
  CC(_SL);
  if(!digitalRead(_SW1)==1)
  {
    delay(10);
    while(!digitalRead(_SW1)==1){delay(0);};
    delay(10);
    _ledtoggled = true;
    ch=0;
  }
  if(!digitalRead(_SW2)==1)
  {
    delay(10);
    while(!digitalRead(_SW2)==1){delay(0);};
    delay(10);
    _ledtoggled = true;
    ch=1;
  }
  OLED.display();
}
