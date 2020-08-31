void setup() {
  Serial.begin(115200);
  while(!Serial)
  {
    //
  }
}

void loop() {
  char incomingByte;
  if (Serial.available() > 0) 
  {
    incomingByte = Serial.read();
    Serial.print("I received: ");
    Serial.println(incomingByte, DEC);
  }
}
