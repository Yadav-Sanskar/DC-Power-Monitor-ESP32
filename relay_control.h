// ═══════════════════════════════════════
// relay_control.h — Menu card
// ═══════════════════════════════════════

#ifndef RELAY_CONTROL_H
#define RELAY_CONTROL_H

#include "config.h"

void  relaySetup();              // Pins initialize karo
void  relayON();                 // Load on karo
void  relayOFF();                // Load off karo
void  buzzerBeep(int times);     // Kitni baar beep karna
void  alertCheck(float amps,
                 float watts);   // Overload check karo
bool  isOverload();              // Overload hai ya nahi

#endif