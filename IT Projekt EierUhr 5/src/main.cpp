/////////////////////////////////////////////
// #include Funktionen
/////////////////////////////////////////////

#include "GlobaleVariable.h"
#include "ClockScreen.h"
#include "Debug.h"
#include "EinschaltenScreen.h"
#include "NeopixelFunktion.h"
#include "TasterFunktion.h"
#include "EncoderFunktion.h"
#include "TimerFunktion.h"
#include "Menuscreen.h"
#include "EinwilligungScreen.h"
#include "SelectedTimer.h"
#include "ESPAsyncWebServer.h"
#include "WLAN.h"
#include <esp_sleep.h>

RTC_DS3231 rtc;
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
ClockScreen clockScreen(display, rtc);
EinschaltenScreen einschaltenScreen(display);
NeopixelFunktion neopixelDisplay(NEOPIXEL_PIN, NUM_LEDS);

/////////////////////////////////////////////
// Variablen für Auswahl und Anzeige
/////////////////////////////////////////////

MenuEntry menuTimes[MENU_ANZ];

int currentScreen = SCREEN_EINSCHALTEN;
int selectedMenuItem = 0;
int Selection = 0;
int Selection2 = 0;
int lastEncoderPosition = 0;
unsigned long einschaltenStartTime = 0;
bool isSelectedHour = false;
bool isSelectedMinute = false;
bool isSelectedSecond = false;
bool isSelectedHour1 = false;
bool isSelectedMinute1 = false;
bool isSelectedSecond1 = false;
bool SelctionINDI = true;
bool isTimerSelected = false;

/////////////////////////////////////////////
// variablen für Buttons
/////////////////////////////////////////////

int btn_pressed = 0;
int btn_counter = 0;
int tmrbtn_pressed = 0;
int tmrbtn_counter = 0;
unsigned long lastPin33Press = 0;
unsigned long lastActivityTime = 0;

/////////////////////////////////////////////
// Variablen für timer
/////////////////////////////////////////////

int stundenMenu;
int minutenMenu;
int sekundenMenu;
int stundenIndi;
int minutenIndi;
int sekundenIndi;
int selectedHour;
int selectedMinute;
int selectedSecond;
DateTime timeout;
DateTime timeout2;
bool menuTimerGestartet = false;
bool individualTimerGestartet = false;

/////////////////////////////////////////////
// Funktionen
/////////////////////////////////////////////

void showClock();
void showIndividualTimer();
void showSelectedTimer();
void showEinwilligungScreen();
void checkEncoderPosition();
void showMenu();
void updateSelectedValue();
void printDebugInfo();
int detect_button_press();
int detect_timer_button_press();
void updateNeopixelDisplay(DateTime now, DateTime startTime, DateTime endTime, NeopixelFunktion &neopixelDisplay);

/////////////////////////////////////////////
// Code
/////////////////////////////////////////////

/////////////////////////////////////////////
// Funktion setup
/////////////////////////////////////////////

void setup()
{
  Serial.begin(9600);
  pinMode(SW_PIN, INPUT_PULLUP);
  pinMode(TIMER_PIN, INPUT_PULLDOWN);
  pinMode(SUMMER_PIN, OUTPUT);

  neopixelDisplay.begin();
  neopixelDisplay.turnOff();

  if (!rtc.begin())
  {
    DEBUG_PRINTLN("Couldn't find RTC");
    while (1)
      ;
  }

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C))
  {
    DEBUG_PRINTLN(F("SSD1306 allocation failed"));
    for (;;)
      ;
  }

  currentScreen = SCREEN_EINSCHALTEN;
  einschaltenScreen.startScreen();

  currentScreen = SCREEN_HOME;
  showClock();

  // Hier wird die Uhrzeit einmalig hochgeladen
  rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  DateTime now = rtc.now();

  setupWiFi();

  for (int i = 0; i < MENU_ANZ; i++)
  {
    menuTimes[i].hour = 0;
    menuTimes[i].minute = 0;
    menuTimes[i].second = 0;
  }
  TimeSpan timeSpan1(stundenMenu * 3600 + minutenMenu * 60 + sekundenMenu);
  TimeSpan timeSpan2(stundenIndi * 3600 + minutenIndi * 60 + sekundenIndi);
}

/////////////////////////////////////////////
// Funktion zum anzeigen des HomeScreen mit aktueller Zeit
/////////////////////////////////////////////

void showClock()
{
  display.clearDisplay();
  clockScreen.show();
  display.display();
}

/////////////////////////////////////////////
// Funktion loop
/////////////////////////////////////////////

