const int soundAnalogPin = A0;   // sensor AO
const int ledPin = 8;
const int threshold = 200;       // quiet is about 30, a clap goes above 400
const unsigned long holdTime = 1000;  // keep the LED on 1s after the last sound

unsigned long lastSound = 0;
bool ledOn = false;

void setup() {
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  int level = analogRead(soundAnalogPin);

  if (level > threshold) {
    lastSound = millis();        // every loud sample restarts the 1s timer
    if (!ledOn) {
      ledOn = true;
      digitalWrite(ledPin, HIGH);
      Serial.print("Sound! level=");
      Serial.print(level);
      Serial.println("  LED ON");
    }
  }

  if (ledOn && millis() - lastSound > holdTime) {
    ledOn = false;
    digitalWrite(ledPin, LOW);
    Serial.println("Quiet  LED OFF");
  }
}
