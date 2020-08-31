
#include <SoftwareSerial.h>
#define Switch_1        13
#define Switch_2        12

#define Heater_On       11
#define Heater_Level    9

#define Fan_On          8
#define Fan_Speed       10

#define Mist_Pump       7
#define Lighter         6
  byte Output;

  uint8_t   Status_Sw1, Status_Sw2;
  byte      DataRead[15];
  String    SerialRecieve, SoftwareRecieve;
/**/  //AFTER YOU MANAULS CONTROL USE BELOW PARAMETER TO COLLECT DATA FOR SEND BACK TO CLIENT.
/**/  byte F_LV;                      //<---USE THIS TO GET PERCENT OF FAN    LV(0-100)  
/**/  byte H_LV;                      //<---USE THIS TO GET PERCENT OF HEAT   LV(0-100)  
/**/  byte L_LV;                      //<---USE THIS TO GET PERCENT OF LIGHT  LV(0-100)  
/**/  String M_ST="OFF";              //<---USE THIS TO GET STATE OF MIST     ON/OFF 
/**/  //*************************************************************************************
  bool      ClearSerial = true;
  bool      dora;
  bool      ClearStatus;
  long      pre,sam = 500;
  float     HUMIDITY;             //<---USE THIS TO CALCULATE
  float     TEMPARETURE;          //<---USE THIS TO CALCULATE
  uint32_t  LIGHT,OLDL;                //<---USE THIS TO CALCULATE
  
  String    Buffer;               //<--ONLY USE THIS TO DEFINE MANAUL COMMAND.
  String    humidity;             //<--NOT USE THIS TO CALCULATE (only use to show **not recommand**)
  String    tempareture;          //<--NOT USE THIS TO CALCULATE (only use to show **not recommand**)
  String    light;                //<--NOT USE THIS TO CALCULATE (only use to show **not recommand**)
  
  SoftwareSerial ESPPort(2,3);

/**/  //all command and desciption 
/**/  //CommandReadSensor();         //<---Get raw   data(HEX)                                 |
/**/  //getFulldata();               //<---Get all   data(DEC)                                 |
/**/  //getHumidity();               //<---Get only  Humidity(DEC)                             | 
/**/  //getTempareture();            //<---Get only  Tempareture(DEC)                          |
/**/  //getLigth();                  //<---Get only  Ligth(DEC)                                |
/**/  //pushData();                  //<---SEND ALL DATA OFF PLANT BOARD TO ESP PORT           |(FAN LEVEL /HEAT LEVEL /LIGHT LEVEL /MIST ONOFF/  SENSOR:HUD/TEMP/LIGTH )
/**/  //ManualOnOff();               //<---USE TO MANAUL CONTROL FORM CLIENT VIA SERAIL PORT   |(DO NOT EDIT)
/**/  //SWCHECK();                   //<---MAKE YOUR MANUAL SW CONTROL IN THIS FUNCTION        |
/**/  //ESPREAD();                   //<---USE TO MAKE YOUR FUNCTION CONTROL FROM CLIENT       |   
/**/  //*************************************************************************************************************************************
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);                     //START SERIAL.PORT TO CONNET PLAT CONTROL BOARD 
  ESPPort.begin(9600);                    //START SERIAL.PORT TO CONNET ESP CONTROL BOARD 
  ClearStatus = false;                    
  delay(1000);
  
/**/  //PINMODE ZONE
/**/   pinMode(Switch_1, INPUT);   pinMode(Switch_2, INPUT);
/**/   pinMode(Heater_On, OUTPUT); pinMode(Heater_Level, OUTPUT);
/**/   pinMode(Fan_On, OUTPUT);    pinMode(Fan_Speed, OUTPUT);
/**/   pinMode(Lighter, OUTPUT);
/**/   pinMode(Mist_Pump, OUTPUT);
/**/  //************************************************************


