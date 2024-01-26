#include "Menuscreen.h"
#include "GlobaleVariable.h"

// Annahme: Definition der globalen Variablen
extern int selectedMenuItem;
extern int currentScreen;

const char *menu[MENU_ANZ] = {
    "Eier",
    "Pizza",
    "Ente",
    "Ofen",
    "Soße",
    "Kuchen",
    "Kaffee",
    "Schokolade",
    "Waffel",
    "Stoppuhr",
};

/////////////////////////////////////////////
// Feste Zeiten für jeden Menüeintrag (in Millisekunden)
/////////////////////////////////////////////

unsigned long fixedTimes[MENU_ANZ] =
    {
        300000,  // Beispiel: 5 Minuten für "Eier"
        900000,  // Beispiel: 15 Minuten für "Pizza"
        3600000, // Beispiel: 1 Stunde für "Ente"
        180000,  // Beispiel: 3 Minuten für "Ofen"
        600000,  // Beispiel: 10 Minuten für "Soße"
        15000,   // Beispiel: 15 Sekunden für "Kuchen"
        360000,  // Beispiel: 6 Minuten für "Kaffee"
        420000,  // Beispiel: 7 Minuten für "Schokolade"
        480000,  // Beispiel: 8 Minuten für "Waffel"
        60000    // Beispiel: 1 Minute für "Stoppuhr"
};

/////////////////////////////////////////////
// Funktion zum anzeigen des Menus
/////////////////////////////////////////////

void showMenu()
{
  display.clearDisplay();
  display.setTextSize(1);

  int startIndex = selectedMenuItem > 5 ? selectedMenuItem - 5 : 0;

  for (int i = startIndex; i < startIndex + 6 && i < MENU_ANZ; i++)
  {
    if (i == selectedMenuItem && currentScreen == SCREEN_MENU)
    {
      display.setTextColor(BLACK, WHITE);
    }
    else
    {
      display.setTextColor(WHITE);
    }

    display.setCursor(0, (i - startIndex) * 10);
    display.print(menu[i]);

    // Anzeigen der zugehörigen Uhrzeit (rechts)
    display.setCursor(64, (i - startIndex) * 10);

    // Überprüfen Sie, ob der Index innerhalb des gültigen Bereichs liegt
    if (i < MENU_ANZ)
    {
      // Anzeigen der vordefinierten Zeit, unabhängig von benutzerdefinierten Zeiten
      unsigned long hours = fixedTimes[i] / 3600000;
      unsigned long minutes = (fixedTimes[i] % 3600000) / 60000;
      unsigned long seconds = (fixedTimes[i] % 60000) / 1000;

      display.print(hours);
      display.print("h ");
      display.print(minutes);
      display.print("m ");
      display.print(seconds);
      display.print("s");
    }
  }

  display.display();
}
