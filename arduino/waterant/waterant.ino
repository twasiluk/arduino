int relayPin = 2;

void setup()
{
  pinMode(relayPin, OUTPUT);  
}

void loop()
{
  digitalWrite(relayPin, HIGH);
  delay(0.5 * 3600 * 1000);
  digitalWrite(relayPin, LOW);
  delay(6 * 3600 * 1000);
}
