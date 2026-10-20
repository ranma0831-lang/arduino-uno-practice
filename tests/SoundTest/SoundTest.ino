const int doPin = 2;
const int aoPin = A0;

void setup() {
  pinMode(doPin, INPUT);
  Serial.begin(115200);
}

void loop() {
  // sample for 50ms and report the range, so short claps are not missed
  int lo = 1023, hi = 0, doHigh = 0, n = 0;
  unsigned long start = millis();
  while (millis() - start < 50) {
    int v = analogRead(aoPin);
    if (v < lo) lo = v;
    if (v > hi) hi = v;
    if (digitalRead(doPin) == HIGH) doHigh++;
    n++;
  }
  Serial.print(lo); Serial.print(' ');
  Serial.print(hi); Serial.print(' ');
  Serial.print(doHigh); Serial.print(' ');
  Serial.println(n);
}
