const int potPin = A0;
const int ledPin = 9;          // PWM pin (~)

void setup() {
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  int potValue = analogRead(potPin);              // 0 ~ 1023
  int brightness = map(potValue, 0, 1023, 0, 255); // 0 ~ 255

  analogWrite(ledPin, brightness);

  Serial.print("pot: ");
  Serial.print(potValue);
  Serial.print("  brightness: ");
  Serial.println(brightness);

  delay(100);
}
