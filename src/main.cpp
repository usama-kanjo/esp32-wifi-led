#include <Arduino.h>
#include "wifi_manager.h"
#include "web_server.h"
#include "dns_captive.h"
#include "pin_config.h"
#include "led_effects.h"
#include "button.h"

const char* ssid = "ESP32_WiFi";
const char* password = "12345678";

void setup() {
    Serial.begin(115200);

    ledEffectsSetup();
    buttonSetup();

    wifiStart(ssid, password);
    wifiPrintInfo();

    dnsStart(WiFi.softAPIP());
    serverStart();

    Serial.println("System started!");
}

void loop() {
    buttonLoop();
    ledEffectsLoop();
    dnsProcess();
    server.handleClient();
}
