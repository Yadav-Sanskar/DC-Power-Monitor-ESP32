// ═══════════════════════════════════════
// display.cpp — Asli kaam yahan
// ═══════════════════════════════════════

#include <Arduino.h>
#include "display.h"
#include <LiquidCrystal_I2C.h>

// LCD object — address 0x27, 16 columns, 2 rows
LiquidCrystal_I2C lcd(0x27, 16, 2);

void displaySetup() {
  lcd.init();
  lcd.backlight();
  lcd.clear();

  // Startup message
  lcd.setCursor(0, 0);
  lcd.print("  Power Monitor ");
  lcd.setCursor(0, 1);
  lcd.print("  Starting...   ");

  delay(1500);
  lcd.clear();

  Serial.println("Display ready.");
}

void displayData(float volts, float amps, float watts) {
  lcd.clear();

  // Row 0: Voltage aur Current
  lcd.setCursor(0, 0);
  lcd.print("V:");
  lcd.print(volts, 1);      // 1 decimal place
  lcd.print("  A:");
  lcd.print(amps, 2);       // 2 decimal places

  // Row 1: Power (Watts)
  lcd.setCursor(0, 1);
  lcd.print("Power: ");
  lcd.print(watts, 1);
  lcd.print(" W");
}

void displayAlert(const char* message) {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("!! ALERT !!");
  lcd.setCursor(0, 1);
  lcd.print(message);
}

void displayClear() {
  lcd.clear();
}