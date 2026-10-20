const int soundAnalogPin = A0;   // sensor AO
const int greenLed = 8;          // sound
const int redLed = 7;            // quiet
const int threshold = 200;       // quiet is about 30, a clap goes above 400
const unsigned long holdTime = 300;   // stay "sound" 0.3s after the last loud sample

unsigned long lastSound = 0;
bool hearing = false;

void showState(bool sound) {
  digitalWrite(greenLed, sound ? HIGH : LOW);
  digitalWrite(redLed, sound ? LOW : HIGH);
  Serial.println(sound ? "Sound  GREEN ON / RED OFF" : "Quiet  GREEN OFF / RED ON");
}

void setup() {
  pinMode(greenLed, OUTPUT);
  pinMode(redLed, OUTPUT);
  Serial.begin(9600);
  showState(false);              // start quiet: red on
}

void loop() {
  if (analogRead(soundAnalogPin) > threshold) {
    lastSound = millis();
  }

  bool now = lastSound != 0 && millis() - lastSound < holdTime;
  if (now != hearing) {          // update the LEDs only when the state changes
    hearing = now;
    showState(hearing);
  }
}
