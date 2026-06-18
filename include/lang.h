#ifndef LANG_H
#define LANG_H

#include <Arduino.h>

enum Lang { LANG_EN, LANG_TR, LANG_AR, LANG_COUNT };

enum StrId {
    S_TITLE,
    S_LED_STATUS,
    S_ON,
    S_OFF,
    S_LED_ON_BTN,
    S_LED_OFF_BTN,
    S_EFFECT,
    S_BRIGHTNESS,
    S_TOGGLE_BTN,
    S_LANG_TR,
    S_LANG_EN,
    S_LANG_AR,
    S_COUNT
};

const char* langStr(byte id, Lang lang);
Lang detectLang(const String& acceptLanguage);
void setPreferredLang(Lang lang);
Lang getPreferredLang();

#endif
