/* 01 Simple (LED) test

    The clock competition consists in a competition in making a clock
    using a series of concentric rings of NeoPixel LEDs. The rings consist
    of 12, 16, and 24 LEDs respectively.

    The contendants are: Arturo G. and David C. from Arduino and the conditions
    were just to be using the MKR1000 in order to count with some basic real time
    functionalities.

    This code is part of David C. experiments used to prepare his personal code

    Based on the NeoPixel Ring simple sketch (c) 2013 Shae Erisson
    released under the GPLv3 license to match the rest of the AdaFruit NeoPixel library

    This example is licensed under GPLv3 (c) 2018 D. Cuartielles
*/

#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h>
#endif

// Data Out pin
#define PIN            12


// Total amount of NeoPixels in the clock
#define NUMPIXELS      52

// Final luminosity of the test (0..255)
#define LUMINOSITY     50

// Delay for the interaction between LEDs
#define DELAYVAL       100

// Create the pixels object
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  // This initializes the NeoPixel library
  pixels.begin(); 

}

void loop() {

  testClock(0, LUMINOSITY, 0);

  testClock(LUMINOSITY, LUMINOSITY, 0);
  
  testClock(LUMINOSITY, LUMINOSITY, LUMINOSITY);

}

void testClock(byte r, byte g, byte b) {
  // For a set of NeoPixels the first NeoPixel is 0, second is 1, all the way up to the count of pixels minus one.
  for (int i = 0; i < NUMPIXELS; i++) {

    // pixels.Color takes RGB values, from 0,0,0 up to 255,255,255
    pixels.setPixelColor(i, pixels.Color(r, g, b)); // Moderately bright green color.

    pixels.show(); // This sends the updated pixel color to the hardware.

    delay(DELAYVAL); // Delay for a period of time (in milliseconds).

  }  
}

