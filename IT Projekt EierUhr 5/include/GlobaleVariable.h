#ifndef GLOBALE_VARIABLE_H
#define GLOBALE_VARIABLE_H

#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_NeoPixel.h>
#include <RTClib.h>
#include <RotaryEncoder.h>
#include <driver/ledc.h>
#include <SPI.h>

/////////////////////////////////////////////
// defines
/////////////////////////////////////////////

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
#define CLK_PIN 26
#define DT_PIN 27
#define SW_PIN 33
#define SUMMER_PIN 19
#define TIMER_PIN 16
#define NEOPIXEL_PIN 18
#define NUM_LEDS 8
#define SCREEN_EINSCHALTEN 0
#define SCREEN_HOME 1
#define SCREEN_MENU 2
#define SCREEN_SELECTED_TIME 3
#define SCREEN_EINWILLIGUNG 4
#define SCREEN_INDIVIDUAL_TIMER 5
#define SCREEN_ABGELAUFEN 6
#define MENU_ANZ 10

extern RTC_DS3231 rtc;
extern Adafruit_SSD1306 display;

extern char daysOfTheWeek[7][12];

extern const char *menu[MENU_ANZ];

struct MenuEntry
{
  int hour;
  int minute;
  int second;
};

extern MenuEntry menuTimes[MENU_ANZ];

extern int currentScreen;
extern int selectedMenuItem;
extern int Selection;
extern int Selection2;
extern int lastEncoderPosition;
extern unsigned long einschaltenStartTime;
extern bool isSelectedHour;
extern bool isSelectedMinute;
extern bool isSelectedSecond;
extern bool isSelectedHour1;
extern bool isSelectedMinute1;
extern bool isSelectedSecond1;
extern bool SelctionINDI;
extern bool isTimerSelected;

/////////////////////////////////////////////
// variablen für Buttons
/////////////////////////////////////////////

extern int btn_pressed;
extern int btn_counter;
extern int tmrbtn_pressed;
extern int tmrbtn_counter;
extern unsigned long lastPin33Press;
extern unsigned long lastActivityTime;

/////////////////////////////////////////////
// Variablen für timer
/////////////////////////////////////////////

extern int stundenMenu;
extern int minutenMenu;
extern int sekundenMenu;
extern int stundenIndi;
extern int minutenIndi;
extern int sekundenIndi;
extern int selectedHour;
extern int selectedMinute;
extern int selectedSecond;

#endif // GLOBALE_VARIABLE_H