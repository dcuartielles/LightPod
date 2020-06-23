#include "RingLED.h"

// Empty constructor
RingLED :: RingLED() {
}

// Constructor for the LED as a screen
// - _leds: amount of LEDs in the ring
// - _cal: index for the LED used for calibration
RingLED :: RingLED(byte _leds, byte _cal) {
  leds = _leds;
  cal = _cal;
}

// Turn only the calibration LED
void RingLED :: calibrate() {
  clearRing();
  setPixel(0, 50, 50, 50);
}

// Turn all off
void RingLED :: clearRing() {
  for (int i = 0; i < leds; i++) {
    buf[i].setPixel(0, 0, 0);
  }
}

// change the calibration LED
void RingLED :: setCalibrationLED(byte _cal) {
  cal = _cal;
}

// Return the size
byte RingLED :: getSize() {
  return leds;
}

// Set all pixels in ring using the Pixel class
void RingLED :: setRing(Pixel c) {
  for (int i = 0; i < leds; i++)
    setPixel(i, c.r, c.g, c.b);
}

// Set pixel in ring using the Pixel class
void RingLED :: setPixel(byte index, Pixel c) {
  setPixel(index, c.r, c.g, c.b);
}

// Set pixel in ring at low level
void RingLED :: setPixel(byte index, byte r, byte g, byte b) {
  buf[(index + cal) % leds].setPixel(r, g, b);
}

Pixel RingLED :: getPixel(byte index) {
  Pixel tmp;
  tmp = buf[index].getPixel();
  return (tmp);
}

// Using the "most elegant, efficient solution" for the circular
// display as described by Jon Bentley in Programming Pearls Column 2
// The Reverse and Rotate functions are taken from there
void RingLED :: reverse(Pixel array[], int _start, int _end) {
  int i, j;
  for (i = _start, j = _end; i < j; i++, j--) {
    Pixel tmp = array[i];
    array[i] = array[j];
    array[j] = tmp;
  }
}


// XXX: These four funcions can be optimized to be just one, just have no time by now
// Scroll the LED ring to the right (default 1 unit)
void RingLED :: scrollRight(byte _i) {
  if (_i < 0)
    rotateLeft(buf, leds, leds -_i);
  else
    rotateRight(buf, leds, _i);
}

// Scroll the LED ring to the left (default 1 unit)
void RingLED :: scrollLeft(byte _i) {
  if (_i < 0)
    rotateRight(buf, leds, leds -_i);
  else
    rotateLeft(buf, leds, _i);
}

void RingLED :: rotateLeft(Pixel array[], int _size, int _i) {
  reverse(array, 0, _i - 1);
  reverse(array, _i, _size - 1);
  reverse(array, 0 , _size - 1);
}

void RingLED :: rotateRight(Pixel array[], int _size, int _i) {
  reverse(array, 0, _size - _i - 1);
  reverse(array, _size - _i, _i - 1);
  reverse(array, 0 , _size - 1);
}

