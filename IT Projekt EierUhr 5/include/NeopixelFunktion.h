// NeopixelFunktion.h

#ifndef NEOPIXELFUNKTION_H
#define NEOPIXELFUNKTION_H

#include "GlobaleVariable.h"

extern bool menuTimerGestartet;
extern bool individualTimerGestartet;

class NeopixelFunktion
{
public:
  NeopixelFunktion(int pin, int numLeds);
  void begin();
  void startTimer(unsigned long duration);
  void updateTimer(unsigned long currentTime);
  void turnOff();
  float calculateTimerPercentage();
  void updateTimerDisplay(float percentage);
  void updateNeopixelDisplay(DateTime now, DateTime startTime, DateTime endTime); // Add this line

private:
  Adafruit_NeoPixel strip;
  unsigned long startTime;
  unsigned long endTime;
};

#endif // NEOPIXELFUNKTION_H
