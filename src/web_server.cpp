#include "web_server.h"
#include "html_page.h"
#include "led_effects.h"
#include "lang.h"
#include <WiFi.h>
#include <Arduino.h>

WebServer server(80);

static String redirectLang() {
    if (server.hasArg("lang")) {
        String l = server.arg("lang");
        if (l == "tr" || l == "ar") return "?lang=" + l;
    }
    return "";
}

void handleRoot() {
    Lang lang = detectLang(server.header("Accept-Language"));
    if (server.hasArg("lang")) {
        String l = server.arg("lang");
        if (l == "tr") lang = LANG_TR;
        else if (l == "ar") lang = LANG_AR;
        else if (l == "en") lang = LANG_EN;
    }
    server.send(200, "text/html", getHTML(getLedState(), getCurrentEffect(), getBrightness(), lang));
}

void ledOn() {
    setLedState(true);
    server.sendHeader("Location", "/" + redirectLang());
    server.send(302, "text/plain", "Redirecting...");
}

void ledOff() {
    setLedState(false);
    server.sendHeader("Location", "/" + redirectLang());
    server.send(302, "text/plain", "Redirecting...");
}

void handleToggle() {
    toggleLed();
    server.sendHeader("Location", "/" + redirectLang());
    server.send(302, "text/plain", "Redirecting...");
}

void handleEffect() {
    if (server.hasArg("id")) {
        int id = server.arg("id").toInt();
        if (id >= 0 && id < EFFECT_COUNT) {
            setEffect((Effect)id);
        }
    }
    if (server.hasArg("bri")) {
        int bri = server.arg("bri").toInt();
        if (bri >= 0 && bri <= 255) {
            setBrightness((uint8_t)bri);
        }
    }
    server.sendHeader("Location", "/" + redirectLang());
    server.send(302, "text/plain", "Redirecting...");
}

void handleSetLang() {
    server.sendHeader("Location", "/");
    server.send(302, "text/plain", "Redirecting...");
}

void handleCaptivePortal() {
    handleRoot();
}

void handleNotFound() {
    server.sendHeader("Location", "http://" + WiFi.softAPIP().toString() + "/");
    server.send(302, "text/plain", "Redirecting...");
}

void serverSetupRoutes() {
    server.on("/", handleRoot);
    server.on("/led/on", ledOn);
    server.on("/led/off", ledOff);
    server.on("/led/toggle", handleToggle);
    server.on("/effect", handleEffect);
    server.on("/lang", handleSetLang);

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
