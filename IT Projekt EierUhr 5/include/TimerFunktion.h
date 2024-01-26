#ifndef TIMER_FUNKTION_H
#define TIMER_FUNKTION_H

#include "GlobaleVariable.h"

extern int unsigned long fixedTimes[MENU_ANZ];

void timerStarten();
void menuTimerZuruecksetzen();
void timerAbgelaufen();

void timer2Starten();
void indiTimerZuruecksetzen();
void timer2Abgelaufen();

void showTimerAbgelaufen();
void closeTimerAbgelaufen();

void showClock();
void showSelectedTimer();

#endif // TIMER_FUNKTION_H