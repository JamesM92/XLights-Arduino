/*

XLights - Arduino Generic Serial for Addressable Pixels


This code was originaly made for vixen, and has been mofiied to work with xlights.
the red and green led values are switched to work with xlights.

to get this to work in xlights when setting up the serial controller settup the prefix for the controller as 
>>[#Leds]<< 
for example >>200<<


The oringal code credit:
Vixen Lights 3.x - Arduino Generic Serial for Addressable Pixels
Created   November 8th, 2014
By        Richard Sloan - www.themindfactory.com
And       David Hunt - blog.huntgang.com
Version   1.4

*/


// You must download and install the library from http://fastled.io/ 
#include <FastLED.h>

// Sets the maximum number of LEDs that this code will handle to avoid running out of memory
#define NUM_LEDS 200

// Sets the pin which is used to connect to the LED pixel strip
#define DATA_PIN 6

CRGB leds[NUM_LEDS];


void setup() {
  // Define the speed of the serial port
  Serial.begin(115200);
}

void loop() {
  // Set some counter / temporary storage variables
  int cnt;
  unsigned int num_leds;
  unsigned int d1, d2, d3;

  // Begin an endless loop to receive and process serial data
  for(;;) {
    // Set a counter to 0.  This couter keeps track of the pixel colors received.
    cnt = 0;
    //Begin waiting for the header to be received on the serial bus
    //1st character
    
    while(!Serial.available());
      if(Serial.read() != '>') {
        continue;
        }
    //second character
    while(!Serial.available());
      if(Serial.read() != '>') {
        continue;
        }
    
    //get the first digit from the serial bus for the number of pixels to be used
    
    while(!Serial.available());
      d1 = Serial.read();
    //get the second digit from the serial bus for the number of pixels to be used
    while(!Serial.available());
      d2 = Serial.read();
    //get the third digit from the serial bus for the number of pixels to be used
    while(!Serial.available());
      d3 = Serial.read();
    //get the end of the header
    
    
    while(!Serial.available());
      if(Serial.read() != '<') {
        continue;
        }
    while(!Serial.available());
      if(Serial.read() != '<') {
        continue;
        }
    
    // calculate the number of pixels based on the characters provided in the header digits
    num_leds = (d1-'0')*100+(d2-'0')*10+(d3-'0');
    // ensure the number of pixels does not exceed the number allowed
    if(num_leds > NUM_LEDS) {
      continue;
      }
   
   num_leds = NUM_LEDS - 1;
    // Let the FastLED library know how many pixels we will be addressing
    FastLED.addLeds<WS2811, DATA_PIN, GRB>(leds, num_leds);
    // Loop through each of the pixels and read the values for each color
    do {
      while(!Serial.available());
        leds[cnt].g = Serial.read();
      
      while(!Serial.available());
        leds[cnt].r = Serial.read();

      while(!Serial.available());
        leds[cnt++].b = Serial.read();
      } 
    while(--num_leds);
    // Tell the FastLED Library it is time to update the strip of pixels
    FastLED.show();
    // WOO HOO... We are all done and are ready to start over again!
    }
}
