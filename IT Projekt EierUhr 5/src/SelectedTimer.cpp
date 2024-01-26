#include "SelectedTimer.h"

extern DateTime timeout;
extern DateTime timeout2;
extern bool menuTimerGestartet;
extern bool individualTimerGestartet;
extern int unsigned long fixedTimes[MENU_ANZ];

/////////////////////////////////////////////
// Funktion zum anzeigen der ausgewählten Timer
/////////////////////////////////////////////

void showSelectedTimer()
{
  if (isTimerSelected == 1 && (selectedHour > 0 || selectedMinute > 0 || selectedSecond > 0) && menuTimerGestartet)
  {
    DateTime now = rtc.now();
    TimeSpan verbleibendeZeit = (now < timeout) ? (timeout - now) : TimeSpan(0);
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(WHITE);

    display.setCursor(0, 0);
    display.print(menu[selectedMenuItem]);

    // Umrechnung der ausgewählten Zeit in Stunden, Minuten und Sekunden
    unsigned long selectedHour1 = fixedTimes[selectedMenuItem] / 3600000;
    unsigned long selectedMinute1 = (fixedTimes[selectedMenuItem] % 3600000) / 60000;
    unsigned long selectedSecond1 = (fixedTimes[selectedMenuItem] % 60000) / 1000;

    display.setCursor(0, 10);
    display.print(verbleibendeZeit.hours());
    display.print("h ");
    display.print(verbleibendeZeit.minutes());
    display.print("m ");
    display.print(verbleibendeZeit.seconds());
    display.print("s ");

    TimeSpan verbleibendeZeit2 = (now < timeout2) ? (timeout2 - now) : TimeSpan(0);
    display.setCursor(0, 40);
    display.print("Eigener Timer");
    display.setCursor(0, 50);
    display.print(verbleibendeZeit2.hours());
    display.print("h ");
    display.print(verbleibendeZeit2.minutes());
    display.print("m ");
    display.print(verbleibendeZeit2.seconds());
    display.print("s ");
  }

  if (isTimerSelected == 0 && (selectedHour > 0 || selectedMinute > 0 || selectedSecond > 0))
  {
    DateTime now = rtc.now();
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(WHITE);

    display.setCursor(0, 0);
    display.print("Kein weiterer");
    display.setCursor(0, 10);
    display.print("Timer eingestellt");
    TimeSpan verbleibendeZeit2 = (now < timeout2) ? (timeout2 - now) : TimeSpan(0);

    display.setCursor(0, 40);
    display.print("Eigener Timer");
    display.setCursor(0, 50);
    display.print(verbleibendeZeit2.hours());
    display.print("h ");
    display.print(verbleibendeZeit2.minutes());
    display.print("m ");
    display.print(verbleibendeZeit2.seconds());
    display.print("s ");
  }

  if (isTimerSelected == 1 && selectedHour == 0 && selectedMinute == 0 && selectedSecond == 0 && menuTimerGestartet)
  {
    DateTime now = rtc.now();
    TimeSpan verbleibendeZeit = (now < timeout) ? (timeout - now) : TimeSpan(0);
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(WHITE);

    display.setCursor(0, 0);
    display.print(menu[selectedMenuItem]);

    // Umrechnung der ausgewählten Zeit in Stunden, Minuten und Sekunden
    unsigned long selectedHour1 = fixedTimes[selectedMenuItem] / 3600000;
    unsigned long selectedMinute1 = (fixedTimes[selectedMenuItem] % 3600000) / 60000;
    unsigned long selectedSecond1 = (fixedTimes[selectedMenuItem] % 60000) / 1000;

    display.setCursor(0, 10);
    display.print(verbleibendeZeit.hours());
    display.print("h ");
    display.print(verbleibendeZeit.minutes());
    display.print("m ");
    display.print(verbleibendeZeit.seconds());
    display.print("s ");

    display.setCursor(0, 40);
    display.print("Kein eigener ");
    display.setCursor(0, 50);
    display.print("Timer eingestellt");
  }

  display.display();
}

/////////////////////////////////////////////
// Funktion zum updaten der ausgewählten Zeiten
/////////////////////////////////////////////

void updateSelectedValue()
{
  if (isSelectedHour)
  {
    if (selectedHour < 23)
    {
      selectedHour++;
    }
    else
    {
      selectedHour = 0;
    }
    showSelectedTimer();
  }
  else if (isSelectedMinute)
  {
    if (selectedMinute < 59)
    {
      selectedMinute++;
    }
    else
    {
      selectedMinute = 0;
    }
    showSelectedTimer();
  }
  else if (isSelectedSecond)
  {
    if (selectedSecond < 59)
    {
      selectedSecond++;
    }
    else
    {
      selectedSecond = 0;
    }
    showSelectedTimer();
  }
}

/////////////////////////////////////////////
// Funktion zum anzeigen der Einstellung des individuellen Timers
/////////////////////////////////////////////

void showIndividualTimer()
{
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(WHITE);

  if (Selection2 == 0)
  {
    display.setCursor(0, 0);
    display.print("[H]");
    display.setCursor(40, 0);
    display.print(" M. ");
    display.setCursor(80, 0);
    display.print(" S. ");
  }
  else if (Selection2 == 1)
  {
    display.setCursor(0, 0);
    display.print("H. ");
    display.setCursor(40, 0);
    display.print("[M]");
    display.setCursor(80, 0);
    display.print(" S. ");
  }
  else if (Selection2 == 2)
  {
    display.setCursor(0, 0);
    display.print("H. ");
    display.setCursor(40, 0);
    display.print(" M. ");
    display.setCursor(80, 0);
    display.print("[S]");
  }

  display.setCursor(0, 30);
  display.print(selectedHour <= 99 ? "" : "");
  display.print(selectedHour);

  display.setCursor(45, 30);
  display.print(selectedMinute <= 59 ? "" : "");
  display.print(selectedMinute);

  display.setCursor(90, 30);
  display.print(selectedSecond <= 59 ? "" : "");
  display.print(selectedSecond);

  display.display();
}
