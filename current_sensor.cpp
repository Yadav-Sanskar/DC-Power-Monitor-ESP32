// ═══════════════════════════════════════
// current_sensor.cpp — Asli kaam yahan
// ═══════════════════════════════════════

#include <Arduino.h>
#include "current_sensor.h"

void currentSensorSetup() {
  // GPIO36 automatically ADC mode mein hota hai
  // Kuch special setup nahi chahiye ACS712 ke liye
  // Bas ek message print karte hain confirm karne ke liye
  Serial.println("Current sensor ready.");
}

float readCurrent() {
  long sum = 0;

  // 500 readings ka average — noise filter hoti hai
  for (int i = 0; i < ACS_SAMPLES; i++) {
    sum += analogRead(ACS_PIN);
  }

  float avg     = (float)sum / ACS_SAMPLES;
  float voltage = (avg / 4095.0) * 3.3;
  float current = (voltage - ACS_MIDPOINT) / ACS_SENSITIVITY;

  // Noise floor — 0.05A se kam ko zero maano
  if (abs(current) < 0.05) current = 0.0;

  return current;
}



// ## Kya Ho Raha Hai Yahan

// `readCurrent()` ke andar 3 kaam hote hain:
// ```
// ADC number → Voltage → Amps
//   (0-4095)   (0-3.3V)  (actual current)