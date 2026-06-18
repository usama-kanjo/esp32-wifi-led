#ifndef LED_EFFECTS_H
#define LED_EFFECTS_H

#include <Arduino.h>

enum Effect {
    EFFECT_SOLID,
    EFFECT_BLINK,
    EFFECT_BLINK_FAST,
    EFFECT_FADE_IN,
    EFFECT_FADE_OUT,
    EFFECT_BREATH,
    EFFECT_COUNT
};

void ledEffectsSetup();
void ledEffectsLoop();
void setEffect(Effect effect);
void setBrightness(uint8_t bri);
void toggleLed();
void setLedState(bool state);
Effect getCurrentEffect();
bool getLedState();
uint8_t getBrightness();
const char* getEffectName(Effect effect);
const char* getEffectNameTr(Effect effect);
const char* getEffectNameAr(Effect effect);

#endif
