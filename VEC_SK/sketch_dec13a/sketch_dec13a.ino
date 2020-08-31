int value =0 ;
void setup() {
  Serial.begin(115200);
pinMode(2,OUTPUT);
}

void loop() {
for(value =0 ;value <=255;value += 5)
{

  analogWrite(2,value);
  Serial.println(analogRead(2));
  //int x = map(analogRead(2),0,255,0,5);
  //Serial.println(x);
  delay(100);
 
  
}
for(value =255 ;value >=0;value -= 5)
{
  
  analogWrite(2,value);
  Serial.println(analogRead(2));
  //int x = map(analogRead(2),0,255,0,5);
  //Serial.println(x);
  delay(100);
 
}
}
