// Teensy 3.0
int ledPin = 13;

// Pin definitions - Encoder:
int aPin = 3;  // Encoder A pin, D3 is external interrupt 1
int bPin = 2;  // Encoder B pin, D2 is external interrupt 0
int redPin = 0;  // Encoder's red LED - D5 is PWM enabled
int bluPin = 0;  // Encoder's blue LED- D6 is PWM enabled
int grnPin = 0;  // Encoder's green LED - D9 is PWM enabled
int swhPin = 4;  // Encoder's switch pin

// Pin definitions - Shift registers:
int enPin = 0;  // Shift registers' Output Enable pin
int latchPin = 0;  // Shift registers' rclk pin
int clkPin = 0;  // Shift registers' srclk pin
int clrPin = 0;  // shift registers' srclr pin
int datPin;  // shift registers' SER pin

#include <Encoder.h>
Encoder myEnc(bPin, aPin);

int encoderSteps = 153;

#include "FastLED.h"
#define NUM_LEDS 153
#define DATA_PIN 11
#define CLOCK_PIN 13
CRGB leds[NUM_LEDS];

int currentColor = CRGB::Blue;
volatile long lastButtonPress = 1000000000;
long buttonPressTimeout = 200;
volatile int buttonPressed = 1;

/*
* Encoder modes:
* 0. Bargraph
* 1. Color hue
* 2. Saturation
*/
volatile int encoderMode = 0;
volatile int encoderModeMax = 2;
int encoderModeValues[3] = {100, 1, 1};

long oldPosition = -999;
long newPosition = 153;

void setup()
{
  lastButtonPress = 0;
  FastLED.addLeds<WS2801, DATA_PIN, CLOCK_PIN, RBG>(leds, NUM_LEDS);
  Serial.begin(9600);
  pinMode(swhPin, INPUT);
  //attachInterrupt(swhPin, buttonPress, RISING);
  myEnc.write(round(encoderSteps / 2));
}

void loop()
{
  /*
  if (buttonPressed == 1) {
    onButtonPress();
  }
  */
  
  newPosition = min(
    max(myEnc.read(), 0),
    encoderSteps
  );
  
  
  if (newPosition != oldPosition) {    
    oldPosition = newPosition;
    myEnc.write(newPosition);
    Serial.println(newPosition);
    bargraph(0.5);
  }
  
  delay(100);
}



void bargraph(float percent)
{
  int lightUp = round(percent * NUM_LEDS);
  //Serial.println("Lightup led amount: ");
  //Serial.println(NUM_LEDS);
  
    for(int dot = 0; dot <= NUM_LEDS; dot++) { 
      if (dot <= lightUp) {
            leds[dot] = currentColor;
      } else {
            leds[dot] = CRGB::Black;
      }
    }
    FastLED.show();
}

