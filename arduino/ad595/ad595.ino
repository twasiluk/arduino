int ledPin = 11;
int tempPin = 13;
float sensorValue;

void setup()
{
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
  pinMode(tempPin, INPUT);  
}

void loop() {
  sensorValue = analogRead(tempPin); 
  Serial.println(sensorValue);
  
  digitalWrite(ledPin, HIGH);   // set the LED on
  delay(1000);              // wait for a second
  digitalWrite(ledPin, LOW);    // set the LED off
  delay(1000);              // wait for a second
}
