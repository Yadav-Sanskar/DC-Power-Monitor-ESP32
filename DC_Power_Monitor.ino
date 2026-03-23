// ═══════════════════════════════════════
// DC_Power_Monitor.ino — Boss file
// ═══════════════════════════════════════

#include "current_sensor.h"
#include "voltage_sensor.h"
#include "display.h"
#include "relay_control.h"
#include "wifi_server.h"

// ── Data variables ───────────────────────
float volts = 0;
float amps  = 0;
float watts = 0;

// ── Timing variables ────────────────────
unsigned long lastSensorRead    = 0;
unsigned long lastDisplayUpdate = 0;
unsigned long lastRelayTest     = 0;

// ── Intervals ───────────────────────────
#define SENSOR_INTERVAL      500
#define DISPLAY_INTERVAL     1000
#define RELAY_TEST_INTERVAL  3000

// ── Relay test state ─────────────────────
bool relayTestState = false;

// ════════════════════════════════════════
void setup() {
  Serial.begin(115200);
  Serial.println("\n=== DC Power Monitor Starting ===");

  currentSensorSetup();
  voltageSensorSetup();
  displaySetup();
  relaySetup();
  wifiSetup();

  Serial.println("=== Sab ready hai! ===\n");
}

// ════════════════════════════════════════
void loop() {
  unsigned long now = millis();

  // ── Sensor reading — har 500ms ──────
  if (now - lastSensorRead >= SENSOR_INTERVAL) {
    lastSensorRead = now;

    amps  = readCurrent();
    volts = readVoltage();
    watts = volts * amps;

    if (watts < 0) watts = 0;

    alertCheck(amps, watts);
    wifiUpdateData(volts, amps, watts, isOverload());

    Serial.print("V: "); Serial.print(volts, 1);
    Serial.print(" | A: "); Serial.print(amps, 3);
    Serial.print(" | W: "); Serial.print(watts, 1);
    Serial.print(" | Overload: ");
    Serial.println(isOverload() ? "YES" : "NO");
  }

  // ── Display update — har 1 second ───
  if (now - lastDisplayUpdate >= DISPLAY_INTERVAL) {
    lastDisplayUpdate = now;

    if (isOverload()) {
      displayAlert("Overload!");
    } else {
      displayData(volts, amps, watts);
    }
  }

  // ── Relay + Buzzer test — har 3 second ───
  if (now - lastRelayTest >= RELAY_TEST_INTERVAL) {
    lastRelayTest = now;

    if (relayTestState == false) {
      relayON();
      buzzerBeep(1);
      Serial.println(">> Relay ON — Green LED on");
      relayTestState = true;

    } else {
      relayOFF();
      buzzerBeep(2);
      Serial.println(">> Relay OFF — Red LED on");
      relayTestState = false;
    }
  }

  // ── WiFi requests ───────────────────
  wifiHandle();
}