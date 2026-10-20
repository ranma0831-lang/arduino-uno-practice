// Lights D2..D8 one at a time (1.5s each). The LED on D11 is on during step 1 (D2).
const int segPins[7] = {2, 3, 4, 5, 6, 7, 8};
const int ledPin = 11;

void setup() {
  for (int i = 0; i < 7; i++) pinMode(segPins[i], OUTPUT);
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  for (int i = 0; i < 7; i++) {
    for (int j = 0; j < 7; j++) digitalWrite(segPins[j], j == i);
    digitalWrite(ledPin, i == 0);
    Serial.print("step ");
    Serial.print(i + 1);
    Serial.print(": D");
    Serial.println(segPins[i]);
    delay(1500);
  }
}
