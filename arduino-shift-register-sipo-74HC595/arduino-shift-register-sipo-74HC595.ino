//**************************************************************//
//  Name    : shiftOutCode, Hello World
//  Author  : Carlyn Maw,Tom Igoe, David A. Mellis, (EDIT) Javier Arellano
//  Date    : 25 Oct, 2006
//  Modified: 23 Mar 2010 (EDIT) 07 Sep 2024
//  Version : 2.0 (EDIT) 2.1
//  Notes   : Code for using a 74HC595 Shift Register           //
//          : to count from 0 to 255
//****************************************************************
// 
// (EDIT) Note: shift registers (SIPO, Serial-In Parallel-Out and PISO, Parallel-In Serial-Out) require at least 3 pins to operate,
// so they might be able to use the GPIO0, GPIO2 and TX (for SIPO) or RX (for PISO) pins when used with the ESP8266-01(S)
// In my circuit, I used an SN74HC595N shift register, which seems to be the same or almost identical to the 74HC595
// 
// Pin connected to ST_CP of 74HC595
int latchPin = 8;
// Pin connected to SH_CP of 74HC595
int clockPin = 12;
// Pin connected to DS of 74HC595
int dataPin = 11;
void setup() {
  // set pins to output so you can control the shift register
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
  Serial.begin(9600);
}
void loop() {
  // count from 0 to 255 and display the number
  // on the LEDs
  for (int numberToDisplay = 0; numberToDisplay < 256; numberToDisplay++) {
    // take the latchPin low so
    // the LEDs don't change while you're sending in bits:
    digitalWrite(latchPin, LOW);
    // shift out the bits:
    // 
    // (EDIT) Explanation, as I understand it
    // - 0 = B00000000, 4 = B00000100, and so forth
    // - Q0 is wired to be the LSB, and Q7 is wired to be the MSB according to the tutorial from: https://docs.arduino.cc/tutorials/communication/guide-to-shift-out/
    // - So by passing "MSBFIRST" to shiftOut, we ensure that, i. e. in 4 or B00000100, the leading zero is passed first and the shifted until they reach Q7, so Q2 takes the 1 and so forth
    // - (in short, the MSBFIRST or LSBFIRST choice depends on the wiring of the circuit)
    // 
    shiftOut(dataPin, clockPin, MSBFIRST, numberToDisplay);
    // take the latch pin high so the LEDs will light up
    digitalWrite(latchPin, HIGH);
    // (EDIT) print current number to serial monitor
    Serial.println(String(numberToDisplay).c_str());
    // pause before next value
    delay(500);
  }
}