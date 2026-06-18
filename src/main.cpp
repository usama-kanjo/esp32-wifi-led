#include <Arduino.h>
#include "wifi_manager.h"
#include "web_server.h"
#include "dns_captive.h"
#include "pin_config.h"

const char* ssid = "ESP32_WiFi";
const char* password = "12345678";

void setup() {
    Serial.begin(115200);
    
    pinMode(LED_PIN, OUTPUT);
    digitalWrite(LED_PIN, LOW);

    wifiBaslat(ssid, password);
    wifiBilgiYazdir();

    dnsBaslat(WiFi.softAPIP());
    serverBaslat();

    Serial.println("Sistem basladi!");
}

void loop() {
    dnsIsle();
    server.handleClient();
}
