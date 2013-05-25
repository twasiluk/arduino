int pinUp = A0;
int pinRight = A1;
int pinDown = A2;
int pinLeft = A3;
int ledPin = 11;

void setup() {
  Serial.begin(9600);
  pinMode(pinUp, INPUT);
  pinMode(pinRight, INPUT);
  pinMode(pinDown, INPUT);
  pinMode(pinLeft, INPUT);
  pinMode(ledPin, OUTPUT);
}

int getPressedPin()
{
  int v = 0;
  
  v = digitalRead(pinUp);
  if (v) return pinUp;
  
  v = digitalRead(pinRight);
  if (v) return pinRight;
 
  v = digitalRead(pinDown);
  if (v) return pinDown;
  
  v = digitalRead(pinLeft);
  if (v) return pinLeft;
  
  return 0;
}

void loop()
{
  int pressed = getPressedPin();
  Serial.println(pressed);
  if (pressed) {
    moveOnPress(pressed);
  }
  delay(5);
}

void moveOnPress(int pressed)
{
  if (pressed == pinUp) {
    Mouse.move(0, -2);
    Keyboard.print("Hello World ");
  } else if (pressed == pinRight) {
    Mouse.move(2, 0);
  } else if (pressed == pinDown) {
    Mouse.move(0, 2);
  } else if (pressed == pinLeft) {
    Mouse.move(-2, 0);
  }  
  delay(10);
}


void triangle()
{
  int i;
  for (i=0; i<40; i++) {
    Mouse.move(2, -1);
    delay(25);
  }
  for (i=0; i<40; i++) {
    Mouse.move(2, 2);
    delay(25);
  }
  for (i=0; i<40; i++) {
    Mouse.move(-4, -1);
    delay(25);
  }
}
