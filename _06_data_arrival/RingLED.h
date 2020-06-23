#ifndef RingLED_h
#define RingLED_h

#include "Pixel.h"

#define DEBUG

#if (ARDUINO >= 100)
 #include <Arduino.h>
#else
 #include <WProgram.h>
 #include <pins_arduino.h>
#endif

class RingLED {
  public:
    // global variables
    byte leds;
    byte cal = 0;
    Pixel *buf = new Pixel[24];

    RingLED();
    RingLED(byte _leds, byte _cal);
    void setCalibrationLED(byte _cal);
    void setRing(Pixel c);
    void setPixel(byte index, Pixel c);
    void setPixel(byte index, byte r, byte g, byte b);
    Pixel getPixel(byte index);
    void calibrate();
    void clearRing();
    byte getSize();
    void scrollRight(byte _i = 1);
    void scrollLeft(byte _i = 1);

  private:
    void reverse(Pixel a[], int _start, int _end);
    void rotateLeft(Pixel array[], int _size, int _i);
    void rotateRight(Pixel array[], int _size, int _i);
};

#endif

