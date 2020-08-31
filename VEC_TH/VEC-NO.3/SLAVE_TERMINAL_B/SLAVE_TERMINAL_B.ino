#include <Wire.h>
#include <Wire.h>                   // Include library
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <SoftwareSerial.h>

#define OLED_RESET -1

Adafruit_SSD1306 OLED(OLED_RESET);

SoftwareSerial myNode(13,12,false,4096);  

String COMCMD;
int COMINT;

void displayOLED(String MSG)
{
  OLED.clearDisplay();               //Clear display
  OLED.setTextColor(WHITE);          //Set text color
  OLED.setCursor(15,20);               //Set display start position
  OLED.setTextSize(3);               //Set text size x1
  OLED.println( String(MSG));  // Show result value
  OLED.display();                 
}


void setup() {
 Wire.begin();
 OLED.begin(SSD1306_SWITCHCAPVCC, 0x3C); 
 myNode.begin(115200);
 
 delay(10);
 Serial.begin(115200);
 Serial.println("");
 OLED.clearDisplay();
 OLED.setTextColor(WHITE);          //Set text color
 OLED.setCursor(10,20);               //Set display start position
 OLED.setTextSize(3);       
 OLED.println("NODE#2");  
 OLED.display();
}

void loop() {
  if(myNode.available()>0)
  {
    COMCMD =myNode.readString();
    myNode.flush();
    Serial.println();
  }
  /*if(COMCMD.indexOf("A")!=-1)
  {
    
    COMCMD.remove(0,1);
    COMINT=COMCMD.toInt();
    COMINT=COMINT*2;
    COMCMD =String(COMINT);
    Serial.println(COMCMD);
    displayOLED(COMCMD);
    COMCMD = "";
    COMINT = 0;
  }*/
  if(COMCMD.indexOf("B")!=-1)
  {
    
    COMCMD.remove(0,1);
    COMINT=COMCMD.toInt();
    COMINT=COMINT*2;
    COMCMD =String(COMINT);
    Serial.println(COMCMD);
    displayOLED(COMCMD);
    COMCMD = "";
    COMINT = 0;
  }
  /*if(COMCMD.indexOf("C")!=-1)
  {
    
    COMCMD.remove(0,1);
    COMINT=COMCMD.toInt();
    COMINT=COMINT*2;
    COMCMD =String(COMINT);
    Serial.println(COMCMD);
    displayOLED(COMCMD);
    COMCMD = "";
    COMINT = 0;
  }*/
}
