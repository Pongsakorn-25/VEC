#define LED1          6
#define LED2          5
#define LED3          4
#define LED4          3

void setup() 
{
  pinMode(LED1,OUTPUT);
  pinMode(LED2,OUTPUT);
  pinMode(LED3,OUTPUT);
  pinMode(LED4,OUTPUT);
  Serial.begin(115200);
  while(!Serial)
  {
    //
  }
}

void loop() {
  String incomingByte;
  int d;
  if (Serial.available() > 0) 
  {
    incomingByte = Serial.readString();
    if(incomingByte =="led1on"){ d=1;}
    if(incomingByte =="led1off"){ d=2;}
    if(incomingByte =="led2on"){ d=3;}
    if(incomingByte =="led2off"){ d=4;}
    if(incomingByte =="led3on"){ d=5;}
    if(incomingByte =="led3off"){ d=6;}
    if(incomingByte =="led4on"){ d=7;}
    if(incomingByte =="led4off"){ d=8;}
    
    
    switch (d)
    {
      case 1 : digitalWrite(LED1,HIGH);
               break;
      case 2 : digitalWrite(LED1,LOW);
               break;
      case 3 : digitalWrite(LED2,HIGH);
               break;
      case 4 : digitalWrite(LED2,LOW);
               break;
      case 5 : digitalWrite(LED3,HIGH);
               break;
      case 6 : digitalWrite(LED3,LOW);
               break;
      case 7 : digitalWrite(LED4,HIGH);
               break;
      case 8 : digitalWrite(LED4,LOW);
               break;                  
    }
  }
  
}