/**/  //initial pinMOde First time
/**/  digitalWrite(Heater_On, HIGH);  analogWrite(Heater_Level, 0);
/**/  digitalWrite(Fan_On, LOW);      analogWrite(Fan_Speed, 0);
/**/  analogWrite(Lighter, 0);
/**/  digitalWrite(Mist_Pump, LOW);
/**/  //************************************************************



}
void loop() {
  ESPREAD();
  SWCHECK();
  getFulldata();
  if(millis()-pre>100){
      pre = millis();
      if(HUMIDITY>95.5){
          Output++;
          digitalWrite(Mist_Pump,LOW);
          if(Output>=250){
            Output=250;
          }
      }
      if(HUMIDITY<95.0){
        digitalWrite(Mist_Pump,HIGH);
          Output--;
          if(Output<=10){
            Output=10;
          }
      }
      digitalWrite(Fan_On,HIGH);
      analogWrite(Fan_Speed, Output);
               
  }
  Serial.println();
  if(dora){
     pushData();
  }
}
void SWCHECK(){
  Status_Sw1 = digitalRead(Switch_1);
  if(Status_Sw1 == 0){
      
  }
  while (Status_Sw1 == 0){
    Status_Sw1 = digitalRead(Switch_1);
    
  }
  
  Status_Sw2 = digitalRead(Switch_2);
  if(Status_Sw2 == 0){
    pushData(); 
  }
  while (Status_Sw2 == 0){
    Status_Sw2 = digitalRead(Switch_2);
  }
  
}
void ESPREAD(){
  if(ESPPort.available()){

    char c = ESPPort.read();                       
    if (c == '\n'){
      Serial.println(SerialRecieve);
      if(SerialRecieve=="hello"){
        pushData();
        dora=true;
      }else if(SerialRecieve=="SS"){
        ClearSerial=true;
      }else{
        ManaulOnOff();
      }
      SerialRecieve="";
    }
    else if (c != '\r'){                                  
          
      SerialRecieve += c;                                   
    }     
  }
}


