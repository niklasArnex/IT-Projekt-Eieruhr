#include "Debug.h"
#include "EncoderFunktion.h"
#include "GlobaleVariable.h"

/////////////////////////////////////////////
// Funktion zum anzeigen der DEBUG ausgaben am seriellen Monitor
/////////////////////////////////////////////

void printDebugInfo()
{
  // Debug information (if needed)
  static unsigned long lastDebugPrint = 0;
  static unsigned long lastPin25Print = 0;

  if (millis() - lastDebugPrint > 500)
  {
    lastDebugPrint = millis();

    DEBUG_PRINT("CLK_PIN state: ");
    DEBUG_PRINTLN(digitalRead(CLK_PIN));

    DEBUG_PRINT("DT_PIN state: ");
    DEBUG_PRINTLN(digitalRead(DT_PIN));

    // Anzeigen der Encoder-Position
    DEBUG_PRINT("Encoder Position: ");
    DEBUG_PRINTLN(encoder.getPosition());
  }

  if (millis() - lastPin25Print > 500)
  {
    lastPin25Print = millis();

    if (digitalRead(33) == LOW)
    {
      DEBUG_PRINTLN("Pin 33 pressed: 1");
      // Wenn Pin 33 gedrückt wird, wechsle von SCREEN_HOME zu SCREEN_MENU
      lastActivityTime = millis();
    }
    else
    {
      DEBUG_PRINTLN("Pin 33 not pressed: 0");
    }
    if (digitalRead(16) == HIGH)
    {
      DEBUG_PRINTLN("TIMER_PIN pressed: 1");
    }
    else
    {
      DEBUG_PRINTLN("TIMER_PIN not pressed: 0");
    }
    // Debug-Ausgaben für Auswahl und Zustände hier einfügen
    DEBUG_PRINT("Current Screen: ");
    DEBUG_PRINTLN(currentScreen);
    DEBUG_PRINT("Timer gestartet: ");
    DEBUG_PRINTLN(menuTimerGestartet);
    DEBUG_PRINT("Stunden: ");
    DEBUG_PRINTLN(selectedHour);
    DEBUG_PRINT("Minuten: ");
    DEBUG_PRINTLN(selectedMinute);
    DEBUG_PRINT("Sekunden: ");
    DEBUG_PRINTLN(selectedSecond);
    DEBUG_PRINT("SelctionINDI: ");
    DEBUG_PRINTLN(SelctionINDI);
    DEBUG_PRINT("TimerSelected: ");
    DEBUG_PRINTLN(isTimerSelected);
  }
}
