const int buttonPin = 2;
const int ledPin = 13;

bool ledState = false;
bool buttonState = HIGH;      // stable (debounced) state
bool lastReading = HIGH;
unsigned long lastChange = 0;

void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP);
}

void loop() {
  bool reading = digitalRead(buttonPin);

  if (reading != lastReading) {
    lastChange = millis();      // signal is bouncing, restart timer
  }

  if (millis() - lastChange > 50 && reading != buttonState) {
    buttonState = reading;
    if (buttonState == LOW) {   // pressed
      ledState = !ledState;     // toggle
      digitalWrite(ledPin, ledState);
    }
  }

  lastReading = reading;
}
