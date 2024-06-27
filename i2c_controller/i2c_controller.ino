#include <Wire.h>

// Wire
// SDA 4
// SCL 5

constexpr uint8_t kDeviceAddr = 0x55;

constexpr uint8_t kLedBPin = 20;
constexpr uint8_t kLedGPin = 19;
constexpr uint8_t kLedRPin = 18;

uint8_t cnt = 0;

void printHex(uint8_t h) {
  Serial.print("0x");
  Serial.print((h >> 4) & 0xF0, HEX);
  Serial.println(h & 0x0F, HEX);
}

void blinkHex(uint8_t h, uint8_t pin) {
  for (int i = 0; i < 8; i++) {
    digitalWrite(pin, !(h & 0x01));
    h = h >> 1;
    delay(20);
  }
  digitalWrite(pin, 1);
}

void setup() {
  pinMode(kLedBPin, OUTPUT);
  pinMode(kLedGPin, OUTPUT);
  pinMode(kLedRPin, OUTPUT);
  digitalWrite(kLedBPin, 1);
  digitalWrite(kLedGPin, 1);
  digitalWrite(kLedRPin, 1);
  Serial.begin(9600);
  Wire.begin();
}

void loop() {
  Serial.print("SENT: ");
  printHex(cnt);
  Wire.beginTransmission(kDeviceAddr); 
  Wire.write(cnt);
  Wire.endTransmission();
  blinkHex(cnt, kLedBPin);

  Wire.requestFrom(kDeviceAddr, 1);
  byte t = Wire.read();
  Serial.print("RECV: ");
  printHex(t);

  blinkHex(t, kLedGPin);

  cnt++;
  delay(1000);
}
