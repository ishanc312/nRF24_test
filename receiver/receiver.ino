#include <RF24.h>
#include <RF24_config.h>
#include <nRF24L01.h>
#include <printf.h>

#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(7, 8);
const byte address[6] = "00001";

void setup() {
  Serial.begin(9600);
  // Opens up the serial port on our computer
  // We want to read all our data through the serial port of our Mac
  radio.begin();
  radio.openReadingPipe(1, address);
  // We can actually open up to 6 pipes for reading at once
  radio.setPALevel(RF24_PA_MIN);
  radio.startListening();
}

void loop() {
  if (radio.available()) {
    // check if there is data to be received
    char text[32] = "";
    // creates array of 32 characters, initializes it as an empty string literal
    // first element is null character, rest are zeroed out (default constructor)
    radio.read(&text, sizeof(text));
    Serial.println(text);
    // print our text to the serial monitor
  }
}
