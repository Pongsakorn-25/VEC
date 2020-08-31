


void setup() {

pinMode(7,OUTPUT);
pinMode(13,OUTPUT);
analogWrite(7,125);
TCCR4B = (TCCR4B & 0xF8) | 0x04;
}

void loop() {
digitalWrite(13,!digitalRead(13));
delay(500);
}
