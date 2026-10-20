// 1-digit 7-segment counter: each button press adds 1 (0 -> 9 -> 0), the LED flashes on every press
const int segPins[7] = {2, 3, 4, 5, 6, 7, 8};   // a, b, c, d, e, f, g
const int buttonPin = 10;
const int ledPin = 11;

const bool COMMON_ANODE = false;   // set true for a common-anode display

// bit order: a b c d e f g (bit 0 = a)
const byte DIGITS[10] = {
  0b0111111,  // 0
  0b0000110,  // 1
  0b1011011,  // 2
  0b1001111,  // 3
  0b1100110,  // 4
  0b1101101,  // 5
  0b1111101,  // 6
  0b0000111,  // 7
  0b1111111,  // 8
  0b1101111   // 9
};

int number = 0;
bool buttonState = HIGH;
bool lastReading = HIGH;
unsigned long lastChange = 0;
unsigned long ledOnAt = 0;

void showDigit(int n) {
  for (int i = 0; i < 7; i++) {
    bool on = DIGITS[n] & (1 << i);
    digitalWrite(segPins[i], COMMON_ANODE ? !on : on);
  }
}

void setup() {
  for (int i = 0; i < 7; i++) pinMode(segPins[i], OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
  showDigit(number);
}

void loop() {
  bool reading = digitalRead(buttonPin);
  if (reading != lastReading) lastChange = millis();

  if (millis() - lastChange > 50 && reading != buttonState) {
    buttonState = reading;
    if (buttonState == LOW) {          // pressed
      number = (number + 1) % 10;
      showDigit(number);
      digitalWrite(ledPin, HIGH);
      ledOnAt = millis();
      Serial.println(number);
    }
  }
  lastReading = reading;

  if (ledOnAt && millis() - ledOnAt > 200) {   // LED flash lasts 0.2s
    digitalWrite(ledPin, LOW);
    ledOnAt = 0;
  }
}
