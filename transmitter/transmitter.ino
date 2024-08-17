#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(7, 8);
// Create an instance of the RF24 transceiver, passing in, as input, our CE & CSN pin # 
const byte address[6] = "00001";
// enables us to choose which receiver we want our transmitter to talk to

void setup() {
  radio.begin();
  radio.openWritingPipe(address);
  // set the address of the receiver that we will be writing data to
  // thus, in our receiver code, we will see radio.setReadingPipe(), 
  // where we set the address of the transmitter we read data from
  radio.setPALevel(RF24_PA_MIN);
  // set the power amplification level, based on the distance between transmitter & receiver
  radio.stopListening();
  // sets this transceiver as a transmitter
}

void loop() {
  // Let us try transmitting Hello World 
  const char text[] = "Hello World";
  // Remember that strings are reference types; they really are just an array of char
  // w/ a special null char to mark the end of the string
  // Thus, we can initialize a char array with a string literal 
  radio.write(&text, sizeof(text));
  // pass a reference to the data we send, alongside the size of the data 
  delay(1000);
}