const int redPin = 10;
const int yellowPin = 9;
const int greenPin = 8;

void setLights(bool red, bool yellow, bool green) {
  digitalWrite(redPin, red);
  digitalWrite(yellowPin, yellow);
  digitalWrite(greenPin, green);
}

void setup() {
  pinMode(redPin, OUTPUT);
  pinMode(yellowPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
}

void loop() {
  setLights(LOW, LOW, HIGH);   // green
  delay(5000);

  setLights(LOW, HIGH, LOW);   // yellow
  delay(2000);

  setLights(HIGH, LOW, LOW);   // red
  delay(5000);
}
