#include "EncoderFunktion.h"
#include "TimerFunktion.h"

RotaryEncoder encoder(CLK_PIN, DT_PIN);

/////////////////////////////////////////////
// Funktion zur Überprüfung des Encoders
/////////////////////////////////////////////

void checkEncoderPosition()
{
  int encoderPosition = encoder.getPosition();

  if (currentScreen == SCREEN_MENU)
  {
    if (encoderPosition > lastEncoderPosition)
    {
      // Scrolling nach unten
      selectedMenuItem = (selectedMenuItem + 1) % MENU_ANZ;
      showMenu();
    }
    else if (encoderPosition < lastEncoderPosition)
    {
      // Scrolling nach oben
      selectedMenuItem = (selectedMenuItem - 1 + MENU_ANZ) % MENU_ANZ;
      showMenu();
    }

    lastEncoderPosition = encoderPosition;
  }
  if (currentScreen == SCREEN_INDIVIDUAL_TIMER)
  {
    if (encoderPosition > lastEncoderPosition)
    {
      // Rechtsdrehung: Inkrementiere die ausgewählte Zeit
      if (SelctionINDI)
      {
        Selection2 = (Selection2 + 1) % 3;
        showIndividualTimer();
      }
      if (isSelectedHour1)
      {
        if (selectedHour < 99)
        {
          selectedHour++;
        }
        else
        {
          selectedHour = 0;
        }
        showIndividualTimer();
      }
      else if (isSelectedMinute1)
      {
        if (selectedMinute < 59)
        {
          selectedMinute++;
        }
        else
        {
          selectedMinute = 0;
        }
        showIndividualTimer();
      }
      else if (isSelectedSecond1)
      {
        if (selectedSecond < 59)
        {
          selectedSecond++;
        }
        else
        {
          selectedSecond = 0;
        }
        showIndividualTimer();
      }
    }
    else if (encoderPosition < lastEncoderPosition)
    {
      // Linksdrehung: Dekrementiere die ausgewählte Zeit
      if (isSelectedHour1)
      {
        if (selectedHour > 0)
        {
          selectedHour--;
        }
        else
        {
          selectedHour = 99;
        }
        showIndividualTimer();
      }
      else if (isSelectedMinute1)
      {
        if (selectedMinute > 0)
        {
          selectedMinute--;
        }
        else
        {
          selectedMinute = 59;
        }
        showIndividualTimer();
      }
      else if (isSelectedSecond1)
      {
        if (selectedSecond > 0)
        {
          selectedSecond--;
        }
        else
        {
          selectedSecond = 59;
        }
        showIndividualTimer();
      }
      if (SelctionINDI)
      {
        Selection2 = (Selection2 - 1 + 3) % 3;
        showIndividualTimer();
      }
    }
    lastEncoderPosition = encoderPosition;
  }
  if (currentScreen == SCREEN_EINWILLIGUNG)
  {
    if (encoderPosition > lastEncoderPosition)
    {
      Selection = 0;
      showEinwilligungScreen();
    }
    else if (encoderPosition < lastEncoderPosition)
    {
      Selection = 1;
      showEinwilligungScreen();
    }
    lastEncoderPosition = encoderPosition;
  }
}