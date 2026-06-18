#include "web_server.h"
#include "html_page.h"
#include <WiFi.h>
#include <Arduino.h>

WebServer server(80);
bool ledDurum = false;

void anaSayfa() {
    server.send(200, "text/html", getHTML(ledDurum));
}

void ledAc() {
    ledDurum = true;
    digitalWrite(2, HIGH);
    server.sendHeader("Location", "/");
    server.send(302, "text/plain", "Yonlendiriliyor...");
}

void ledKapat() {
    ledDurum = false;
    digitalWrite(2, LOW);
    server.sendHeader("Location", "/");
    server.send(302, "text/plain", "Yonlendiriliyor...");
}

void handleCaptivePortal() {
    server.send(200, "text/html", getHTML(ledDurum));
}

void handleNotFound() {
    server.sendHeader("Location", "http://" + WiFi.softAPIP().toString() + "/");
    server.send(302, "text/plain", "Yonlendiriliyor...");
}

void serverRotalariEkle() {
    server.on("/", anaSayfa);
    server.on("/led/ac", ledAc);
    server.on("/led/kapat", ledKapat);
    
    // Captive portal test URL'leri
    server.on("/generate_204", handleCaptivePortal);
    server.on("/ncsi.txt", handleCaptivePortal);
    server.on("/hotspot-detect.html", handleCaptivePortal);
    server.on("/library/test/success.html", handleCaptivePortal);
    server.on("/connectivitycheck.gstatic.com", handleCaptivePortal);
    
    server.onNotFound(handleNotFound);
}

void serverBaslat() {
    serverRotalariEkle();
    server.begin();
}
