int vertPin = 5;
int horizPin = 6;
int selPin = 7;


void setup() {
  // initialize the digital pin as an output.
  // Pin 13: Arduino has an LED connected on pin 13
  // Pin 11: Teensy 2.0 has the LED on pin 11
  // Pin 6: Teensy++ 2.0 has the LED on pin 6
  pinMode(11, OUTPUT);
  
  pinMode(vertPin, INPUT);
  pinMode(horizPin, INPUT);
  pinMode(selPin, INPUT);
}

int dly = 1;

void loop() {
  digitalWrite(11, HIGH);   // set the LED on
  //delay(dly);              // wait for a second
  digitalWrite(11, LOW);    // set the LED off
  delay(dly);              // wait for a second
}
