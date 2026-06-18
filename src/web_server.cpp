#include "web_server.h"
#include "html_page.h"
#include <WiFi.h>
#include <Arduino.h>

WebServer server(80);
bool ledState = false;

void handleRoot() {
    server.send(200, "text/html", getHTML(ledState));
}

void ledOn() {
    ledState = true;
    digitalWrite(2, HIGH);
    server.sendHeader("Location", "/");
    server.send(302, "text/plain", "Redirecting...");
}

void ledOff() {
    ledState = false;
    digitalWrite(2, LOW);
    server.sendHeader("Location", "/");
    server.send(302, "text/plain", "Redirecting...");
}

void handleCaptivePortal() {
    server.send(200, "text/html", getHTML(ledState));
}

void handleNotFound() {
    server.sendHeader("Location", "http://" + WiFi.softAPIP().toString() + "/");
    server.send(302, "text/plain", "Redirecting...");
}

void serverSetupRoutes() {
    server.on("/", handleRoot);
    server.on("/led/on", ledOn);
    server.on("/led/off", ledOff);
    
    // Captive portal test URLs
    server.on("/generate_204", handleCaptivePortal);
    server.on("/ncsi.txt", handleCaptivePortal);
    server.on("/hotspot-detect.html", handleCaptivePortal);
    server.on("/library/test/success.html", handleCaptivePortal);
    server.on("/connectivitycheck.gstatic.com", handleCaptivePortal);
    
    server.onNotFound(handleNotFound);
}

void serverStart() {
    serverSetupRoutes();
    server.begin();
}
