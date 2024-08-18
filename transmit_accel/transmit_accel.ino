#include <Wire.h>
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

int ADXL345 = 0x53;
float X_out, Y_out, Z_out;

RF24 radio(7, 8);
const byte address[6] = "00001";

void setup() {
  Wire.begin();
  Wire.beginTransmission(ADXL345);
  Wire.write(0x2D);
  Wire.write(8);
  Wire.endTransmission();

  // Radio Setup
  radio.begin();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MIN);
  radio.stopListening();
}

void loop() {
  // Read X, Y, and Z Accel
  Wire.beginTransmission(ADXL345);
  Wire.write(0x32);
  Wire.endTransmission(false);
  Wire.requestFrom(ADXL345, 6, true);
  X_out = ( Wire.read() | Wire.read() << 8);
  X_out = X_out/256;
  Y_out = ( Wire.read() | Wire.read() << 8);
  Y_out = Y_out/256;
  Z_out = ( Wire.read() | Wire.read() << 8);
  Z_out = Z_out/256;

  const float accel[3] = {X_out, Y_out, Z_out};
  radio.write(accel, sizeof(accel));
  delay(250);
}
