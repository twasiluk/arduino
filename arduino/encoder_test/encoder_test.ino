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

void setup()
{
  lastButtonPress = 0;
  FastLED.addLeds<WS2801, DATA_PIN, CLOCK_PIN, RBG>(leds, NUM_LEDS);
  Serial.begin(9600);
  pinMode(swhPin, INPUT);
  attachInterrupt(swhPin, buttonPress, RISING);
  myEnc.write(round(encoderSteps / 2));
}

long oldPosition = -999;
long newPosition = 0;

void loop()
{
  if (buttonPressed == 1) {
    onButtonPress();
  }
  
  newPosition = min(max(myEnc.read(), 0), encoderSteps);
  
  if (newPosition != oldPosition) {
    myEnc.write(newPosition);
    oldPosition = newPosition;
    Serial.println(newPosition);
    encoderFunction(encoderMode, (float) newPosition / NUM_LEDS);      
  }
  

}

void onButtonPress()
{
  Serial.println();
  Serial.print("Button mode: ");
  Serial.println(encoderMode);
  buttonPressed = 0;
  
  int prevMode = getPreviousEncoderMode();
  
  /* Save last mode's encoder state */
  encoderModeValues[prevMode] = newPosition;
  Serial.print("Saving encoder for mode:");
  Serial.print(prevMode);
  Serial.print(" position:");
  Serial.println(newPosition);
  
  /* Load encoder state for newly loaded mode */
  myEnc.write(encoderModeValues[encoderMode]);
  Serial.print("Loading encoder for mode:");
  Serial.print(encoderMode);
  Serial.print(" position:");
  Serial.println(encoderModeValues[encoderMode]);
}

int getPreviousEncoderMode()
{
  if (encoderMode > 0) {
      return encoderMode - 1;
  }
  return encoderModeMax;
}

void encoderFunction(int mode, float percent)
{
  encoderModeMax = 2;
  
  switch(encoderMode) {
    default:
      bargraph(percent);      
      //delay(500);
      break;
  }
}

void bargraph(float percent)
{
  noInterrupts();
  int lightUp = round(percent * NUM_LEDS);
  //Serial.println(NUM_LEDS);  
    for(int dot = 0; dot < NUM_LEDS; dot++) { 
      if (dot < lightUp) {
            leds[dot] = currentColor;
      } else {
            leds[dot] = CRGB::Black;
      }
    }    
    //leds[0] = currentColor;
    FastLED.show();
    interrupts();
}

void setHue(float percent)
{
}

void setSaturation(float percent)
{
}

void buttonPress()
{  
  if (millis() - lastButtonPress < buttonPressTimeout) {
    return;
  }
  lastButtonPress = millis();
  buttonPressed = 1;
  encoderMode = (encoderMode + 1) % (encoderModeMax + 1);  
  
  switch (currentColor) {
      case CRGB::Blue:
        currentColor = CRGB::Green; break;      
      case CRGB::Green:
        currentColor = CRGB::Red; break;      
      case CRGB::Red:
        currentColor = CRGB::Orange; break;
      case CRGB::Orange:
        currentColor = CRGB::Purple; break;
      default:
        currentColor = CRGB::Blue; break;
    }
}

void buttonPressColor()
{
  //long elapsedMs = timeElapsed - lastButtonPress;
  //Serial.println(elapsedMs);
  
  if (millis() - lastButtonPress > buttonPressTimeout) {
    lastButtonPress = millis();
      switch (currentColor) {
      case CRGB::Blue:
        currentColor = CRGB::Green; break;      
      case CRGB::Green:
        currentColor = CRGB::Red; break;      
      case CRGB::Red:
        currentColor = CRGB::Orange; break;
      case CRGB::Orange:
        currentColor = CRGB::Purple; break;
      default:
        currentColor = CRGB::Blue; break;
    }
  }
  

}

