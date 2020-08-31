#include <ESP8266WiFi.h>
#include <WiFiUDP.h>
#include <Wire.h>
#include <Adafruit_SSD1306.h>
#define OLED_RESET 0
#define Status_LED  2  
#define Switch_1    14
#define Switch_2    16
#define LED_1       13

  const char *ssid = "Resolution";
  const char *password = "12345678";
  unsigned int UDPPort = 4023;                

  int Status_Sw1, Status_Sw2;
  int packetSize, len, NumText;
  String NameString, BufferString,SerialRecieve,MYCommand;
  bool sendCommand=false;
  const int lineH_String1 = (10);const int lineW_String1 = (6);
  const int lineH_String2 = (16);const int lineW_String2 = (12);
  const int lineH_String3 = (26);const int lineW_String3 = (19);

  int FANDATA;  
  int HEATDATA;
  int LTGDATA;
  String MIST;
  int HUD;
  int TEMP;
  int LIGHT;
  
  Adafruit_SSD1306 OLEDdisplay(OLED_RESET);
  WiFiUDP Udp;
  
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(Status_LED, OUTPUT);
  pinMode(LED_1, OUTPUT);
  pinMode(Switch_1, INPUT);
  pinMode(Switch_2, INPUT);
  digitalWrite(Status_LED,LOW);
  digitalWrite(LED_1,LOW);

  OLEDdisplay.begin(SSD1306_SWITCHCAPVCC, 0x3C); 
  OLEDdisplay.clearDisplay();                     // Clear the buffer.
  OLEDdisplay.display();
  
  delay(1000);
  
  printOLED_String1(0,1,"Connecting to :");
  printOLED_String1(3,2,ssid);
  
  WiFi.begin(ssid, password);

  int i=0;
  while (WiFi.status() != WL_CONNECTED){
    
    delay(500);
    printOLED_String1(i,3,"." );
    i++;
  }
  
  OLEDdisplay.clearDisplay();   
  Udp.begin(UDPPort);
  printOLED_String1(3,1,"WiFi UDP Mode");
  printOLED_String1(2,2,WiFi.localIP().toString());
  Serial.println(WiFi.localIP().toString());
}

void loop() {
  UDP_write();
  UDP_read();

}
void UDP_write(){
  if (Serial.available()>0) {
     SerialRecieve = Serial.readString();
    
      
      char StringBuffer[(SerialRecieve.length())+1];
      Serial.println(SerialRecieve);
      SerialRecieve.toCharArray(StringBuffer,(SerialRecieve.length())+1);
      Udp.beginPacket(Udp.remoteIP(),UDPPort);
      Udp.write(StringBuffer,SerialRecieve.length());
      Udp.endPacket();
      SerialRecieve=""; 
  }
  if (sendCommand) {
      SerialRecieve = MYCommand;
      char StringBuffer[(SerialRecieve.length())+1];
      Serial.println(SerialRecieve);
      SerialRecieve.toCharArray(StringBuffer,(SerialRecieve.length())+1);
      Udp.beginPacket(Udp.remoteIP(),UDPPort);
      Udp.write(StringBuffer,SerialRecieve.length());
      Udp.endPacket();
      SerialRecieve="";    
  }
}

