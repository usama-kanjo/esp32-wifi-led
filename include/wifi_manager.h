#ifndef WIFI_MANAGER_H
#define WIFI_MANAGER_H

#include <WiFi.h>

void wifiStart(const char* ssid, const char* password);
void wifiPrintInfo();

#endif
