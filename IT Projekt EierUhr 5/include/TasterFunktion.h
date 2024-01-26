// TasterFunktion.h
#ifndef TASTER_FUNKTION_H
#define TASTER_FUNKTION_H

#include "GlobaleVariable.h"

/////////////////////////////////////////////
// Funktion zum auslesen des SW_PIN
/////////////////////////////////////////////
int detect_button_press()
{
  if (LOW == digitalRead(SW_PIN))
  {
    btn_pressed = 1;
  }
  else
  {
    if (btn_pressed)
    {
      btn_counter++;
      btn_pressed = 0;
      return true;
    }
  }
  return false;
}
/////////////////////////////////////////////
// Funktion zum auslesen des Tasters
/////////////////////////////////////////////

int detect_timer_button_press()
{
  if (HIGH == digitalRead(TIMER_PIN))
  {
    tmrbtn_pressed = 1;
  }
  else
  {
    if (tmrbtn_pressed)
    {
      tmrbtn_counter++;
      tmrbtn_pressed = 0;
      return true;
    }
  }
  return false;
}

#endif // TASTER_FUNKTION_H