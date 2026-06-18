#include "wifi_manager.h"
#include <Arduino.h>

void wifiBaslat(const char* ssid, const char* password) {
    WiFi.softAP(ssid, password);
}

void wifiBilgiYazdir() {
    Serial.println("\n========================================");
    Serial.println("WiFi Acildi!");
    Serial.print("IP Adresi: ");
    Serial.println(WiFi.softAPIP());
    Serial.println("========================================");
}
