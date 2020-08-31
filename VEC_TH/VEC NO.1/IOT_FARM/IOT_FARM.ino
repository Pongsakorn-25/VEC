#include <ESP8266WiFi.h>
#include <MicroGear.h>
#include <Wire.h>                   // Include library
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#define OLED_RESET -1
Adafruit_SSD1306 display(OLED_RESET); 
const char* ssid     = "asdfghj";
const char* password = "91992189327";
int HUD;
int PH;
int LUX;
#define APPID   "NODE01"
#define KEY     "OXb804pkAVgc4T5"
#define SECRET  "h88iAcdXjQKlqgaipt5BCAI0c"
#define ALIAS   "NODE010"
WiFiClient client;
MicroGear microgear(client);


void onMsghandler(char *topic, uint8_t* msg, unsigned int msglen) {
    Serial.print("Incoming message --> ");
    msg[msglen] = '\0';
    Serial.println((char *)msg);
}
void onConnected(char *attribute, uint8_t* msg, unsigned int msglen) {
    Serial.println("Connected to NETPIE...");
     microgear.setAlias(ALIAS);
}

unsigned int readADS7828(unsigned char ads_address, unsigned char channel, bool mode)
{
  ads_address = ads_address >> 1 ; //
  // command address for the channels, allows 0-7 channel mapping in the correct order
  unsigned char channels[8] = {0x00, 0x40, 0x10, 0x50, 0x20, 0x60, 0x30, 0x70};
  unsigned char command = 0;    // Initialize command variable
  unsigned int reading = 0;     // Initialize reading variable

  command = channels[channel];    // put required channel address in command variable

  if (mode) {                     // mode = 1 Single-ended input, mode = 0 Differential input
    command = command ^ 0x80;     // Enable Single-ended mode (toggle MSB, SD bit in datasheet)
  }

  Wire.beginTransmission(ads_address);  // Send a start or repeated start command with a slave address and the R/W bit set to '0' for writing.
  Wire.write(command);            // Then send a command byte for the register to be read.
  Wire.endTransmission();       // Send stop command
  delay(10);
  Wire.requestFrom(ads_address, 2);   // Request 2 bytes from the ADC
  if (2 <= Wire.available())      // if two bytes were received
  {
    reading = Wire.read();        // receive high byte
    reading = reading << 8;       // shift high byte to be high 8 bits
    reading |= Wire.read();       // receive low byte into lower 8 bits
  }
  return reading;         // return the full 12 bits reading from the ADC channel
}
void displayOLED()
{
    display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(WHITE);          //Set text color
  display.setCursor(5,5);               //Set display start position
  display.println("HUD="+String(HUD)+"%");  
  display.setCursor(5,25);               //Set display start position
  display.println("PH="+String(PH));
  display.setCursor(5,45);               //Set display start position
  display.println("LIGTH="+String(LUX));
  display.display();
 }
void setup() {
    Wire.begin();
    microgear.on(MESSAGE,onMsghandler);
    microgear.on(CONNECTED,onConnected);
    Serial.begin(115200);
    Serial.println("Starting...");
    display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  
    /* Initial WIFI, this is just a basic method to configure WIFI on ESP8266.                       */
    /* You may want to use other method that is more complicated, but provide better user experience */
    if (WiFi.begin(ssid, password)) {
        while (WiFi.status() != WL_CONNECTED) {
            delay(500);
            Serial.print(".");
        }
    }

    Serial.println("WiFi connected");  
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());

    /* Initial with KEY, SECRET and also set the ALIAS here */
    microgear.init(KEY,SECRET,ALIAS);

    /* connect to NETPIE to a specific APPID */
    microgear.connect(APPID);
    display.display();
    delay(2000);
    display.clearDisplay();
}


void loop() {
  HUD = map(analogRead(A0),0,953,0,100);
  PH  = map(readADS7828(B10010001,0,1),0,4093,0,14);
  LUX = map(readADS7828(B10010001,1,1),0,4093,0,1000);
  
  if (microgear.connected()) 
  {
        microgear.loop();
        displayOLED();
        microgear.chat("NODE010/HUD",HUD);
        microgear.chat("NODE010/PH",PH);
        microgear.chat("NODE010/LUX",LUX);
        microgear.publish("/HUD",HUD);
        microgear.publish("/PH",PH);
        microgear.publish("/LUX",LUX);
  }else{
  microgear.connect(APPID);
  }
}
