#include "wifi_manager.h"
#include <Arduino.h>

void wifiStart(const char* ssid, const char* password) {
    WiFi.softAP(ssid, password);
}

void wifiPrintInfo() {
    Serial.println("\n========================================");
    Serial.println("WiFi Started!");
    Serial.print("IP Address: ");
    Serial.println(WiFi.softAPIP());
    Serial.println("========================================");
}
