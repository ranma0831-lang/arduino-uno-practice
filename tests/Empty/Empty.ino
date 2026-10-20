void setup() {
  for (int p = 2; p <= 13; p++) {
    if (p == 10) continue;   // button pin stays an input
    pinMode(p, OUTPUT);
    digitalWrite(p, LOW);
  }
}

void loop() {
}
