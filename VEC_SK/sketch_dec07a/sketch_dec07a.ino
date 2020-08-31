#include <SoftwareSerial.h>
#include <Wire.h>                   // Include library
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#define OLED_RESET -1
Adafruit_SSD1306 OLED(OLED_RESET);
SoftwareSerial myNode(14,12,false,4096); 
String COMCMD="" ;
void setup() {
Serial.begin(115200);

while(!Serial)
{
  ;
}
myNode.begin(115200);
OLED.begin(SSD1306_SWITCHCAPVCC, 0x3C); 
Serial.println("");
}
void displayOLED(String MSG)
{
  OLED.clearDisplay();               //Clear display
  OLED.setTextColor(WHITE);          //Set text color
  OLED.setCursor(35,0);               //Set display start position
  OLED.setTextSize(2);               //Set text size x1
  OLED.println("VALUE");          //Type message
  OLED.setCursor(40,35);             //Set display postion
  OLED.setTextSize(2);               //Set text size x2 
  OLED.println( String(MSG));  // Show result value
  OLED.display();                 
}
void loop() {
  if(myNode.available()>0)
  {
      COMCMD = myNode.readString();
      //int z = map(x,0,255,0,4095);
      // Serial.println(String(x));
      //z=0;
      //x="";
  }
  if(COMCMD == "S")
  {
    analogWrite(D8,255);
    delay(500);
    analogWrite(D8,0);
    COMCMD ="";
    return;
  }else  if(COMCMD == "D")
  {
   COMCMD=(String)analogRead(A0);
   displayOLED(COMCMD);
   Serial.println(COMCMD);
   COMCMD ="";
   return;
  }else if(COMCMD!=""){
    displayOLED(COMCMD);
    Serial.println(COMCMD);
    COMCMD ="";
  }
}
