/* 02 Sync (LED) rings

    The clock competition consists in a competition in making a clock
    using a series of concentric rings of NeoPixel LEDs. The rings consist
    of 12, 16, and 24 LEDs respectively.

    The contendants are: Arturo G. and David C. from Arduino and the conditions
    were just to be using the MKR1000 in order to count with some basic real time
    functionalities.

    This example is setting up which LED in each one of the rings corresponds to the
    beginning of the cycle. In order to do so, I create a class that will allow having
    a variable size of rings, common scrolling functions, etc.

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
#define PIN            12

// Total amount of NeoPixels in the clock
#define NUMPIXELS      52

// Final luminosity of the test (0..255)
#define LUMINOSITY     50

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
  innerRing = RingLED(12, 0);
  midRing = RingLED(16, 0);
  outerRing = RingLED(24, 0);

  // Start by calibrating the Rings (turns on the Calibration LED)
  innerRing.calibrate();
  midRing.calibrate();
  outerRing.calibrate();

#ifdef DEBUG
  // Init serial port
  Serial.begin(9600);
#endif
}

void loop() {

  // Use these funcions e.g. tied up to a potentiometer to
  // interactively calibrate the LEDs
  //innerRing.setCalibrationLED(i);
  //midRing.setCalibrationLED(m);
  //outerRing.setCalibrationLED(o);
  //innerRing.calibrate();
  //midRing.calibrate();
  //outerRing.calibrate();

#ifdef DEBUG
  // printout the inner ring to check it out
  for (int i = 0; i < innerRing.getSize(); i++) {
    Serial.print(innerRing.getPixel(i).r); Serial.print(", ");
  }
  Serial.println();
#endif

  updateRings();

  pixels.show();

  delay(50);

}


