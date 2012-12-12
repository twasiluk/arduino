const int analogPin = 0;

void setup() {
  Serial.begin(9600); 
}

void loop() {
  Serial.println(analogRead(A0));
  delay(2);  
}

void minMax()
{
  
  int mn = 1024;     // mn only decreases
  int mx = 0;        // mx only increases

  // Perform 9999 reads. Update mn and mx for each one.
  for (int i = 0; i < 9999; ++i) {
    int val = analogRead(analogPin);
    mn = min(mn, val);
    mx = max(mx, val);
  }

  // Send min, max and delta over Serial
  Serial.print("m=");
  Serial.print(mn);  
  Serial.print(" M=");
  Serial.print(mx);  
  Serial.print(" D=");
  Serial.print(mx-mn);  
  Serial.println();  
}

