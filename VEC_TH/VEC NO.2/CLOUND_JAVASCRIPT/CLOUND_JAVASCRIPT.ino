#include <ESP8266WiFi.h>
#define SW D1

const char* ssid ="asdfghj";
const char* password ="91992189327";

WiFiServer server(80);


void setup() {
  Serial.begin(115200);
  delay(10);
  Serial.println("");Serial.println("");
  Serial.print("CONNECTING TO");
  Serial.println(ssid);
  WiFi.begin(ssid,password);
  while(WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  
  Serial.println("IP Address");
 
  Serial.println(WiFi.localIP());

  server.begin();
  Serial.println("Server started");
  ESP.wdtDisable();
  ESP.wdtEnable(WDTO_8S);
}

void loop() {
  // put your main code here, to run repeatedly:
  ESP.wdtFeed();
  WiFiClient client = server.available();
  if(!client)
  {
    return;
  }
  Serial.println("new client");
  while(!client.available())
  {
    delay(1);
  }
  String req = client.readStringUntil('\r');
  Serial.println(req);
  client.flush();



}
