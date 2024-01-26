#include "EinwilligungScreen.h"
#include "GlobaleVariable.h"

/////////////////////////////////////////////
// Funktion zum anzeigen des Einwilligungsscreens
/////////////////////////////////////////////

void showEinwilligungScreen()
{
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);

  display.setCursor(22, 10);
  display.print("Willst du den");

  display.setCursor(22, 20);
  display.print("Timer starten?");

  display.setCursor(30, 40);

  int encoderPosition = encoder.getPosition();
  if (Selection == 0)
  {
    display.print("[Ja] - Nein");
  }
  else if (Selection == 1)
  {
    display.print("Ja - [Nein]");
  }
  lastEncoderPosition = encoderPosition;
  display.display();
}