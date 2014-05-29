int enablePin = 0;
int dirPin = 1;
int stepPin = 11;

int joyXPin = A0;
int joyYPin = A1;

int joyXValue = 0;

void setup()
{
  pinMode(enablePin, OUTPUT);
  pinMode(dirPin, OUTPUT);
  pinMode(stepPin, OUTPUT);
  pinMode(joyXPin, INPUT);
  pinMode(joyYPin, INPUT);
  
  digitalWrite(enablePin, LOW);
  digitalWrite(dirPin, HIGH);  
  
  Serial.begin(9600);
}

void doSteps(int steps = 10, int tDelay = 100)
{
  int stepDelay = max(1, 11 - abs(joyXValue));
  tDelay = max(2, stepDelay);
  
  for (int i = 0; i < steps; i++) {
    digitalWrite(stepPin, HIGH);
    delay(tDelay / 2);
    digitalWrite(stepPin, LOW);
    delay(tDelay / 2);
  }
}

void loop()
{
  doSteps(10, 10);
  getJoystick();
}


void getJoystick()
{
  int joystick_x;
  int joystick_y;
  joystick_x = map(analogRead(joyXPin), 0, 1023, 0, 20) - 10;
  joystick_y = map(analogRead(joyYPin), 0, 1023, 0, 19) - 9;
  
  joyXValue = joystick_x;
  
  if (1) {
    Serial.print("x  ");
    Serial.print(joystick_x);
    Serial.print(" / y ");
    Serial.println(joystick_y);
  }
  
  if (abs(joystick_x) < 2) {
    setEnabled(0);
  } else {
    setDir(joystick_x);
    setEnabled(1);
  }
}

void setEnabled(int enabled)
{
  digitalWrite(enablePin, enabled ? LOW : HIGH);
}

void setDir(int x)
{
  if (x > 0) {
    digitalWrite(dirPin, HIGH);
  } else {
    digitalWrite(dirPin, LOW);
  }
}
