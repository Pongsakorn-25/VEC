const int pingPin = D2;
const int inPin = D1;
long duration, cm; 
unsigned long _premil0 = 0; 
unsigned long _premil1 = 0;  
unsigned long _premil2 = 0; 
unsigned long _premil3 = 0; 
unsigned long _premil4 = 0;          
const long _time0 = 100; //Serail
const long _time1 = 700; //>50cm
const long _time2 = 350; //>25cm
const long _time3 = 175; //>10cm 
const long _time4 = 700; // ; 
bool _50CM =false;  
bool _25CM =false;
bool _10CM =false;
unsigned long currentMillis; 
int _pwmLevel= 512;
void setup() {
Serial.begin(9600);
pinMode(inPin, INPUT);
pinMode(pingPin, OUTPUT);
//pinMode(D8,OUTPUT);
analogWrite(D8,0);
analogWriteFreq(200);
}
 
void loop()
{
  
  
  
  //delay(100);
  currentMillis = millis();
  
  if (currentMillis - _premil0 >= _time0) {
    _premil0 = currentMillis;
    digitalWrite(pingPin, LOW);
    delayMicroseconds(1);
    digitalWrite(pingPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(pingPin, LOW);

    duration = pulseIn(inPin, HIGH);
 
    cm = microsecondsToCentimeters(duration);
 
    Serial.print(cm);
    Serial.print("cm");
    Serial.println();
    Serial.println();
  }
  if(cm<=50&&cm>=25){
    
    _50CM =true;
    _25CM =false;
    _10CM =false;
    
  }else if(cm<=24&&cm>=11){
    _50CM =false;
    _25CM =true;
    _10CM =false;
    
  }else if(cm<=10){
    _50CM =false;
    _25CM =false;
    _10CM =true;
    
  }else{
    _50CM =false;
    _25CM =false;
    _10CM =false;
    analogWrite(D8,0);  
  }
  if ((currentMillis - _premil1 >= _time1)&&_50CM ) {
    _premil1 = currentMillis;
    if(_pwmLevel>=512){
      _pwmLevel=0;
    }else{
      _pwmLevel=512;
    }
    analogWrite(D8,_pwmLevel);
  }
  if ((currentMillis - _premil2 >= _time2)&&_25CM ) {
    _premil2 = currentMillis;
    if(_pwmLevel>=512){
      _pwmLevel=0;
    }else{
      _pwmLevel=512;
    }
    analogWrite(D8,_pwmLevel);
  }
  if ((currentMillis - _premil3 >= _time3)&&_10CM ) {
    _premil3 = currentMillis;
    if(_pwmLevel>=512){
      _pwmLevel=0;
    }else{
      _pwmLevel=512;
    }
    analogWrite(D8,_pwmLevel);
  }
   
}
 
long microsecondsToCentimeters(long microseconds)
{
// The speed of sound is 340 m/s or 29 microseconds per centimeter.
// The ping travels out and back, so to find the distance of the
// object we take half of the distance travelled.
return microseconds / 58;
}
