
#include <ESP8266WiFi.h>
#include <WiFiUDP.h>

  const char *ssid = "Resolution";
  const char *password = "12345678";
  const char* host = "192.168.43.37";
  unsigned int UDPPort = 4023;                // local port to listen on
  int Status_LED = 2;
  int packetSize,len;
  String BufferString,SerialRecieve,MYCommand;
  bool sendCommand=false; 
  WiFiUDP Udp;

  
void setup() {
  Serial.begin(9600);
  pinMode(Status_LED, OUTPUT);
  digitalWrite(Status_LED, HIGH);  delay(500);
  Serial.print("Connecting to :");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    //Serial.print(".");
  }
  digitalWrite(Status_LED, LOW);
  delay(2000);
  digitalWrite(Status_LED, HIGH);
  delay(500);
  digitalWrite(Status_LED, LOW);
  delay(500);
  digitalWrite(Status_LED, HIGH);
  delay(500);
  digitalWrite(Status_LED, LOW);
  delay(500);
  Serial.println();
  Serial.print("WiFi UDP Mode : ");
  Serial.println(WiFi.localIP().toString());

  delay(1000);

  digitalWrite(Status_LED, HIGH);


  Udp.begin(UDPPort);

  delay(500);
}




void loop() {

  UDP_write(); 
  UDP_read();

}
void UDP_write(){
  if (Serial.available()) {
      SerialRecieve = Serial.readString();
      char StringBuffer[(SerialRecieve.length())+1];
      Serial.println("SS");
      SerialRecieve.toCharArray(StringBuffer,(SerialRecieve.length())+1);
      Udp.beginPacket(host,UDPPort);
      Udp.write(StringBuffer,SerialRecieve.length());
      Udp.endPacket();
      SerialRecieve="";    
  }
   if (sendCommand) {
      SerialRecieve = MYCommand;
      char StringBuffer[(SerialRecieve.length())+1];
      Serial.println(SerialRecieve);
      SerialRecieve.toCharArray(StringBuffer,(SerialRecieve.length())+1);
      Udp.beginPacket(host,UDPPort);
      Udp.write(StringBuffer,SerialRecieve.length());
      Udp.endPacket();
      SerialRecieve="";    
  }
}

void UDP_read()
{
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
  }
}
