#define RPWM_Pin 5
#define LPWM_Pin 6



void setup() {
 Serial.begin(9600);
pinMode(RPWM_Pin,OUTPUT);
pinMode(LPWM_Pin,OUTPUT);
}

void loop() {
  // not working
digitalWrite(RPWM_Pin,1);
digitalWrite(LPWM_Pin,0);
Serial.println("CW");
delay(2000);
digitalWrite(RPWM_Pin,0);
digitalWrite(LPWM_Pin,1);
Serial.println("CCW");
delay(2000);
}
