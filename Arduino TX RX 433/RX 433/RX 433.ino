// include libraries:
#include <RH_ASK.h>
#include <SPI.h>

// Create an instance of the RadioHead ASK handler:
// -> Default pins for the RF modules:
//    Pin 11: Data input from receiver
//    Pin 12: Data output to transmitter
RH_ASK radio;

// Create and initialize three 8-bit variables for our received RGB values:
uint8_t r = 0;
uint8_t g = 0;
uint8_t b = 0;

void setup() {
  // initialize the RadioHead library:
  radio.init();
     Serial.begin(9600);   // inicializa monitor serie a 9600 bps

  //declare pin 3, 5 and 6 as output pins so that the analog voltages for the RGB LED can later be written to them:
  pinMode(3, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
}

void loop() {
  // create an empty array of 8-bit variables that is used to store the received data:
  uint8_t data[3];
  // store the expected data length in a variable (3 Bytes: One for r, g, and b):
  uint8_t dataLength = 3;

  // check if data has been received by RadioHead and push the empty array as well as the 
  // expected dataLength to RadioHead, so that it can store the received data inside the provided array:
  if(radio.recv(data, &dataLength)){
    // when data has been received, extract the received RGB values from the array:
    // -> The order must be the same as in the dataArray[] on the transmitter side (here: 0: red, 1: green, 2: blue):
    r = data[0];
    g = data[1];
    b = data[2];
    
     Serial.print("R: ");  // imprime Mensaje:
     Serial.println(255-r);   // imprime buffer de mensaje     
     Serial.print("G: ");  // imprime Mensaje:
     Serial.println(255-g);   // imprime buffer de mensaje     
     Serial.print("B: ");  // imprime Mensaje:
     Serial.println(255-b);   // imprime buffer de mensaje     
delay(1000);





    // afterwards write the received values to the analog pins of the RGB LED:
    outputValues();
  }
}

void outputValues(){
  // write the RGB values stored in the global r, g and b variables to pin 3, 5 and 6 where the RGB LED is connected:
  // -> Since I used a common anode RGB leds, the analog pins act as the ground pins of the LED. Therefore the signals must be inverted,
  // e.g. '0' means full brightness and '255' means completely dark.
  analogWrite(3, 255-r);
  analogWrite(5, 255-g);
  analogWrite(6, 255-b);




}