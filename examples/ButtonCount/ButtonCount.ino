const int buttonPin = 2;

int count = 0;
bool lastState = HIGH;

void setup() {
  pinMode(buttonPin, INPUT_PULLUP);
  Serial.begin(9600);
}

void loop() {
  bool state = digitalRead(buttonPin);

  if (lastState == HIGH && state == LOW) {   // the moment it is pressed
    count++;
    Serial.println(count);
  }

  lastState = state;
  delay(10);   // simple debounce
}
