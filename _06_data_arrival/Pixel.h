#ifndef Pixel_h
#define Pixel_h

#if (ARDUINO >= 100)
 #include <Arduino.h>
#else
 #include <WProgram.h>
 #include <pins_arduino.h>
#endif

class Pixel {
  public:
    // stores the colors for a pixel
    // global variables
    byte r, g, b;

    Pixel();
    Pixel(byte _r, byte _g, byte _b);
    void setPixel(byte _r, byte _g, byte _b);
    Pixel getPixel();

  private:
    // do nothing
};

#endif
