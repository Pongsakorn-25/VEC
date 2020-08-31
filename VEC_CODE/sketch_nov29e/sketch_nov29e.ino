void setup() {
  // put your setup code here, to run once:
   Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
   Serial.println("F-ON-100");
   Serial.println("H-ON-100");
   Serial.println("L-ON-100");
   Serial.println("M-ON-100");
   delay(5000);
   Serial.println("F-OFF");
   Serial.println("H-OFF");
   Serial.println("L-OFF");
   Serial.println("M-OFF");
   delay(5000);
}
