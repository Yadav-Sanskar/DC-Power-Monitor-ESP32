// ═══════════════════════════════════════
// wifi_server.h — Menu card
// ═══════════════════════════════════════

#ifndef WIFI_SERVER_H
#define WIFI_SERVER_H

#include "config.h"
#include <WiFi.h>
#include <WebServer.h>

void wifiSetup();                           // WiFi connect karo
void wifiHandle();                          // Requests suno — loop mein chalega
void wifiUpdateData(float v,
                    float a,
                    float w,
                    bool overload);         // Fresh data do server ko

#endif