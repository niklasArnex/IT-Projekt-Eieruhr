#include "TimerFunktion.h"

extern bool menuTimerGestartet;
extern bool individualTimerGestartet;
extern int selectedMenuItem;
extern int selectedHour;
extern int selectedMinute;
extern int selectedSecond;
extern DateTime timeout;
extern DateTime timeout2;

/////////////////////////////////////////////
// Funktion zum Starten des MenuTimers
/////////////////////////////////////////////

void timerStarten()
{
  if (!menuTimerGestartet)
  {
    stundenMenu = fixedTimes[selectedMenuItem] / 3600000;
    minutenMenu = (fixedTimes[selectedMenuItem] % 3600000) / 60000;
    sekundenMenu = (fixedTimes[selectedMenuItem] % 60000) / 1000;
    TimeSpan timespan1(stundenMenu * 3600 + minutenMenu * 60 + sekundenMenu);
    menuTimerGestartet = true;
    DateTime now = rtc.now();
    timeout = now + timespan1;
    Serial.println("Timer gestartet!");
  }
  else
  {
    Serial.println("Timer läuft bereits!");
  }
}

/////////////////////////////////////////////
// Funktion zum Zurücksetzen des MenuTimers
/////////////////////////////////////////////

void menuTimerZuruecksetzen()
{
  menuTimerGestartet = false;
  isTimerSelected = false;
  int stundenMenu = 0; // Setzen Sie die Werte zurück oder ändern Sie sie nach Bedarf
  int minutenMenu = 0;
  int sekundenMenu = 0;
  Serial.println("Timer zurückgesetzt!");
}

/////////////////////////////////////////////
// Funktion falls MenuTimer abgelaufen
/////////////////////////////////////////////

void timerAbgelaufen()
{
  Serial.println("Timer abgelaufen!");
  // Hier können Sie den Code einfügen, den Sie beim Ablauf des Timers ausführen möchten
  menuTimerGestartet = false;     // Setze das Timer-Flag zurück
  digitalWrite(SUMMER_PIN, HIGH); // Schalte den Ausgang für 2 Sekunden ein
  delay(1500);                    // Warte 2 Sekunden
  digitalWrite(SUMMER_PIN, LOW);  // Schalte den Ausgang aus
  menuTimerZuruecksetzen();
  if (individualTimerGestartet == false)
  {
    currentScreen = SCREEN_HOME;
  }
}

/////////////////////////////////////////////
// Funktion zum Starten des IndividualTimers
/////////////////////////////////////////////

void timer2Starten()
{
  if (!individualTimerGestartet)
  {

    stundenIndi = selectedHour;
    minutenIndi = selectedMinute;
    sekundenIndi = selectedSecond;
    TimeSpan timespan2(stundenIndi * 3600 + minutenIndi * 60 + sekundenIndi);
    individualTimerGestartet = true;
    DateTime now = rtc.now();
    timeout2 = now + timespan2;
    Serial.println("Timer gestartet!");
  }
  else
  {
    Serial.println("Timer läuft bereits!");
  }
}

/////////////////////////////////////////////
// Funktion zum Zurücksetzen des IndividualTimers
/////////////////////////////////////////////

void indiTimerZuruecksetzen()
{
  individualTimerGestartet = false;

  int stundenIndi = 0; // Setzen Sie die Werte zurück oder ändern Sie sie nach Bedarf
  int minutenIndi = 0;
  int sekundenIndi = 0;
  selectedHour = 0;
  selectedMinute = 0;
  selectedSecond = 0;
  Serial.println("Timer zurückgesetzt!");
}

/////////////////////////////////////////////
// Funktion falls IndividualTimer abgelaufen
/////////////////////////////////////////////

void timer2Abgelaufen()
{
  Serial.println("Timer abgelaufen!");
  // Hier können Sie den Code einfügen, den Sie beim Ablauf des Timers ausführen möchten
  individualTimerGestartet = false; // Setze das Timer-Flag zurück
  digitalWrite(SUMMER_PIN, HIGH);   // Schalte den Ausgang für 2 Sekunden ein
  delay(1500);                      // Warte 2 Sekunden
  digitalWrite(SUMMER_PIN, LOW);    // Schalte den Ausgang aus
  indiTimerZuruecksetzen();
  if (menuTimerGestartet == false)
  {
    currentScreen = SCREEN_HOME;
  }
}

/////////////////////////////////////////////
// Funktion zum anzeigen falls ein Timer abgelaufen ist
/////////////////////////////////////////////

void showTimerAbgelaufen()
{
  currentScreen = SCREEN_ABGELAUFEN;
  // Hier kannst du den Code für die Anzeige der Timer-Abgelaufen-Meldung einfügen
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(20, 20);
  display.print("Timer abgelaufen!");
  display.display();
}

/////////////////////////////////////////////
// Funktion um die Anzeige des abgelaufenen Timers zu schließen
/////////////////////////////////////////////

void closeTimerAbgelaufen()
{
  if (menuTimerGestartet || individualTimerGestartet)
  {
    currentScreen = SCREEN_SELECTED_TIME;
    showSelectedTimer();
  }
  else if (menuTimerGestartet == false && individualTimerGestartet == false)
  {
    currentScreen = SCREEN_HOME;
    showClock();
  }
}
