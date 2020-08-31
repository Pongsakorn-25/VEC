/////////////////////////////////////////////////////////////////////
// Author: RSP @ Embedded System Lab (ESL), KMUTNB, Thailand
// Date: 29-Apr-2014
// Target Board: Arduino Uno (ATmega328P, 5V, 16MHz)
// Arduino IDE: version 1.0.5
// Description:
//   This Arduino Sketch shows how to interface the Arduino Uno
//   to a four-digit 7-segment display that utilizes the TM1637
//   LED driver chip. 
/////////////////////////////////////////////////////////////////////

#define CLK_PIN   D4
#define DIO_PIN   D5
#define pingPin   D1
#define inPin     D2
#define bit_delay()   asm("nop\n nop\n nop\n nop\n")

#define TM1637_CMD1  (0x40)
#define TM1637_CMD2  (0xC0)
#define TM1637_CMD3  (0x80)


long duration, cm; 
unsigned long _premil0 = 0;
const long _time0 = 100;
unsigned long currentMillis; 
const uint8_t SEVEN_SEG_DIGITS[] = {
 //  gfedcba
  0b00111111, // 0
  0b00000110, // 1
  0b01011011, // 2
  0b01001111, // 3
  0b01100110, // 4
  0b01101101, // 5
  0b01111101, // 6
  0b00000111, // 7
  0b01111111, // 8
  0b01101111, // 9
 };
long microsecondsToCentimeters(long microseconds)
{
// The speed of sound is 340 m/s or 29 microseconds per centimeter.
// The ping travels out and back, so to find the distance of the
// object we take half of the distance travelled.
return microseconds / 58;
} 
void tm1637_init() {
  pinMode( CLK_PIN, OUTPUT );
  pinMode( DIO_PIN, OUTPUT );
  digitalWrite( CLK_PIN, HIGH );
  digitalWrite( DIO_PIN, HIGH );
}

void tm1637_start_bit() {
  digitalWrite( DIO_PIN, LOW );  bit_delay();
  digitalWrite( CLK_PIN, LOW );  bit_delay();
}

void tm1637_stop_bit() {
  digitalWrite( CLK_PIN, HIGH ); bit_delay();
  digitalWrite( DIO_PIN, HIGH ); bit_delay();
}

int tm1637_send_byte( uint8_t data ) {
  uint8_t ack;
  for( uint8_t i = 0; i < 8; i++ ) { // Send 8-bit data, LSB first
    digitalWrite( CLK_PIN, LOW );
    digitalWrite( DIO_PIN, ( data & 0x01 ) ? HIGH : 0 ); 
    digitalWrite( CLK_PIN, HIGH );
    data >>= 1; // shift bit to the right
  }
  digitalWrite( CLK_PIN, LOW );
  pinMode( DIO_PIN, INPUT );     // make DIO pin floating (input)
  digitalWrite( DIO_PIN, HIGH ); // enable pull-up
  digitalWrite( CLK_PIN, HIGH );
  ack = digitalRead( DIO_PIN );  // read ACK bit
  digitalWrite( DIO_PIN, LOW );
  pinMode( DIO_PIN, OUTPUT );
  digitalWrite( CLK_PIN, LOW );
  return (ack==0);
}

boolean showDigits( uint8_t digits[],
       boolean colon=true, uint8_t brightness=7 ) 
{ 
  // send the first command
  tm1637_start_bit();
  tm1637_send_byte( TM1637_CMD1 );
  tm1637_stop_bit();
  // send the second command
  tm1637_start_bit();
  tm1637_send_byte( TM1637_CMD2 ); 
  for ( uint8_t i=0, value; i < 4; i++ ) {
    value = SEVEN_SEG_DIGITS[ digits[i] ];
    if ( (i == 1) && colon ) {
      value |= 0x80; // turn on the colon on the display
    }
    tm1637_send_byte( value ); 
  }
  tm1637_stop_bit();
  // send the third command
  tm1637_start_bit();
  tm1637_send_byte( TM1637_CMD3 | (brightness & 0x07) | 0x08 );
  tm1637_stop_bit();
}

////////////////////////////////////////////////////////////////////////

uint32_t ts;

void setup() {
  tm1637_init();
  ts = millis();
  Serial.begin(115200);
  Serial.println("");
  pinMode(inPin, INPUT);
  pinMode(pingPin, OUTPUT);
//pinMode(D8,OUTPUT);
  analogWrite(D8,0);
  analogWriteFreq(200);

}

// show time (hour and minute)
void showTime( uint8_t hh, uint8_t mm, boolean colon=false ) {
  static uint8_t data[4];
  data[0] = hh/10;
  data[1] = hh%10;
  data[2] = mm/10;
  data[3] = mm%10;
  showDigits( data, colon );
}

void testDigitalWatch() {
  static boolean colon=false;
  // Start at 12:00:00(hours, minutes and seconds)
  static uint8_t hh=12, mm=0, ss=0; 
  if ( millis() - ts >= 500 ) { // check every 500 msec
    showTime( hh, mm, colon );
    colon = !colon; 
    if (colon) {
      ss = (ss+1)%60;
      if (ss == 0) { 
        mm = (mm+1)%60;
        if (mm == 0) {
          hh = (hh+1)%24;
        } 
      }
    }
    ts += 500; 
  }
}

void testTimer() {
  static uint8_t data[4];
  static uint16_t count = 0, temp;
  if ( millis() - ts >= 100 ) { // check every 100 msec
    temp  = count;
    count = (count+1) % 10000;
    for (uint8_t i=0; i < 4; i++) {
      data[3-i] = temp%10;
      temp /= 10;
    }
    showDigits( data );
    ts += 100; 
  }
}

void loop() {
  //testTimer();
  //testDigitalWatch();
  uint8_t data[4];
  showDigits( data );
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
    if(cm>=40){cm=40;};
    if(cm<5){
      analogWrite(D8,512);
    }else if(cm>=5){
      analogWrite(D8,0);
    }
    Serial.print(cm);
    Serial.print("cm");
    Serial.println();
    Serial.println();
    cm=cm*100;
    for (uint8_t i=0; i < 4; i++) {
      data[3-i] = cm%10;
      cm /= 10;
    }
    showDigits( data );
  }
  
}
