#define sw      7
#define led     6

String i;
int a=0;
void setup() {
  Serial.begin(115200);
  while(!Serial)
  {
    //
  }
  pinMode(sw,INPUT);
  pinMode(led,OUTPUT);
  digitalWrite(sw,HIGH);
}

void loop() 
{
  if(Serial.available()>0)
  {
    i=Serial.readString();
    if(i=="192.168.1.2")
    { 
      a=1;
      Serial.println("\nplease button to connect ");
      
    }
    else
    {
      Serial.println("OK");
    }
  }  
  while(a==1)
  { 
    if(digitalRead(sw) ==LOW)
      {
        delay(80);
        while(digitalRead(sw) != HIGH);
        delay(80);
        Serial.write('y');
        delay(80);
        Serial.println("\nconnect to 192.168.1.1 Complete ");
        digitalWrite(led,HIGH);
      }
}
} 
  

