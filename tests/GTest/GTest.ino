// g segment finder: D8 for 2s (LED off), then D9 for 2s (LED on), repeat
const int ledPin = 11;

void setup() {
  for (int p = 2; p <= 9; p++) { pinMode(p, OUTPUT); digitalWrite(p, LOW); }
  pinMode(ledPin, OUTPUT);
}

void loop() {
  digitalWrite(9, LOW);  digitalWrite(8, HIGH); digitalWrite(ledPin, LOW);
  delay(2000);
  digitalWrite(8, LOW);  digitalWrite(9, HIGH); digitalWrite(ledPin, HIGH);
  delay(2000);
}
