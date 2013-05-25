unsigned lightCutoff = 0;

void setup()
{
  Serial.begin(9600);
  Serial.println("start");
  addLightTime(120);
}

void loop()
{
  Serial.println(getLightTime());
  delay(100);
}

void addLightTime(int seconds)
{
  unsigned now = millis();
  if (now > lightCutoff) {
    // light cutoff has passed. reset it with "now"
    lightCutoff = now + seconds * 1000;
  } else {
    // light is still on
    lightCutoff = lightCutoff + seconds * 1000;
  }
}

int getLightTime()
{
  unsigned now = millis();
  if (now > lightCutoff) {
    return 0;
  }
  return floor((lightCutoff - millis()) / 1000);
}
