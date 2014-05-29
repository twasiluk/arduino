#include <SPI.h>

//Add the SdFat Libraries
#include <SdFat.h>
#include <SdFatUtil.h>

//and the MP3 Shield Library
#include <SFEMP3Shield.h>

// include the library code:
#include <LiquidCrystal.h>

// Below is not needed if interrupt driven. Safe to remove if not using.
#if defined(USE_MP3_REFILL_MEANS) && USE_MP3_REFILL_MEANS == USE_MP3_Timer1
  #include <TimerOne.h>
#elif defined(USE_MP3_REFILL_MEANS) && USE_MP3_REFILL_MEANS == USE_MP3_SimpleTimer
  #include <SimpleTimer.h>
#endif

SdFat sd;
SFEMP3Shield MP3player;
bool useMp3 = true;

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(12, 11, 18, 19, 20, 21);

// This line defines a "Uart" object to access the serial port
HardwareSerial Uart = HardwareSerial(); // Teensy2 RX=7 TX=8

double total = 0;
int ledPin = 11;
unsigned long lightCutoff = 0;
int relayPin = 17;

void setup()
{
  uint8_t result; //result code from some function as to be tested at later time.
  pinMode(0, OUTPUT);
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, HIGH);  
  pinMode(relayPin, OUTPUT);
  digitalWrite(relayPin, LOW);
  
  Serial.begin(9600); //USB
  Serial.println("start");
  
  Uart.begin(4800);
  
  //Initialize the SdCard.
  if (useMp3) {
    if (!sd.begin(SD_SEL, SPI_HALF_SPEED)) sd.initErrorHalt();
    if (!sd.chdir("/")) sd.errorHalt("sd.chdir");

    //Initialize the MP3 Player Shield
    result = MP3player.begin();
    //check result, see readme for error codes.
    if(result != 0) {
      Serial.print(F("Error code: "));
      Serial.print(result);
      Serial.println(F(" when trying to start MP3 player"));
      if( result == 6 ) {
        Serial.println(F("Warning: patch file not found, skipping.")); // can be removed for space, if needed.
        Serial.println(F("Use the \"d\" command to verify SdCard can be read")); // can be removed for space, if needed.
      }
    }
  }

  // set up the LCD's number of columns and rows: 
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.print("Skarbonka Tymka");
  
  // Poczatkowe x sekund swiatla
  //addLightTime(15);
}

void loop()
{

// Below is only needed if not interrupt driven. Safe to remove if not using.
#if defined(USE_MP3_REFILL_MEANS) \
    && ( (USE_MP3_REFILL_MEANS == USE_MP3_SimpleTimer) \
    ||   (USE_MP3_REFILL_MEANS == USE_MP3_Polled)      )

  if (useMp3) { MP3player.available(); }
#endif

  int incomingByte;
  if (Uart.available() > 0) {
    incomingByte = Uart.read();
    
    if (incomingByte > 0) {
      Serial.print("UART received: ");
      Serial.println(incomingByte, DEC);
      total = total + incomingByte * 0.1;
      
      // Muzyczka
      if (useMp3) {
        MP3player.playTrack(getTrackForCoin(incomingByte));
      }
      
      // Swiatlo
      addLightTime(120);
    }
  }
  
  // set the cursor to column 0, line 1
  lcd.setCursor(0, 1);
  
  // print the number of seconds since reset:
  /*
  int aInt = floor(total);
  int aDec = int(total * 100) % 100;
  lcd.print(aInt);
  lcd.print(" zl ");
  lcd.print(aDec);
  lcd.print(" gr ");
  */
  
  int lightSecs = getLightTime();
  //Serial.println(lightSecs);
  //lcd.print(lightSecs);
  //lcd.println("     ");
  
  int aInt = floor(total);
  int aDec = int(total * 100) % 100;
  lcd.print(aInt);
  lcd.print(" zl ");
  lcd.print(aDec);
  lcd.print(" gr ");

  delay(150);
}

int getTrackForCoin(int coin)
{
    if (coin == 1) {
      return 1;
    } else if (coin == 2) {
      return 2;
    } else if (coin == 5) {
      return 3;
    } else if (coin == 10) {
      return 4;
    } else if (coin == 20) {
      return 5;
    } else if (coin == 50) {
      return 6;
    } else {
      return 7;
    }
}

void addLightTime(unsigned long secadd)
{
  unsigned long now = millis();
  if (now >= lightCutoff) {
    // light cutoff has passed. reset it with "now"
    lightCutoff = now + secadd * 1000;
  } else {
    // light is still on
    lightCutoff = lightCutoff + secadd * 1000;
  }
}

int getLightTime()
{
  unsigned long now = millis();
  if (now > lightCutoff) {
    return 0;
  }
  return (int) ((lightCutoff - now) / 1000);
}

