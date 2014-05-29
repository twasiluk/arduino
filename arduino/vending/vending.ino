int vertPin = A1;
int horizPin = A2;
int selPin = 7;
int dirPin = 6;
int enablePin = 5;


void setup() {
  // initialize the digital pin as an output.
  // Pin 13: Arduino has an LED connected on pin 13
  // Pin 11: Teensy 2.0 has the LED on pin 11
  // Pin 6: Teensy++ 2.0 has the LED on pin 6
  pinMode(11, OUTPUT);
  
  pinMode(vertPin, INPUT);
  pinMode(horizPin, INPUT);
  pinMode(selPin, INPUT);
  digitalWrite(selPin, HIGH);
  
  pinMode(dirPin, OUTPUT);
  digitalWrite(dirPin, HIGH);
  
  pinMode(enablePin, OUTPUT);
  digitalWrite(enablePin, HIGH);
  
  Serial.begin(9600);
}

int dly = 100;

void loop() {
  
  int joystick_x;
  int joystick_y;
  joystick_x = map(analogRead(vertPin), 0, 1023, 1, 20);
  joystick_y = map(analogRead(horizPin), 0, 1023, 1, 20);
  Serial.print("x  ");
  Serial.print(joystick_x);
  Serial.print(" / Y ");
  Serial.println(joystick_y);
  
  if (joystick_x < 6) {
    digitalWrite(dirPin, HIGH);
    digitalWrite(enablePin, LOW);
  } else if (joystick_x > 14) {
    digitalWrite(dirPin, LOW);
    digitalWrite(enablePin, LOW);
  } else {
    digitalWrite(enablePin, HIGH);
  }
  
  //dly = max(1, 9 - abs(round(10 - joystick_x)));
  
  /*
  int select = digitalRead(selPin);
  if (select == 0) {
      return;
  }
  */
  
  digitalWrite(11, HIGH);   // set the LED on
  delay(dly);              // wait for a second
  digitalWrite(11, LOW);    // set the LED off
  delay(dly);              // wait for a second
}
