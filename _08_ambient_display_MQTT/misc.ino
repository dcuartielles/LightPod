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


void limitLevels() {
  if (i >= MAX_LED) {
    i = MAX_LED;
    iDir = -1;
  }

  if (i <= 0) {
    i = 0;
    iDir = 1;
  }

  if (m >= MAX_LED) {
    m = MAX_LED;
    mDir = -1;
  }

  if (m <= 0) {
    m = 0;
    mDir = 1;
  }

  if (o >= MAX_LED) {
    o = MAX_LED;
    oDir = -1;
  }

  if (o <= 0) {
    o = 0;
    oDir = 1;
  }
}

void limitLevelsPause() {
  // init the variables to check the extremes of the scale
  boolean iMax = false, iMin = false, mMax = false, mMin = false, oMax = false, oMin = false;

  if (i >= MAX_LED) {
    i = MAX_LED;
    iMax = true;
  }

  if (i <= 0) {
    i = 0;
    iMin = true;
  }

  if (m >= MAX_LED) {
    m = MAX_LED;
    mMax = true;
  }

  if (m <= 0) {
    m = 0;
    mMin = true;
  }

  if (o >= MAX_LED) {
    o = MAX_LED;
    oMax = true;
  }

  if (o <= 0) {
    o = 0;
    oMin = true;
  }

  // start decreasing
  if (iDir > 0 && mDir > 0 && oDir > 0) {
    if (iMax && mMax && oMax) {
      oDir = -1;
    }
  }

  if (iDir > 0 && mDir > 0 && oDir < 0) {
    if (iMax && mMax && o <= MAX_LED - initDiff) {
      mDir = -1;
    }
  }

  if (iDir > 0 && mDir < 0 && oDir < 0) {
    if (iMax && m <= MAX_LED - initDiff && o <= MAX_LED - 2 * initDiff) {
      iDir = -1;
    }
  }

  // start increasing
  if (iDir < 0 && mDir < 0 && oDir < 0) {
    if (iMin && mMin && oMin) {
      iDir = 1;
    }
  }

  if (iDir > 0 && mDir < 0 && oDir < 0) {
    if (mMin && oMin && i >= initDiff) {
      mDir = 1;
    }
  }

  if (iDir > 0 && mDir > 0 && oDir < 0) {
    if (oMin && m >= initDiff && i >= 2 * initDiff) {
      oDir = 1;
    }
  }
}

void limitLevelsWave() {
  // init the variables to check the extremes of the scale
  boolean iMax = false, iMin = false, mMax = false, mMin = false, oMax = false, oMin = false;

  if (i >= MAX_LED) {
    i = MAX_LED;
    iMax = true;
  }

  if (i <= 0) {
    i = 0;
    iMin = true;
  }

  if (m >= MAX_LED) {
    m = MAX_LED;
    mMax = true;
  }

  if (m <= 0) {
    m = 0;
    mMin = true;
  }

  if (o >= MAX_LED) {
    o = MAX_LED;
    oMax = true;
  }

  if (o <= 0) {
    o = 0;
    oMin = true;
  }

  // when reaching max, wait for the others and
  // start from the center again
  if (iDir > 0 && mDir > 0 && oDir > 0) {
    if (iMax && mMax && oMax) {
      iDir = -1;
    }
  }

  if (iDir < 0 && mDir > 0 && oDir > 0) {
    if (mMax && oMax && i <= MAX_LED - initDiff) {
      mDir = -1;
    }
  }

  if (iDir < 0 && mDir < 0 && oDir > 0) {
    if (oMax && m <= MAX_LED - initDiff && i <= MAX_LED - 2 * initDiff) {
      oDir = -1;
    }
  }

  // when reaching min do as usual
  if (iDir < 0 && mDir < 0 && oDir < 0) {
    if (iMin && mMin && oMin) {
      iDir = 1;
    }
  }

  if (iDir > 0 && mDir < 0 && oDir < 0) {
    if (mMin && oMin && i >= initDiff) {
      mDir = 1;
    }
  }

  if (iDir > 0 && mDir > 0 && oDir < 0) {
    if (oMin && m >= initDiff && i >= 2 * initDiff) {
      oDir = 1;
    }
  }
}

void limitLevelsWaveInv() {
  // init the variables to check the extremes of the scale
  boolean iMax = false, iMin = false, mMax = false, mMin = false, oMax = false, oMin = false;

  if (i >= MAX_LED) {
    i = MAX_LED;
    iMax = true;
  }

  if (i <= 0) {
    i = 0;
    iMin = true;
  }

  if (m >= MAX_LED) {
    m = MAX_LED;
    mMax = true;
  }

  if (m <= 0) {
    m = 0;
    mMin = true;
  }

  if (o >= MAX_LED) {
    o = MAX_LED;
    oMax = true;
  }

  if (o <= 0) {
    o = 0;
    oMin = true;
  }

  // when reaching max, wait for the others and
  // start from the outerRing again
  if (iDir > 0 && mDir > 0 && oDir > 0) {
    if (iMax && mMax && oMax) {
      oDir = -1;
    }
  }

  if (iDir > 0 && mDir > 0 && oDir < 0) {
    if (iMax && mMax && o <= MAX_LED - initDiff) {
      mDir = -1;
    }
  }

  if (iDir > 0 && mDir < 0 && oDir < 0) {
    if (iMax && m <= MAX_LED - initDiff && o <= MAX_LED - 2 * initDiff) {
      iDir = -1;
    }
  }

  // when reaching min wait for everyone to arrive
  if (iDir < 0 && mDir < 0 && oDir < 0) {
    if (iMin && mMin && oMin) {
      oDir = 1;
    }
  }

  if (iDir < 0 && mDir < 0 && oDir > 0) {
    if (iMin && mMin && o >= initDiff) {
      mDir = 1;
    }
  }

  if (iDir < 0 && mDir > 0 && oDir > 0) {
    if (iMin && m >= initDiff && o >= 2 * initDiff) {
      iDir = 1;
    }
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

void oppositeScrolls() {
  if (millis() - timerOppositeScrolls > 50) {
    // Make the LEDs scroll in opposite directions
    innerRing.scrollRight();
    midRing.scrollLeft();
    outerRing.scrollRight();
    timerOppositeScrolls = millis();
  }
}

void modRings() {
  // set the color levels
  iP.setPixel(i, i , i);
  mP.setPixel(m, m , m);
  oP.setPixel(o, o , o);

  // Make the LEDs scroll in opposite directions
  innerRing.setRing(iP);
  midRing.setRing(mP);
  outerRing.setRing(oP);
}

