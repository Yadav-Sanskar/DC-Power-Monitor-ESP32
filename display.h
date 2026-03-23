// ═══════════════════════════════════════
// display.h — Menu card
// ═══════════════════════════════════════

#ifndef DISPLAY_H
#define DISPLAY_H

#include "config.h"

void displaySetup();                        // LCD initialize karo
void displayData(float volts,
                 float amps,
                 float watts);              // Normal data dikhao
                 
void displayAlert(const char* message);    // Alert message dikhao
void displayClear();                        // Screen saaf karo

#endif