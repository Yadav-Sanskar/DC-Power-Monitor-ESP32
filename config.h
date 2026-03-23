// ═══════════════════════════════════════
// config.h — Saari settings ek jagah
// ═══════════════════════════════════════
// Yahan kuch change karna ho toh sirf
// is file mein aao — baaki kuch mat chhuona
// ═══════════════════════════════════════

#ifndef CONFIG_H
#define CONFIG_H

// ── Pin Definitions ──────────────────
#define ACS_PIN         36    // ACS712 output → GPIO36
#define VOLTAGE_PIN     39    // Voltage divider → GPIO39
#define LCD_SDA         21    // LCD data → GPIO21
#define LCD_SCL         22    // LCD clock → GPIO22
#define RELAY_PIN        5    // Relay control → GPIO5
#define BUZZER_PIN       4    // Buzzer → GPIO4
#define LED_GREEN        2    // Green LED → GPIO2
#define LED_RED         15    // Red LED → GPIO15

// ── ACS712 Settings ──────────────────
#define ACS_SAMPLES     500   // Kitni readings ka average lena  show noise k pata nahi chalega 
#define ACS_MIDPOINT    2.17   // Zero current pe voltage (ESP32 3.3V system)
#define ACS_SENSITIVITY 0.185 // V per Amp (5A version ke liye)

// ── Voltage Divider Settings ─────────
#define R1              10000.0  // R1 resistor value (10K ohm)
#define R2               1000.0  // R2 resistor value (1K ohm)

// ── Safety Limits ────────────────────
#define MAX_CURRENT      4.0  // Amps — is se zyada → relay off
#define MAX_WATTS       20.0  // Watts — is se zyada → alert

// ── WiFi Settings ────────────────────
#define WIFI_SSID    "Redmi12"
#define WIFI_PASS    "Jiya2023"

#endif