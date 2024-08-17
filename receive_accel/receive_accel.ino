#include <RF24.h>
#include <nRF24L01.h>
#include <SPI.h>

RF24 radio(7, 8);
const byte address[6] = "00001";

void setup() {
  Serial.begin(9600);
  radio.begin();
  radio.openReadingPipe(1, address);
  radio.setPALevel(RF24_PA_LOW);
  radio.startListening();
}

void loop() {
  if (radio.available()) {
    const float accel[3] = {};
    radio.read(accel, sizeof(accel));
    Serial.print(accel[0]);
    Serial.print(",");
    Serial.print(accel[1]);
    Serial.print(",");
    Serial.println(accel[2]);
  }
}
