#include "DHT.h"                    //Include DHT library
#include <Wire.h>                   // Include library
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#define OLED_RESET -1

Adafruit_SSD1306 display(OLED_RESET);

#define DHTTYPE DHT11
#define DHTPIN  D7
DHT dht (DHTPIN, DHTTYPE, 15);
int _l;
int _h;
int _t;
int BAR1; 
int BAR2; 
int BAR3;
int address = 0x23;
bool disbar;
void displaybar(){
  
  BAR1 = map(_l,0,10000,0,100);
  BAR2 = map(_h,0,100,0,100);
  BAR3 = map(_t,0,40,0,100);
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(WHITE);          //Set text color
  display.setCursor(5,5);               //Set display start position
  display.println("L");  
  display.setCursor(5,25);               //Set display start position
  display.println("H");
  display.setCursor(5,45);               //Set display start position
  display.println("T");
  display.fillRect(30,5, BAR1,14, WHITE); //Draws the bar depending on the sensor value
  display.fillRect(30,25, BAR2,14, WHITE); 
  display.fillRect(30,45, BAR3,14, WHITE); 
  display.display();
}
void displayOLED(){
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(WHITE);          //Set text color
  display.setCursor(5,5);               //Set display start position
  display.println("L");  
  display.setCursor(5,25);               //Set display start position
  display.println("H");
  display.setCursor(5,45);               //Set display start position
  display.println("T");

  display.setCursor(30,5);               //Set display start position
  display.println(_l);  
  display.setCursor(30,25);               //Set display start position
  display.println(_h);
  display.setCursor(30,45);               //Set display start position
  display.println(_t);



  
 // display.fillRect(30,5, 19,14, WHITE); //Draws the bar depending on the sensor value
 // display.fillRect(30,25, 19,14, WHITE); 
 // display.fillRect(30,45, 19,14, WHITE); 
  display.display();
}
void DHT11read()
{
  _h = dht.readHumidity();
  _t = dht.readTemperature();
}
void BH1750read()
{
  int i = 0;
  byte buff[2];
  Wire.beginTransmission(address);
  Wire.requestFrom(address, 2);
  while (Wire.available())
  {
    buff[i] = Wire.read();                // Read one byte
    i++;
  }
  Wire.endTransmission();
  if (i== 2)    // Read and check data from BH1750
  {
    _l = ((buff[0] << 8) | buff[1]) / 1.2;
  }else{
    return;  }
}
void setup() {
 
  Wire.begin();
  pinMode(D3,INPUT);
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3D (for the 128x64)
  // init done
  display.display();
  delay(2000);

  // Clear the buffer.
  display.clearDisplay();
  Wire.beginTransmission(address);
  Wire.write(0x10);                       // Start operation
  Wire.endTransmission();

  
}

void loop() {
  DHT11read();
  BH1750read();
  if(digitalRead(D3)==LOW)
  {
    delay(10);
    while(digitalRead(D3)==LOW);
    delay(10);
    disbar =!disbar;
  }
  if(disbar==false)
  {
    if (isnan(_h) || isnan(_t) ) 
    {
       return;
    }else
    {
      displayOLED();
    }
  }else if(disbar==true)
  {
    if (isnan(_h) || isnan(_t) ) 
    {
       return;
    }else
    {
      displaybar();
    }
  }
}
