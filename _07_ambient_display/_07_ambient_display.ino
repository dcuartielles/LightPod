/* 07 Ambient display of (LED) rings

    The clock competition consists in a competition in making a clock
    using a series of concentric rings of NeoPixel LEDs. The rings consist
    of 12, 16, and 24 LEDs respectively.

    The contendants are: Arturo G. and David C. from Arduino and the conditions
    were just to be using the MKR1000 in order to count with some basic real time
    functionalities.

    This is the code put together to make the pod behave as an ambient display
    for MaH's IoTaP laboratory open day demo. The MKR1000 has installed a series
    of certificates that allow it to connect to the MQTT server and start gathering
    data and represent it on the screen. There are a series of MQTT topics available
    at IoTaP, but I decided to focus on the one provided by an Arduino board
    connected to a PC since it is the one providing the most meaningful source
    of data from all the available ones.

    I decide to go for the following configuration: inner ring will represent sound
    levels, middle ring distance, outer ring temperature. The basic color will be
    values of white light and upon the arrival of an event, I will use the red color
    to signify that difference. Also an animation will run whenever a value goes
    over a threshold.

    This code is part of David C. experiments used to prepare his personal code

    Based on the NeoPixel Ring simple sketch (c) 2013 Shae Erisson
    released under the GPLv3 license to match the rest of the AdaFruit NeoPixel library

    This example is licensed under GPLv3 (c) 2018 D. Cuartielles

    Credits: Sandeep M. from Arduino for helping putting the MQTT to work on the MKR1000
             Mattias N. and Johannes N. from Malmo University for the help with the pod design
             Johan H. for his help with AWS IoT
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
#define NETWORK_SEARCH 5
#define MQTT_CONNECT   6
#define DATA_COLLECT   7
#define DATA_FADE_IN   8
#define DATA_FADE_OUT  9
#define NONE           99

byte interaction = NETWORK_SEARCH;
byte interactionNext = NONE;

// States of the machine
#define INIT           0
#define CONNECTING     1
#define CONNECTED      2
#define EVENT_SOUND    3
#define EVENT_DISTANCE 4

byte state = INIT;

// Create the pixels object
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

// Declare the rings
RingLED innerRing, innerRingBackup;
RingLED midRing, midRingBackup;
RingLED outerRing, outerRingBackup;

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

// Declare a variabla for the timer, or maybe two
long timerSearch;
long timerFade;
long timerOppositeScrolls;
long timerEvent;

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

    case NETWORK_SEARCH:
      break;

    case MQTT_CONNECT:
      break;

    case DATA_COLLECT:
      break;

    case DATA_FADE_IN:
      break;

    case DATA_FADE_OUT:
      break;
  }
}

void loop() {

  if (interaction >= UNIFORM && interaction <= WAVE_INV || interaction == MQTT_CONNECT) {
    // uniform increment the grey level of the rings
    i += iDir;
    m += mDir;
    o += oDir;
  }

  // logic for changing state
  switch (state) {
    case INIT:
      //interactionNext = NETWORK_SEARCH;
      interaction = NETWORK_SEARCH;
      timerOppositeScrolls = millis();
      state = CONNECTING;
      break;

    case CONNECTING:
      //state = CONNECTED;
      break;
      
    case CONNECTED:
      //interactionNext = DATA_COLLECT;
      interaction = DATA_COLLECT;
      break;

    case EVENT_SOUND:
      //interactionNext = WAVE;
      interaction = WAVE;
      break;

    case EVENT_DISTANCE:
      //interactionNext = WAVE_INV;
      interaction = WAVE_INV;
      break;
  }

  // timers

  // execute the screen updates
  switch (interaction) {
    case UNIFORM:
      limitLevels();
      modRings();
      break;

    case LINEAR:
      limitLevels();
      modRings();
      break;

    case LINEAR_PAUSE:
      limitLevelsPause();
      modRings();
      break;

    case WAVE:
      limitLevelsWave();
      modRings();
      break;

    case WAVE_INV:
      limitLevelsWaveInv();
      modRings();
      break;

    case NETWORK_SEARCH:
      oppositeScrolls();
      break;

    case MQTT_CONNECT:
      limitLevels();
      modRings();
      break;

    case DATA_COLLECT:
      break;

    case DATA_FADE_IN:
      break;

    case DATA_FADE_OUT:
      break;
  }

  updateRings();

  pixels.show();

  delay(10);

}


