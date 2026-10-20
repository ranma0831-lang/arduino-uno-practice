#include <Adafruit_NeoPixel.h>

const int PIXEL_PIN = 6;
const int NUM_PIXELS = 8;

Adafruit_NeoPixel strip(NUM_PIXELS, PIXEL_PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  strip.begin();
  strip.setBrightness(50);   // 0~255, keep it low on USB power
  strip.show();              // all off
}

void loop() {
  for (int i = 0; i < NUM_PIXELS; i++) {
    strip.clear();
    strip.setPixelColor(i, strip.Color(0, 150, 255));
    strip.show();
    delay(100);
  }
}
