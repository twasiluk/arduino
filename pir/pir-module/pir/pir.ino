const int analogPin = A0;
int ledPin = 12;
int alarmCounter = 0;

void setup() {
//  analogReference(INTERNAL); // 1.1V
  Serial.begin(9600);
  pinMode(analogPin, INPUT);
}

void loop() {
  detectChange();
}

void detectChange()
{
  int v = analogRead(analogPin);
  Serial.println(v);
  delay(100);
}

void alertOn()
{
  //Serial.print("Alert on at "); Serial.println(millis());
  digitalWrite(ledPin, 1);
  alarmCounter = 10;
}

void alertOff()
{
  if (alarmCounter == 0) {
    digitalWrite(ledPin, 0);
  } else {
    alarmCounter--;
  }
}

