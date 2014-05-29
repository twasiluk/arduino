int led = 13;

// Pin definitions - Encoder:
int aPin = 3;  // Encoder A pin, D3 is external interrupt 1
int bPin = 2;  // Encoder B pin, D2 is external interrupt 0
int redPin = ;  // Encoder's red LED - D5 is PWM enabled
int bluPin = ;  // Encoder's blue LED- D6 is PWM enabled
int grnPin = ;  // Encoder's green LED - D9 is PWM enabled
int swhPin = ;  // Encoder's switch pin

// Pin definitions - Shift registers:
int enPin = ;  // Shift registers' Output Enable pin
int latchPin = ;  // Shift registers' rclk pin
int clkPin = ;  // Shift registers' srclk pin
int clrPin = ;  // shift registers' srclr pin
int datPin = ;  // shift registers' SER pin

// the setup routine runs once when you press reset:
void setup() {                
  // initialize the digital pin as an output.
  pinMode(led, OUTPUT);     
}

// the loop routine runs over and over again forever:
void loop() {
  digitalWrite(led, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(1000);               // wait for a second
  digitalWrite(led, LOW);    // turn the LED off by making the voltage LOW
  delay(1000);               // wait for a second
}
