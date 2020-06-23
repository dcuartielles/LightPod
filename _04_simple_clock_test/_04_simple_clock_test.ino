/* 04 Simple clock test

    The clock competition consists in a competition in making a clock
    using a series of concentric rings of NeoPixel LEDs. The rings consist
    of 12, 16, and 24 LEDs respectively.

    The contendants are: Arturo G. and David C. from Arduino and the conditions
    were just to be using the MKR1000 in order to count with some basic real time
    functionalities.

    This example is used to see that all of the LEDs work using the inner ring as
    a fast counter. When the full inner ring as cycled through all of the LEDs, the
    middle ring shifts one LED, and when all of the LEDs in the middle ring have been
    lit, the outer ring will shift one LED. At the end of the loop, the whole ring
    will restart.

    This code is part of David C. experiments used to prepare his personal code

    Based on the NeoPixel Ring simple sketch (c) 2013 Shae Erisson
    released under the GPLv3 license to match the rest of the AdaFruit NeoPixel library

    This example is licensed under GPLv3 (c) 2018 D. Cuartielles
*/

#include <Adafruit_NeoPixel.h>
#include "Pixel.h"
#include "RingLED.h"

#ifdef __AVR__
#include <avr/power.h>
#endif

// Are we debugging the code via Serial?
#define DEBUG          1

// Data Out pin
#define PIN            6

// Total amount of NeoPixels in the clock
#define NUMPIXELS      52

// Final luminosity of the test (0..255)
#define LUMINOSITY     80

// Delay for the interaction between LEDs
#define DELAYVAL       100

// Create the pixels object
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

// Declare the rings
RingLED innerRing;
RingLED midRing;
RingLED outerRing;

// Declare counters
int i = 0, m = 0, o = 0;

void setup() {
  // This initializes the NeoPixel library
  pixels.begin();

  // Init the rings, note this example calibration is
  // the one I needed for my set of LEDs
  innerRing = RingLED(12, 2);
  midRing = RingLED(16, 7);
  outerRing = RingLED(24, 8);

  // Start by calibrating the Rings (turns on the Calibration LED)
  innerRing.calibrate();
  midRing.calibrate();
  outerRing.calibrate();

  // Match the counters to the calibration for each ring
  i = innerRing.cal;
  m = midRing.cal;
  o = outerRing.cal;

#ifdef DEBUG
  // Init serial port
  Serial.begin(9600);
#endif
}

void loop() {

  i++;
  if (i >= innerRing.getSize()) 
    i = 0;

  if (m >= midRing.getSize()) 
    m = 0;

  if (o >= outerRing.getSize())
    o = 0;

  innerRing.scrollRight();
  
  if (i == innerRing.cal) {
    midRing.scrollRight();
    m++;
  }
  
  if (i == innerRing.cal && m == midRing.cal) {
    outerRing.scrollRight();
    o++;
  }

  updateRings();

  pixels.show();

  delay(50);

}


