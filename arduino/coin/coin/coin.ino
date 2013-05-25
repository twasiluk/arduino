// include the library code:
#include <LiquidCrystal.h>

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

// This line defines a "Uart" object to access the serial port
HardwareSerial Uart = HardwareSerial();

double total = 0;

int soundPin = 18;

void setup()
{
  Serial.begin(9600); //USB
  Uart.begin(4800);
  
  pinMode(soundPin, OUTPUT);
  digitalWrite(soundPin, HIGH);
  
  // set up the LCD's number of columns and rows: 
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.print("Skarbonka Tymka");
}

void loop()
{
  int incomingByte;
  if (Uart.available() > 0) {
    
    digitalWrite(soundPin, LOW);
    delay(700);
    digitalWrite(soundPin, HIGH);
    
    incomingByte = Uart.read();
    Serial.print("UART received: ");
    Serial.println(incomingByte, DEC);
    total = total + incomingByte * 0.1;
  }
  
  // set the cursor to column 0, line 1
  lcd.setCursor(0, 1);
  // print the number of seconds since reset:
  int aInt = floor(total);
  int aDec = int(total * 100) % 100;
  lcd.print(aInt);
  lcd.print(" zl ");
  lcd.print(aDec);
  lcd.print(" gr ");
}
