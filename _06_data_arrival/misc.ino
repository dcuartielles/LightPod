void testClock(byte r, byte g, byte b) {
  // For a set of NeoPixels the first NeoPixel is 0, second is 1, all the way up to the count of pixels minus one.
  for (int i = 0; i < NUMPIXELS; i++) {

    // pixels.Color takes RGB values, from 0,0,0 up to 255,255,255
    pixels.setPixelColor(i, pixels.Color(r, g, b)); // Moderately bright green color.

    pixels.show(); // This sends the updated pixel color to the hardware.

    delay(DELAYVAL); // Delay for a period of time (in milliseconds).

  }
}

void updateRings() {
  int offset = 0;
  for (int i = 0; i < innerRing.getSize(); i++) {
    pixels.setPixelColor(i, pixels.Color(innerRing.buf[i].r, innerRing.buf[i].g, innerRing.buf[i].b));
  }
  offset = innerRing.getSize();
  for (int i = 0; i < midRing.getSize(); i++) {
    pixels.setPixelColor(i + offset, pixels.Color(midRing.buf[i].r, midRing.buf[i].g, midRing.buf[i].b));
  }
  offset += midRing.getSize();
  for (int i = 0; i < outerRing.getSize(); i++) {
    pixels.setPixelColor(i + offset, pixels.Color(outerRing.buf[i].r, outerRing.buf[i].g, outerRing.buf[i].b));
  }
}

void affectRing(RingLED ring) {
  for (int i = 1; i < ring.getSize(); i++) {
    Pixel temp = ring.getPixel(i);
    temp = affectColor(temp);
    ring.setPixel(i, temp);
  }
}

// the info is stored in bytes, therefore the operations done this way
Pixel affectColor(Pixel p) {
  if (p.r > 10) p.r = p.r - 10;
  else p.r = 0;

  if (p.g > 10) p.g = p.g - 10;
  else p.g = 0;

  if (p.b > 10) p.b = p.b - 10;
  else p.b = 0;

  return p;
}


