
/*** ENCODER ***/
int aPin = 3;  // Encoder A pin, D3 is external interrupt 1
int bPin = 2;  // Encoder B pin, D2 is external interrupt 0
#include <Encoder.h>
Encoder myEnc(bPin, aPin);
int encoderSteps = 153;
long oldPosition = -999;
long newPosition = 50;
int encoderMode = 2;
int encoderModeMax = 2;
int encoderModeValues[3] = {100, 100, 100};

/*** BUTTON ***/
int swhPin = 4;  // Encoder's switch pin
long lastButtonPress = 1000000000;
volatile int buttonPressed = 1;
long buttonPressTimeout = 100;

/*** LEDS ***/
#include "FastLED.h"
#define NUM_LEDS 153
#define DATA_PIN 11
#define CLOCK_PIN 13
CRGB leds[NUM_LEDS];
CRGB currentColor = CRGB::Blue;
int currentHue = 1;
int currentBrightness = 255;

/*** TIME ***/
#include <Time.h>

void setup()
{
  Serial.begin(9600);
  setupButton();
  setupRtc();
  FastLED.addLeds<WS2801, DATA_PIN, CLOCK_PIN, RBG>(leds, NUM_LEDS);
}

void setupButton()
{
  lastButtonPress = 0;
  buttonPressed = 0;
  encoderMode = 0;
  pinMode(swhPin, INPUT);
  attachInterrupt(swhPin, buttonPress, RISING);
}

void setupRtc()
{
  setSyncProvider(getTeensy3Time);
  unsigned long t = 1401393985 + 30;
  Teensy3Clock.set(t);
  setTime(t);
}

time_t getTeensy3Time()
{
  return Teensy3Clock.get();
}

void loop()
{
  int queueEncoderHandler = 0;
  if (buttonPressed == 1) {
    onButtonPress();
    queueEncoderHandler = 1;
  }
  
  newPosition = min(max(myEnc.read(), 0), encoderSteps);

  // Reset internal encoder counter
  if (newPosition == 0 || newPosition == encoderSteps) {
    myEnc.write(newPosition);
  }
  
  // Call program on encoder move
  if (newPosition != oldPosition || queueEncoderHandler) {
    oldPosition = newPosition;    
    onEncoderChange();
  }
  
  delay(70);
}

void onEncoderChange()
{
  Serial.println(newPosition);
  encoderModeMax = 2;
  
  float percent = (float) newPosition / encoderSteps;
  
  switch(encoderMode) {
    case 0:
      return bargraph(percent);
    case 1:
      return cycleColor(percent);
    case 2:
      return changeBrightness(percent);
    default:
      return bargraph(percent);
  }
}

void buttonPress()
{  
  buttonPressed = 1;
}

void onButtonPress()
{
  buttonPressed = 0;
  
  if (millis() - lastButtonPress < buttonPressTimeout) {
    //Serial.println("Press rejected");
    return;
  }
  lastButtonPress = millis();  
  
  // Increment encoder mode limiting to encoderModeMax
  encoderMode = (encoderMode + 1) % (encoderModeMax + 1);  
  
  Serial.println(encoderModeMax);
  Serial.print("Button mode: ");
  Serial.println(encoderMode);
  buttonPressed = 0;
  
  /*** JUST DO IT ***/
  return;
  
  
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

void bargraph(float percent)
{
  Serial.print("Bargraph ");
  int lightUp = round(NUM_LEDS * percent);
  Serial.print(lightUp);
  for(int dot = 0; dot < NUM_LEDS; dot++) { 
      if (dot < lightUp) {
            leds[dot] = currentColor;
      } else {
            leds[dot] = CRGB::Black;
      }
    }    

  FastLED.show();
  Serial.println("");
}

void cycleColor(float percent)
{
  currentHue = round(percent * 255);
  currentColor = CHSV(currentHue, currentBrightness, 255);  
  bargraph(1.0);
}

void changeBrightness(float percent)
{
  currentBrightness = round(percent * 255);
  currentColor = CHSV(currentHue, 255, currentBrightness);
  bargraph(1.0);
}
  

