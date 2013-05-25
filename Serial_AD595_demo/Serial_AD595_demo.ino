#include <AD595.h>
#include <TimerOne.h>

AD595 thermocouple;

int relayPin = 9;
int relayState = LOW;
unsigned long time = 0;
volatile float temperature = 0;
volatile unsigned long timerCount = 0;
int preHeatTemp = 60;

void setup()
{
  Serial.begin(9600);
  thermocouple.init(20);  
  //Serial.println("AD595 test");
  // wait for AD595 chip to stabilize  
  pinMode(relayPin, OUTPUT);
  digitalWrite(relayPin, LOW);

  delay(500);
  Timer1.initialize(100000);
  Timer1.attachInterrupt(getTemp);
  
  relayState = HIGH;
  digitalWrite(relayPin, relayState);
}

void loop()
{
  if (timerCount == 0) {  
    Serial.print(millis()/1000);
    Serial.print(",");
    Serial.println(temperature);    
    
    if (temperature > 245 && relayState == HIGH) {
      digitalWrite(relayPin, LOW);
      relayState = LOW;
      //Serial.println("oven off");
    }
    timerCount = 1;
  }
 
  //relayState = (relayState == LOW ? HIGH : LOW);
  //digitalWrite(relayPin, relayState);
 
  delay(10);
}

void getTemp()
{
  timerCount = (timerCount + 1) % 10;
  temperature = (temperature * 5 + float(thermocouple.measure(TEMPC))) / 6;
  //temperature = float(thermocouple.measure(TEMPC));
}
