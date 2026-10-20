// Floating test: a driven pin keeps its value with the pull-up on, a floating pin jumps to HIGH/1023
void window(const char *tag) {
  int lo = 1023, hi = 0, doHigh = 0, n = 0, edges = 0, last = -1;
  unsigned long start = millis();
  while (millis() - start < 200) {
    int v = analogRead(A0);
    if (v < lo) lo = v;
    if (v > hi) hi = v;
    int d = digitalRead(2);
    if (d) doHigh++;
    if (last >= 0 && d != last) edges++;
    last = d;
    n++;
  }
  Serial.print(tag); Serial.print(' ');
  Serial.print(lo); Serial.print(' '); Serial.print(hi); Serial.print(' ');
  Serial.print(doHigh); Serial.print(' '); Serial.print(n); Serial.print(' ');
  Serial.println(edges);
}

void setup() {
  Serial.begin(115200);
}

void loop() {
  pinMode(2, INPUT); pinMode(A0, INPUT);
  delay(20);
  window("PLAIN");
  pinMode(2, INPUT_PULLUP); pinMode(A0, INPUT_PULLUP);
  delay(20);
  window("PULLUP");
}
