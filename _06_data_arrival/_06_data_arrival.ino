/* 06 Data Arrival to (LED) rings

    The clock competition consists in a competition in making a clock
    using a series of concentric rings of NeoPixel LEDs. The rings consist
    of 12, 16, and 24 LEDs respectively.

    The contendants are: Arturo G. and David C. from Arduino and the conditions
    were just to be using the MKR1000 in order to count with some basic real time
    functionalities.

    This example is showing how the rings behave when a new stream of data arrives and
    how they change from a previous status to the following one. It is tested using the
    serial port, commands are a letter (i, m, o) for the ring and a HEX number (0 .. F) for
    the jump. It is not perfect, but allows testing how things work

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

  if (Serial.available() > 0) {
    byte ring = Serial.read();

    // leave now if it is not the byte corresponding to the ring indicator
    if (ring != 'i' && ring != 'm' && ring != 'o') {
      // do nothing
    } else {

      // wait for the next byte, stop everything!!
      while (!Serial.available() > 0) {}

      byte jump = Serial.read();

      switch (ring) {
        case 'i':
          affectRing(innerRing);
          for (int i = 0; i < jump; i++)
            innerRing.scrollRight();
          innerRing.setPixel(0, Pixel(50, 50, 50));
          break;

        case 'm':
          affectRing(midRing);
          for (int i = 0; i < jump; i++)
            midRing.scrollLeft();
          midRing.setPixel(0, Pixel(50, 50, 50));
          break;

        case 'o':
          affectRing(outerRing);
          for (int i = 0; i < jump; i++)
            outerRing.scrollRight();
          outerRing.setPixel(0, Pixel(50, 50, 50));
          break;
      }
    }
  }

  updateRings();

  pixels.show();

  delay(50);

}



