#include "lang.h"

static Lang preferredLang = LANG_EN;

static const char* const strings[LANG_COUNT][S_COUNT] = {
    {
        "ESP32 LED Control",
        "LED: %s",
        "ON",
        "OFF",
        "LED ON",
        "LED OFF",
        "Effect: %s",
        "Brightness",
        "Toggle",
        "Türkçe",
        "English"
    },
    {
        "ESP32 LED Kontrol",
        "LED: %s",
        "AÇIK",
        "KAPALI",
        "LED AÇ",
        "LED KAPA",
        "Efekt: %s",
        "Parlaklık",
        "Aç/Kapa",
        "Türkçe",
        "English"
    }
};

const char* langStr(byte id, Lang lang) {
    if (id >= S_COUNT || lang >= LANG_COUNT) return "";
    return strings[lang][id];
}

Lang detectLang(const String& acceptLanguage) {
    if (acceptLanguage.indexOf("tr") >= 0 || acceptLanguage.indexOf("TR") >= 0) {
        return LANG_TR;
    }
    return LANG_EN;
}

void setPreferredLang(Lang lang) {
    if (lang < LANG_COUNT) preferredLang = lang;
}

Lang getPreferredLang() {
    return preferredLang;
}
