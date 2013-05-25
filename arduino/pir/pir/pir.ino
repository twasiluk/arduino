const int analogPin = 0;
int ledPin = 12;
float maxThreshold = 0;
float maxJitter = 0;
int alarmCounter = 0;

float avg = 500;

void setup() {
  analogReference(INTERNAL); // 1.1V
  Serial.begin(9600);
  avg = maxThreshold = analogRead(analogPin);
}

void loop() {
  //Serial.println(analogRead(analogPin)); delayMicroseconds(2);  
  //minMax();
  detectChange();
}

void detectChange()
{
  int v = analogRead(analogPin);
  float delta = abs(v - avg) / avg;
// 0.003 too small
  if (delta > 0.0028) {
    alertOn();    
  } else {
    alertOff();
  }
  avg = (avg * 31 + v) / 32;  
  //delayMicroseconds(50000);
  //delay(50);

  if (1) {
    Serial.print(" d=");
    Serial.print(delta);  
    Serial.print(" avg=");
    Serial.println(avg);   
  }
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

void minMax()
{  
  int mn = 1024;     // mn only decreases
  int mx = 0;        // mx only increases

  // Perform 10000 reads. Update mn and mx for each one.
  for (int i = 0; i < 100; ++i) {
    int val = analogRead(analogPin);
    mn = min(mn, val);
    mx = max(mx, val);
    delayMicroseconds(3);
    
  }

  float jitter = abs(maxThreshold - mx);
  
  if (jitter > 1) {
    alertOn();
  } else {
    alertOff();
  }
  
  //maxThreshold = (maxThreshold * 9 + mx) / 10;
  maxThreshold = mx;
  maxJitter = (maxJitter * 9 + jitter) / 10;

  // Send min, max and delta over Serial
  if (1) {
    Serial.print(" jitter=");
    Serial.print(jitter);  
    Serial.print(" maxJi=");
    Serial.print(maxJitter);  
    Serial.print(" M=");
    Serial.print(mx);  
    Serial.print(" mT=");
    Serial.print(maxThreshold);  
    Serial.println();
  }
}

