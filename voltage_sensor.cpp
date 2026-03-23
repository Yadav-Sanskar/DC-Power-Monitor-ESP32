// ═══════════════════════════════════════
// voltage_sensor.cpp — Asli kaam yahan
// ═══════════════════════════════════════
#include <Arduino.h>
#include "voltage_sensor.h"

void voltageSensorSetup() {
  Serial.println("Voltage sensor ready.");
}

float readVoltage() {
  long sum = 0;

  // Current sensor jaisa — 500 readings ka average
  for (int i = 0; i < ACS_SAMPLES; i++) {
    sum += analogRead(VOLTAGE_PIN);
  }

  float avg        = (float)sum / ACS_SAMPLES;

  // ADC → actual voltage at pin
  float pinVoltage = (avg / 4095.0) * 3.3;

  // Voltage divider formula reverse karo
  // V_actual = V_pin x (R1 + R2) / R2
  float actualVoltage = pinVoltage * (R1 + R2) / R2;

  actualVoltage = actualVoltage / 10.0;  // Scale fix

  // Noise floor — 0.1V se kam ko zero maano
  if (actualVoltage < 0.1) actualVoltage = 0.0;

  return actualVoltage;
}




// ## Yahan Ek Naya Concept Hai — Voltage Divider Reverse Formula

// Blueprint mein tune padha tha voltage divider kaise voltage kam karta hai:
// ```
// V_pin = V_actual x R2 / (R1 + R2)
// ```

// Lekin humein ulta karna hai — pin ki voltage se actual battery voltage nikalna hai:
// ```
// V_actual = V_pin x (R1 + R2) / R2
// ```

// **Example:** Agar battery 12V hai aur R1=10K, R2=1K:
// ```
// V_pin     = 12 x 1000/11000 = 1.09V   (yeh ESP32 padhega)
// V_actual  = 1.09 x 11000/1000 = 12V   (yeh hum calculate karenge)
// ```

// `config.h` mein R1 aur R2 already define hain — isliye yahan directly use kar liye. Agar resistor values change karni ho, sirf `config.h` mein jao.
