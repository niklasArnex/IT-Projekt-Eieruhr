// ClockScreen.h
#ifndef CLOCK_SCREEN_H
#define CLOCK_SCREEN_H

#include "GlobaleVariable.h"

class ClockScreen
{
public:
    ClockScreen(Adafruit_SSD1306 &display, RTC_DS3231 &rtc);
    void show();

private:
    Adafruit_SSD1306 &display;
    RTC_DS3231 &rtc;
    char daysOfTheWeek[7][12] = {"Sonntag", "Montag", "Dienstag", "Mitwoch", "Donnerstag", "Freitag", "Samstag"};
};

#endif // CLOCK_SCREEN_H