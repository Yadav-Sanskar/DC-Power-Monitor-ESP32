// ═══════════════════════════════════════
// relay_control.cpp — Asli kaam yahan
// ═══════════════════════════════════════

#include <Arduino.h>
#include "relay_control.h"

// Ek variable — track karo overload hai ya nahi
bool overloadStatus = false;

void relaySetup() {
  pinMode(RELAY_PIN,   OUTPUT);
  pinMode(BUZZER_PIN,  OUTPUT);
  pinMode(LED_GREEN,   OUTPUT);
  pinMode(LED_RED,     OUTPUT);

  // Shuru mein relay ON, green LED on
  relayON();

  Serial.println("Relay control ready.");
}

void relayON() {
  digitalWrite(RELAY_PIN,  HIGH);
  digitalWrite(LED_GREEN,  HIGH);
  digitalWrite(LED_RED,    LOW);
  overloadStatus = false;
}

void relayOFF() {
  digitalWrite(RELAY_PIN,  LOW);
  digitalWrite(LED_GREEN,  LOW);
  digitalWrite(LED_RED,    HIGH);
  overloadStatus = true;
}

void buzzerBeep(int times) {
  for (int i = 0; i < times; i++) {
    digitalWrite(BUZZER_PIN, HIGH);
    delay(200);
    digitalWrite(BUZZER_PIN, LOW);
    delay(200);
  }
}

void alertCheck(float amps, float watts) {

  // Current limit cross hua?
  if (amps > MAX_CURRENT) {
    Serial.println("OVERLOAD — Current limit cross!");
    relayOFF();
    buzzerBeep(3);      // 3 baar beep
    return;             // Aage mat check karo
  }

  // Watt limit cross hua?
  if (watts > MAX_WATTS) {
    Serial.println("OVERLOAD — Watt limit cross!");
    relayOFF();
    buzzerBeep(3);
    return;
  }

  // Sab theek hai — relay on rakho
  if (overloadStatus == false) {
    relayON();
  }
}

bool isOverload() {
  return overloadStatus;
}