#undef int() // fixes a bug with the stdio.h
#include <stdio.h>
#include "fonts.h";

//Pin connected to ST_CP of 74HC595
int latchPin = 19;
//Pin connected to SH_CP of 74HC595
int clockPin = 20;
////Pin connected to DS of 74HC595
int dataPin = 18;

int a[] = {B0111111, B01001000, B01001000, B01001000, B0111111, B0000000, B0000000};

int tymon[] = {83, 89, 77, 79, 78};

void setup() {
  //set pins to output so you can control the shift register
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
}

void loop() {
  writeWord(tymon);
}

void writeWord(int *letters)
{
  for (int numberToDisplay = 0; numberToDisplay < 6; numberToDisplay++) {
    digitalWrite(latchPin, LOW);
    shiftOut(dataPin, clockPin, MSBFIRST, byte(font[letters[numberToDisplay]]));  
    digitalWrite(latchPin, HIGH);
    delay(1);
  }
  
  delay(50);
}

