#include <SPI.h>
#include <MFRC522.h>

const int SS_PIN = 10;     // RC522 SDA
const int RST_PIN = 9;     // RC522 RST
const int GREEN_LED = 7;   // ALLOW
const int RED_LED = 6;     // DENY

MFRC522 rfid(SS_PIN, RST_PIN);

// Allowed card UIDs. Scan a card, copy the UID from the Serial Monitor, and put it here.
const byte ALLOWED[][4] = {
  { 0xDE, 0xAD, 0xBE, 0xEF },   // example UID - replace with your card
};
const int ALLOWED_COUNT = sizeof(ALLOWED) / sizeof(ALLOWED[0]);

bool isAllowed(const MFRC522::Uid &uid) {
  if (uid.size != 4) return false;
  for (int i = 0; i < ALLOWED_COUNT; i++) {
    if (memcmp(uid.uidByte, ALLOWED[i], 4) == 0) return true;
  }
  return false;
}

void printUid(const MFRC522::Uid &uid) {
  Serial.print("UID:");
  for (byte i = 0; i < uid.size; i++) {
    Serial.print(uid.uidByte[i] < 0x10 ? " 0" : " ");
    Serial.print(uid.uidByte[i], HEX);
  }
}

void setup() {
  pinMode(GREEN_LED, OUTPUT);
  pinMode(RED_LED, OUTPUT);
  Serial.begin(9600);
  SPI.begin();
  rfid.PCD_Init();
  Serial.println("Scan a card...");
}

void loop() {
  if (!rfid.PICC_IsNewCardPresent() || !rfid.PICC_ReadCardSerial()) return;

  printUid(rfid.uid);

  if (isAllowed(rfid.uid)) {
    Serial.println("  -> ALLOW");
    digitalWrite(GREEN_LED, HIGH);
  } else {
    Serial.println("  -> DENY");
    digitalWrite(RED_LED, HIGH);
  }

  delay(1500);
  digitalWrite(GREEN_LED, LOW);
  digitalWrite(RED_LED, LOW);

  rfid.PICC_HaltA();        // stop reading the same card again
  rfid.PCD_StopCrypto1();
}
