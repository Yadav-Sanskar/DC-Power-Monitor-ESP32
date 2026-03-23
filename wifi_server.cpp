// ═══════════════════════════════════════
// wifi_server.cpp — Asli kaam yahan
// ═══════════════════════════════════════

#include <Arduino.h>
#include "wifi_server.h"

// Server object — port 80 (normal browser port)
WebServer server(80);

// Latest readings store karne ke liye
float _volts   = 0;
float _amps    = 0;
float _watts   = 0;
bool  _overload = false;

// ── Dashboard HTML ──────────────────────
// Yeh poora webpage hai jo phone pe dikhega
const char* dashboardHTML = R"rawhtml(
<!DOCTYPE html>
<html>
<head>
  <meta charset="UTF-8">
  <meta name="viewport" content="width=device-width, initial-scale=1">
  <title>Power Monitor</title>
  <style>
    body {
      font-family: Arial, sans-serif;
      background: #1a1a2e;
      color: white;
      text-align: center;
      padding: 20px;
      margin: 0;
    }
    h1 { color: #e94560; font-size: 24px; }

    .card {
      background: #16213e;
      border-radius: 12px;
      padding: 20px;
      margin: 12px auto;
      max-width: 300px;
    }
    .label {
      font-size: 13px;
      color: #aaa;
      margin-bottom: 6px;
    }
    .value {
      font-size: 36px;
      font-weight: bold;
      color: #0f3460;
    }
    .volt  { color: #4ecca3; }
    .amp   { color: #e94560; }
    .watt  { color: #f5a623; }

    .status-ok    { color: #4ecca3; font-size: 18px; }
    .status-alert { color: #e94560; font-size: 18px; }

    .footer {
      font-size: 11px;
      color: #555;
      margin-top: 24px;
    }
  </style>

  <script>
    // Har 2 second mein data refresh karo
    function fetchData() {
      fetch('/data')
        .then(r => r.json())
        .then(d => {
          document.getElementById('volt').innerText  = d.volts.toFixed(1)  + ' V';
          document.getElementById('amp').innerText   = d.amps.toFixed(2)   + ' A';
          document.getElementById('watt').innerText  = d.watts.toFixed(1)  + ' W';
          document.getElementById('status').innerText   = d.overload ? 'OVERLOAD!' : 'Normal';
          document.getElementById('status').className   = d.overload ? 'status-alert' : 'status-ok';
        });
    }
    setInterval(fetchData, 2000);
    fetchData();
  </script>
</head>

<body>
  <h1>⚡ DC Power Monitor</h1>

  <div class="card">
    <div class="label">Voltage</div>
    <div class="value volt" id="volt">-- V</div>
  </div>

  <div class="card">
    <div class="label">Current</div>
    <div class="value amp" id="amp">-- A</div>
  </div>

  <div class="card">
    <div class="label">Power</div>
    <div class="value watt" id="watt">-- W</div>
  </div>

  <div class="card">
    <div class="label">Status</div>
    <div class="status-ok" id="status">Connecting...</div>
  </div>

  <div class="footer">Auto refresh every 2 seconds</div>
</body>
</html>
)rawhtml";

// ── Functions ───────────────────────────

void handleDashboard() {
  server.send(200, "text/html", dashboardHTML);
}

void handleData() {
  // JSON format mein data bhejo
  String json = "{";
  json += "\"volts\":"   + String(_volts, 2)  + ",";
  json += "\"amps\":"    + String(_amps, 3)   + ",";
  json += "\"watts\":"   + String(_watts, 2)  + ",";
  json += "\"overload\":" + String(_overload ? "true" : "false");
  json += "}";

  server.send(200, "application/json", json);
}

void wifiSetup() {
  Serial.print("WiFi se connect ho raha hai");

  WiFi.begin(WIFI_SSID, WIFI_PASS);

  // Connect hone tak wait karo
  int tries = 0;
  while (WiFi.status() != WL_CONNECTED && tries < 40) {
    delay(500);
    Serial.print(".");
    tries++;
  }

  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("\nConnected!");
    Serial.print("Phone mein yeh address open karo: http://");
    Serial.println(WiFi.localIP());
  } else {
    Serial.println("\nWiFi connect nahi hua — sirf LCD mode mein chalega.");
  }

  // Routes register karo
  server.on("/",     handleDashboard);  // Browser se / maange → HTML bhejo
  server.on("/data", handleData);       // Browser se /data maange → JSON bhejo

  server.begin();
}

void wifiHandle() {
  server.handleClient();    // Incoming requests check karo
}

void wifiUpdateData(float v, float a, float w, bool overload) {
  _volts   = v;
  _amps    = a;
  _watts   = w;
  _overload = overload;
}


// ## Yahan 2 Naye Concepts Hain

// **1. R"rawhtml( )rawhtml" kya hai?**

// Yeh ek raw string hai — iske andar quotes, slashes, sab kuch as-is likha ja sakta hai bina escape kiye. Poora HTML iske andar hai.

// **2. `/data` route kya hai?**

// Dashboard ke 2 parts hain:
// ```
// Browser /        maange → poora HTML page mile
// Browser /data    maange → sirf numbers mile (JSON)