void loop()
{
  delay(10);
  encoder.tick();

  DateTime now = rtc.now();

  // Timer starten und Neopixel-Anzeige aktualisieren
  if (menuTimerGestartet)
  {
    updateNeopixelDisplay(now, timeout, (timeout + TimeSpan(0, 0, 0, 0)), neopixelDisplay);
  }
  else if (individualTimerGestartet)
  {
    updateNeopixelDisplay(now, timeout2, (timeout2 + TimeSpan(0, 0, 0, 0)), neopixelDisplay);
  }

  // Überwachen der Position des Drehgebers
  int encoderPosition = encoder.getPosition();
  checkEncoderPosition();

  // Überprüfen, ob der SW_PIN gedrückt gehalten wurde

  unsigned long swPressDuration = millis() - lastPin33Press;

  if (digitalRead(SW_PIN) == LOW)
  {
    // Button ist gedrückt
    if (swPressDuration >= 3000)
    {
      // Button wurde 4 Sekunden lang gedrückt
      currentScreen = SCREEN_EINSCHALTEN;
      showClock();
      lastPin33Press = millis(); // Zurücksetzen der Zeit für den nächsten Druck
    }
  }
  else
  {
    // Button ist nicht gedrückt
    lastPin33Press = millis(); // Zurücksetzen der Zeit, wenn der Button losgelassen wird
  }

  // SW Taster Steuerung

  if (detect_button_press())
  {
    if (currentScreen == SCREEN_EINSCHALTEN)
    {
      if (millis() - einschaltenStartTime > 3000)
      {
        currentScreen = SCREEN_HOME;
        showClock();
      }
    }
    else if (currentScreen == SCREEN_HOME)
    {

      if (!menuTimerGestartet && !individualTimerGestartet)
      {
        currentScreen = SCREEN_MENU;
        showMenu();
      }
      else if (!menuTimerGestartet && individualTimerGestartet)
      {
        currentScreen = SCREEN_MENU;
        showMenu();
      }
      else if (menuTimerGestartet && !individualTimerGestartet)
      {
        currentScreen = SCREEN_SELECTED_TIME;
        showSelectedTimer();
      }
      else if (menuTimerGestartet && individualTimerGestartet)
      {
        currentScreen = SCREEN_SELECTED_TIME;
        showSelectedTimer();
      }
    }
    else if (currentScreen == SCREEN_MENU)
    {
      currentScreen = SCREEN_EINWILLIGUNG;
      showEinwilligungScreen();
      isTimerSelected = true;
    }
    else if (currentScreen == SCREEN_EINWILLIGUNG)
    {
      if (Selection == 0)
      {
        currentScreen = SCREEN_SELECTED_TIME;
        showSelectedTimer();
        if (isTimerSelected)
        {
          timerStarten();
        }
        if (selectedHour > 0 || selectedMinute > 0 || selectedSecond > 0)
        {
          timer2Starten();
        }
      }
      else if (Selection == 1)
      {
        currentScreen = SCREEN_MENU;
        showMenu();
        isTimerSelected = false;
      }
    }
    else if (currentScreen == SCREEN_INDIVIDUAL_TIMER && SelctionINDI == true)
    {
      if (Selection2 == 0)
      {
        isSelectedHour1 = true;
        SelctionINDI = false;
      }
      else if (Selection2 == 1)
      {
        isSelectedMinute1 = true;
        SelctionINDI = false;
      }
      else if (Selection2 == 2)
      {
        isSelectedSecond1 = true;
        SelctionINDI = false;
      }
    }
    else if (currentScreen == SCREEN_INDIVIDUAL_TIMER && SelctionINDI == false)
    {
      if (isSelectedHour1 == true)
      {
        isSelectedHour1 = false;
        SelctionINDI = true;
      }
      else if (isSelectedMinute1 == true)
      {
        isSelectedMinute1 = false;
        SelctionINDI = true;
      }
      else if (isSelectedSecond1 == true)
      {
        isSelectedSecond1 = false;
        SelctionINDI = true;
      }
    }
    else if (currentScreen == SCREEN_SELECTED_TIME)
    {
      currentScreen = SCREEN_HOME;
      showClock();
    }
  }

  // Timer Taster Steuerung

  if (detect_timer_button_press())
  {
    if (currentScreen == SCREEN_HOME || currentScreen == SCREEN_MENU)
    {
      currentScreen = SCREEN_INDIVIDUAL_TIMER;
      showIndividualTimer();
    }
    if (currentScreen == SCREEN_INDIVIDUAL_TIMER && (selectedHour > 0 || selectedMinute > 0 || selectedSecond > 0))
    {
      currentScreen = SCREEN_EINWILLIGUNG;
      showEinwilligungScreen();
    }
    if (individualTimerGestartet)
    {
      currentScreen = SCREEN_SELECTED_TIME;
      showSelectedTimer();
    }
  }

  // Aktualisierung des TimerScreen

  if (currentScreen == SCREEN_SELECTED_TIME)
  {
    showSelectedTimer();
  }

  // Auslesen ob timer abgelaufen sind

  if (menuTimerGestartet && now >= timeout)
  {
    timerAbgelaufen(); // Timer ist abgelaufen, führe die Aktion aus
    showTimerAbgelaufen();

    // Warte 1,5 Sekunden
    delay(1500);

    // Schließe die Anzeige
    closeTimerAbgelaufen();
  }
  if (individualTimerGestartet && now >= timeout2)
  {
    timer2Abgelaufen(); // Timer ist abgelaufen, führe die Aktion aus
    showTimerAbgelaufen();

    // Warte 1,5 Sekunden
    delay(1500);

    // Schließe die Anzeige
    closeTimerAbgelaufen();
  }

  // Aktualisierung des HomeScreens

  if (currentScreen == SCREEN_HOME)
  {
    showClock();
  }

  // Debug-Informationen (falls erforderlich)

  printDebugInfo();
}
