# DC Power Monitor — ESP32

Real-time DC energy monitoring system built on ESP32 with 
ACS712 current sensing, automated overload protection, 
and WiFi-hosted live web dashboard.

## Features
- Real-time voltage, current & power measurement
- 16x2 LCD live display (I2C)
- WiFi web dashboard — no external cloud needed
- Automatic relay cutoff on overload
- Buzzer + LED alert system
- Modular firmware architecture

## Hardware Used
- ESP32 NodeMCU 38-pin
- ACS712 5A Current Sensor
- ZMPT101B / Voltage Divider (10K + 1K)
- 16x2 LCD with I2C (0x27)
- 5V Relay Module
- BC547 NPN Transistor
- Passive Buzzer, LED, Resistors

## Pin Connections
| Component     | ESP32 Pin     |
|---------------|---------------|
| ACS712 OUT    | GPIO36 (VP)   |
| Voltage Div   | GPIO39 (VN)   |
| LCD SDA       | GPIO21        |
| LCD SCL       | GPIO22        |
| Relay (BC547) | GPIO5         |
| Buzzer        | GPIO4         |
| Green LED     | GPIO2         |

## Circuit Working
1. ACS712 measures current (Hall Effect — series connection)
2. Voltage divider scales supply voltage for ESP32 ADC
3. ESP32 calculates Power = V x I
4. LCD displays live readings
5. WiFi web server hosts dashboard on phone browser
6. Relay auto-cuts load on overload (>4.5A or >20W)

## Libraries Required
- LiquidCrystal_I2C (Frank de Brabander)

## Skills Demonstrated
ESP32 · Embedded C++ · ADC · I2C Protocol · 
WiFi Web Server · Sensor Calibration · Relay Control