void getFulldata(){
  CommandReadSensor();
  getHumidity();
  getTempareture();
  getLigth();
}
void getHumidity(){
    //byte2-5 HUD
    //CommandReadSensor();
    humidity="";
    for(int i=0;i<4;i++){
      humidity+=DataRead[i+2];
    }
    //Serial.println(humidity);
    HUMIDITY=(humidity.toInt())*0.1;
    //Serial.println(HUMIDITY);
}
void getTempareture(){
    //byte6-9 TEMP
    //CommandReadSensor();
    tempareture="";
    for(int i=0;i<4;i++){
      tempareture+=DataRead[i+6];
    }
    //Serial.println(tempareture);
    TEMPARETURE=(tempareture.toInt())*0.1;
    //Serial.println(TEMPARETURE);
}   
void getLigth(){ 
    //byte10-12 LIGTH 
    //CommandReadSensor(); 
    LIGHT=0;
    int buf = 256;
    for(int i=0;i<3;i++){
      LIGHT+=DataRead[i+10]*buf;
      buf=buf>>4;
    }
    light=LIGHT;
    //Serial.println(LIGHT);
}   
void pushData(){
  //hud
  //temp
  //ligth
  getFulldata();
  //fan       on/off  //fan       speed (0-255)
  //heater    on/off  //heater    level (0-255)
  //lighting  on/off  //lighting  level (0-255)
  //mist      on/off
  String allData;
  allData+= "DATA-FAN"+String(F_LV)+"-HEAT"+String(H_LV)+"-LTG"+String(L_LV)+"-MIST"+M_ST+"-HUD"+String(HUMIDITY)+"-TEMP"+String(TEMPARETURE)+"-LIGHT"+String(LIGHT);
  //Serial.println(allData);
  if(ClearSerial){
           
      ESPPort.println(allData);
      ClearSerial=false;
  }  
}
void ManaulOnOff(){
  if(SerialRecieve.indexOf("F-")>=0)
        {
          Buffer=SerialRecieve; Buffer.remove(0,2);
          if(Buffer.indexOf("ON-")>=0){
              Buffer.remove(0,3);
              //Serial.println(Buffer);
              F_LV = Buffer.toInt();
              //Serial.println(Buffer);
              byte LEVEL = map(F_LV,0,100,0,255);
              digitalWrite(Fan_On,HIGH);
              analogWrite(Fan_Speed,LEVEL); 
            }else{
              F_LV = 0;
              digitalWrite(Fan_On,LOW);
              analogWrite(Fan_Speed,0); 
            }
      }else if(SerialRecieve.indexOf("H-")>=0)
        {
          //Serial.println(SerialRecieve);
          Buffer=SerialRecieve; Buffer.remove(0,2);
          //Serial.println(Buffer);
          if(Buffer.indexOf("ON-")>=0)
            {
              Buffer.remove(0,3);
              //Serial.println(Buffer);
              H_LV = Buffer.toInt();
              //Serial.println(Buffer);
              byte LEVEL = map(H_LV,0,100,0,255);
              digitalWrite(Heater_On,LOW);
              analogWrite(Heater_Level,LEVEL); 
            }else{
              H_LV =0;
              digitalWrite(Heater_On,HIGH);
              analogWrite(Heater_Level,0); 
            }
      }else if(SerialRecieve.indexOf("L-")>=0)
        {
          //Serial.println(SerialRecieve);
          Buffer=SerialRecieve;Buffer.remove(0,2);
          //Serial.println(Buffer);
          if(Buffer.indexOf("ON-")>=0)
            {
              Buffer.remove(0,3);
              //Serial.println(Buffer);
              L_LV = Buffer.toInt();
              //Serial.println(Buffer);
              byte LEVEL = map(L_LV,0,100,0,255);
              analogWrite(Lighter,LEVEL); 
            }else{
              L_LV=0;
              analogWrite(Lighter,0); 
            }
      }else if(SerialRecieve.indexOf("M-")>=0)
        {
          //Serial.println(SerialRecieve);
          Buffer=SerialRecieve;Buffer.remove(0,2);
          //Serial.println(Buffer);
          if(Buffer.indexOf("ON-")>=0)
            {
              Buffer.remove(0,3);
              //Serial.println(Buffer);
              M_ST = "ON";
              digitalWrite(Mist_Pump,HIGH); 
            }else{
              M_ST = "OFF";
              digitalWrite(Mist_Pump,LOW);  
            }
        }
}
void CommandReadSensor(){

  boolean LoopRead = true;
  int Buffer_1;
  byte CommandSend[5];
  byte BufferClear;
  bool BitClear;

  
    //0x02 0x0A 0x23 0x2D 0x03
  CommandSend[0] = 0x02;
  CommandSend[1] = 0x0A;
  CommandSend[2] = 0x23;
  CommandSend[3] = 0x2D;
  CommandSend[4] = 0x03;  
  
  Serial.write(CommandSend, 5);

  while(LoopRead){

    if (Serial.available()){
      
      if(ClearStatus){

        goto Label_1;
      }
    
      DataRead[0] = Serial.read();
    
      if(DataRead[0] == 0x02){
        
Label_1:
        ClearStatus = false;
           
        for(int i=1; i<15; i++){

          while(!(Serial.available())){

            //
          }

          DataRead[i] = Serial.read();
        }

        if(DataRead[14] == 0x03){

          if(DataRead[1] == 0x0B){

            Buffer_1 = DataRead[1] + DataRead[2] + DataRead[3] + DataRead[4] + DataRead[5] + DataRead[6] + DataRead[7] + DataRead[8] + DataRead[9] + DataRead[10] + DataRead[11] + DataRead[12];
            if(DataRead[13] == Buffer_1){
              
              //Status = true;
              
            }
          }
        }
        else{

          goto Label_2;
        }

        LoopRead = false;
      }
      
      else{
Label_2:
        BitClear = true;
        
        while(BitClear){
        
          unsigned long previousMicros = micros();
        
          while(!(Serial.available())){

            unsigned long currentMicros = micros();
          
            if (currentMicros - previousMicros >= 100) {

              goto Label_3;
            }
          }

          BufferClear = Serial.read();
          if(BufferClear == 0x02){

            BitClear = false;  
            ClearStatus = true;
          }
        }
      } 
    }
    
Label_3:
    BitClear = false;
    LoopRead = false;    
  }
}
