// NeopixelFunktion.cpp

#include "NeopixelFunktion.h"

extern bool menuTimerGestartet;
extern bool individualTimerGestartet;

void updateNeopixelDisplay(DateTime now, DateTime startTime, DateTime endTime, NeopixelFunktion &neopixelDisplay)
{
  static bool neopixelStatus = false;
  bool timerIsActive = (now.unixtime() >= startTime.unixtime() && now.unixtime() <= endTime.unixtime());

  if (timerIsActive != neopixelStatus)
  {
    neopixelStatus = timerIsActive;

    if (timerIsActive)
    {
      // Neopixel-Anzeige aktivieren und initialisieren
      neopixelDisplay.begin();
    }
  }

  // Immer die Neopixel-Anzeige während des Timers aktualisieren
  neopixelDisplay.updateTimer(now.unixtime());

  if (!timerIsActive)
  {
    // Neopixel-Anzeige ausschalten, wenn der Timer abgelaufen ist
    neopixelDisplay.turnOff();
  }
}

NeopixelFunktion::NeopixelFunktion(int pin, int numLeds) : strip(Adafruit_NeoPixel(numLeds, pin, NEO_GRB + NEO_KHZ800))
{
  // constructor implementation
}

void NeopixelFunktion::begin()
{
  strip.begin();
  strip.show();
}

void NeopixelFunktion::startTimer(unsigned long duration)
{
  startTime = millis();
  endTime = startTime + duration;
}

void NeopixelFunktion::updateTimer(unsigned long currentTime)
{
  float percentage = calculateTimerPercentage();

  // Debug-Ausgabe des aktuellen Prozentsatzes
  Serial.print("Percentage: ");
  Serial.println(percentage);

  updateTimerDisplay(percentage);

  if (currentTime >= endTime)
  {
    // Timer abgelaufen, alle LEDs ausschalten
    turnOff();
  }
}

void NeopixelFunktion::updateTimerDisplay(float percentage)
{
  int numPixels = strip.numPixels();
  int activePixels = static_cast<int>(percentage * numPixels);
  float maxBrightness = 0.1; // Set max brightness to 10%

  for (int i = 0; i < numPixels; ++i)
  {
    if (i < activePixels)
    {
      // Set the color with reduced brightness based on timer type
      int brightness = static_cast<int>(255 * maxBrightness);
      if (individualTimerGestartet)
      {
        // Red for individualTimerGestartet
        strip.setPixelColor(i, strip.Color(brightness, 0, 0));
      }
      else if (menuTimerGestartet)
      {
        // Blue for menuTimerGestartet
        strip.setPixelColor(i, strip.Color(0, 0, brightness));
      }
    }
    else
    {
      strip.setPixelColor(i, strip.Color(0, 0, 0));
    }
  }

  strip.show();
}

void NeopixelFunktion::turnOff()
{
  int numPixels = strip.numPixels();

  for (int i = 0; i < numPixels; ++i)
  {
    strip.setPixelColor(i, strip.Color(0, 0, 0));
  }

  strip.show();
}

float NeopixelFunktion::calculateTimerPercentage()
{
  unsigned long currentTime = millis();

  if (currentTime >= endTime)
  {
    return 100.0;
  }
  else if (currentTime <= startTime)
  {
    return 0.0;
  }
  else
  {
    unsigned long elapsedTime = currentTime - startTime;
    unsigned long totalDuration = endTime - startTime;

    float percentage = static_cast<float>(elapsedTime) / totalDuration * 100.0;

    // Begrenze den Prozentsatz auf maximal 100%
    return std::min(percentage, 100.0f);
  }
}