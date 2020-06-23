/* 05 Breathing (LED) rings

    The clock competition consists in a competition in making a clock
    using a series of concentric rings of NeoPixel LEDs. The rings consist
    of 12, 16, and 24 LEDs respectively.

    The contendants are: Arturo G. and David C. from Arduino and the conditions
    were just to be using the MKR1000 in order to count with some basic real time
    functionalities.

    This example is showing how the rings give the feeling of waves by changing the colors
    between the rings following a concentric fashion.

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

// Maximum light value at which the LEDs stop being linear
#define MAX_LED        100

// Type of interaction: UNIFORM, LINEAR, LINEAR_PAUSE
#define UNIFORM        0
#define LINEAR         1
#define LINEAR_PAUSE   2
#define WAVE           3
#define WAVE_INV       4

byte interaction = WAVE_INV;

// Create the pixels object
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

// Declare the rings
RingLED innerRing;
RingLED midRing;
RingLED outerRing;

// Declare the uniform color for each ring
Pixel iP;
Pixel mP;
Pixel oP;

// Declare counters
int i = 0, m = 0, o = 0;

// Declare counter increments
int iDir = 1, mDir = 1, oDir = 1;

// Declare possible initial differences
int initDiff = 20;

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

  switch (interaction) {
  case UNIFORM:
    // config for uniform increment the grey level of the rings
    i = 0; m = 0; o = 0;
    break;

  case LINEAR:
    // config for linear differences at the increment the grey level of the rings
    i = 0; m = initDiff; o = initDiff * 2;
    break;

  case LINEAR_PAUSE:
    // config for uniform increment the grey level of the rings
    i = 0; m = 0; o = 0;
    break;

  case WAVE:
    // config for uniform increment the grey level of the rings
    i = 0; m = 0; o = 0;
    break;

  case WAVE_INV:
    // config for uniform increment the grey level of the rings
    i = 0; m = 0; o = 0;
    break;
  }
}

void loop() {

  // uniform increment the grey level of the rings
  i += iDir;
  m += mDir;
  o += oDir;

  // check that the levels are Ok
  switch (interaction) {
  case UNIFORM:
    limitLevels();
    break;

  case LINEAR:
    limitLevels();
    break;

  case LINEAR_PAUSE:
    limitLevelsPause();
    break;

  case WAVE:
    limitLevelsWave();
    break;

  case WAVE_INV:
    limitLevelsWaveInv();
    break;
  }

  // set the color levels
  iP.setPixel(i, i , i);
  mP.setPixel(m, m , m);
  oP.setPixel(o, o , o);

#ifdef DEBUG
  // Check light intensity
  //Serial.println(m);
#endif

  // Make the LEDs scroll in opposite directions
  innerRing.setRing(iP);
  midRing.setRing(mP);
  outerRing.setRing(oP);

  updateRings();

  pixels.show();

  delay(10);

}

