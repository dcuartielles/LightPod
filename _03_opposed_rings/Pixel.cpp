#include "Pixel.h"

Pixel :: Pixel() {
  // by default, let the pixel be gray at 200, as a homeage to Processing
  r = 200;
  g = 200;
  b = 200;
}

Pixel :: Pixel(byte _r, byte _g, byte _b) {
  r = _r;
  g = _g;
  b = _b;
}

void Pixel :: setPixel(byte _r, byte _g, byte _b) {
  r = _r;
  g = _g;
  b = _b;
}

Pixel Pixel :: getPixel() {
  Pixel arr;
  arr.r = r;
  arr.g = g;
  arr.b = b;
  return (arr);
}

/* OLD take away */
/*
byte* Pixel :: getPixel() {
  byte* arr = new byte[3];
  arr[0] = r; arr[1] = g; arr[2] = b;
  return (arr);
}
*/