void UDP_read(){
  packetSize = Udp.parsePacket();
  if( packetSize>0){
    char packetBuffer[packetSize];
    len = Udp.read(packetBuffer,packetSize);
    if(len>0){
      packetBuffer[len]=0;
    }
    BufferString = "";
    for(int i =0;i<len;i++){
      BufferString+= String(packetBuffer[i]);
    }
    Serial.println(BufferString);
    MNST();
  }
  
}
void MNST(){
  String dataBuffer;
  if(BufferString.indexOf("DATA-">=0)){
    dataBuffer=BufferString;
    dataBuffer.remove(0,5);
    if(BufferString.indexOf("FAN")>=0){
      dataBuffer.remove(0,3);
      int i = 0;
      FANDATA = 0;
      String DUMMY;
      while(dataBuffer[i]!='-')
      {
        DUMMY += dataBuffer[i];
        i++;
      }
      FANDATA = DUMMY.toInt();
      dataBuffer.remove(0,i+1);
      //Serial.println(dataBuffer);
      Serial.println(FANDATA);
    }
    if(BufferString.indexOf("HEAT")>0){
      dataBuffer.remove(0,4);
      int i = 0;
      HEATDATA = 0;
      String DUMMY;
      while(dataBuffer[i]!='-')
      {
        DUMMY += dataBuffer[i];
        i++;
      }
      HEATDATA = DUMMY.toInt();
      dataBuffer.remove(0,i+1);
     // Serial.println(dataBuffer);
      Serial.println(HEATDATA);
    }
    if(BufferString.indexOf("LTG")>0){
      dataBuffer.remove(0,3);
      int i = 0;
      LTGDATA = 0;
      String DUMMY;
      while(dataBuffer[i]!='-')
      {
        DUMMY += dataBuffer[i];
        i++;
      }
      LTGDATA = DUMMY.toInt();
      dataBuffer.remove(0,i+1);
      //Serial.println(dataBuffer);
      Serial.println(LTGDATA);
    }
     if(BufferString.indexOf("MIST")>0){
      dataBuffer.remove(0,4);
      int i = 0;
      MIST = "";
      String DUMMY;
      while(dataBuffer[i]!='-')
      {
        DUMMY += dataBuffer[i];
        i++;
      }
      MIST = DUMMY;
      dataBuffer.remove(0,i+1);
      //Serial.println(dataBuffer);
      Serial.println(MIST);
    }
     if(BufferString.indexOf("HUD")>0){
      dataBuffer.remove(0,3);
      int i = 0;
      HUD = 0;
      String DUMMY;
      while(dataBuffer[i]!='-')
      {
        DUMMY += dataBuffer[i];
        i++;
      }
      HUD = DUMMY.toInt();
      dataBuffer.remove(0,i+1);
     // Serial.println(dataBuffer);
      Serial.println(HUD);
    }
     if(BufferString.indexOf("TEMP")>0){
      dataBuffer.remove(0,4);
      int i = 0;
      TEMP= 0;
      String DUMMY;
      while(dataBuffer[i]!='-')
      {
        DUMMY += dataBuffer[i];
        i++;
      }
      TEMP = DUMMY.toInt();
      dataBuffer.remove(0,i+1);
      //Serial.println(dataBuffer);
      Serial.println(TEMP);
    }
    if(BufferString.indexOf("LIGHT")>0){
      dataBuffer.remove(0,5);
      int i = 0;
      LIGHT= 0;
      String DUMMY;
      while(dataBuffer[i]!='\n')
      {
        DUMMY += dataBuffer[i];
        i++;
      }
      LIGHT = DUMMY.toInt();
      dataBuffer.remove(0,dataBuffer.length());
      //Serial.println(dataBuffer);
      Serial.println(LIGHT);
    }

    
  }
}

void printOLED_String3 (int w,int h,String s ){
  // 7 character, 2 line
  OLEDdisplay.setTextSize(3);
  OLEDdisplay.setCursor(w*lineW_String3, (h*lineH_String3)+10);
  OLEDdisplay.setTextColor(WHITE);
  OLEDdisplay.print(s);
  OLEDdisplay.display();
}
void printOLED_String2 (int w,int h,String s ){
  // 10 character, 4 line
  OLEDdisplay.setTextSize(2);
  OLEDdisplay.setTextColor(WHITE);
  OLEDdisplay.setCursor(w*lineW_String2, (h*lineH_String2));              
  OLEDdisplay.print(s);
  OLEDdisplay.display();
}
void printOLED_String1 (int w,int h,String s ){
  // 21 character, 6 line
  OLEDdisplay.setTextSize(1);
  OLEDdisplay.setTextColor(WHITE);
  OLEDdisplay.setCursor(w*lineW_String1, (h*lineH_String1));               
  OLEDdisplay.print(s);
  OLEDdisplay.display();
}
