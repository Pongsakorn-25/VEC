#define Switch_1        13
#define Switch_2        12

  uint8_t   Status_Sw1, Status_Sw2;
  byte      DataRead[15];
  bool      ClearStatus;
  
  float     HUMIDITY;             //<---USE THIS TO CALCULATE
  float     TEMPARETURE;          //<---USE THIS TO CALCULATE
  uint32_t  LIGHT;                //<---USE THIS TO CALCULATE

  
  String    humidity;             //<--NOT USE THIS TO CALCULATE (only use to show **not recommand**)
  String    tempareture;          //<--NOT USE THIS TO CALCULATE (only use to show **not recommand**)
  String    light;                //<--NOT USE THIS TO CALCULATE (only use to show **not recommand**)
  
// CommandReadSensor();         ***get raw data(HEX)
// getFulldata();               ***get all data(DEC)
// getHumidity();               ***get only Humidity(DEC)
// getTempareture();            ***get only Tempareture(DEC)
// getLigth();                  ***get only Ligth(DEC)

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
 

  pinMode(Switch_1, INPUT);
  pinMode(Switch_2, INPUT);
  
  ClearStatus = false;
   
  delay(1000);
}

void loop() {
  Status_Sw1 = digitalRead(Switch_1);
  if(Status_Sw1 == 0){
      delay(25);
  }
  while (Status_Sw1 == 0){
    Status_Sw1 = digitalRead(Switch_1);
  }
  
  Status_Sw2 = digitalRead(Switch_2);
  if(Status_Sw2 == 0){
    delay(25);
  }
  while (Status_Sw2 == 0){
    Status_Sw2 = digitalRead(Switch_2);
  }

}







void getFulldata(){
  getHumidity();
  getTempareture();
  getLigth();
}
void getHumidity(){
    //byte2-5 HUD
    CommandReadSensor();
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
    CommandReadSensor();
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
    CommandReadSensor(); 
    LIGHT=0;
    int buf = 256;
    for(int i=0;i<3;i++){
      LIGHT+=DataRead[i+10]*buf;
      buf=buf>>4;
    }
    light=LIGHT;
    //Serial.println(LIGHT);
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
      
//Label_3:
        //BitClear = false;
        //LoopRead = false;
      } 
    }
    
Label_3:
    BitClear = false;
    LoopRead = false;    
  }
}
