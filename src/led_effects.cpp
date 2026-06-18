#include "led_effects.h"
#include "pin_config.h"

static Effect currentEffect = EFFECT_SOLID;
static bool ledOn = true;
static uint8_t brightness = 255;
static uint8_t currentPwm = 0;

static unsigned long prevMillis = 0;
static int fadeDir = 1;

static const char* const effectNamesEn[EFFECT_COUNT] = {
    "Solid",
    "Blink",
    "Fast Blink",
    "Fade In",
    "Fade Out",
    "Breath"
};

static const char* const effectNamesTr[EFFECT_COUNT] = {
    "Sürekli",
    "Yanıp Sön",
    "Hızlı Yanıp Sön",
    "Yavaş Açıl",
    "Yavaş Kapan",
    "Nefes"
};

void ledEffectsSetup() {
    ledcSetup(PWM_CHANNEL, PWM_FREQ, PWM_RES);
    ledcAttachPin(LED_PIN, PWM_CHANNEL);
    ledcWrite(PWM_CHANNEL, brightness);
    currentPwm = brightness;
}

void setEffect(Effect effect) {
    if (effect >= EFFECT_COUNT) return;
    currentEffect = effect;
    prevMillis = 0;
    fadeDir = 1;
}

void setBrightness(uint8_t bri) {
    brightness = bri;
}

void toggleLed() {
    ledOn = !ledOn;
    if (!ledOn) {
        ledcWrite(PWM_CHANNEL, 0);
        currentPwm = 0;
    } else {
        currentPwm = brightness;
    }
    prevMillis = 0;
    fadeDir = 1;
}

void setLedState(bool state) {
    if (state != ledOn) toggleLed();
}

bool getLedState() { return ledOn; }
Effect getCurrentEffect() { return currentEffect; }
uint8_t getBrightness() { return brightness; }

const char* getEffectName(Effect effect) {
    if (effect >= EFFECT_COUNT) return "";
    return effectNamesEn[effect];
}

const char* getEffectNameTr(Effect effect) {
    if (effect >= EFFECT_COUNT) return "";
    return effectNamesTr[effect];
}

void ledEffectsLoop() {
    unsigned long now = millis();

    if (!ledOn) {
        if (currentPwm != 0) {
            currentPwm = 0;
            ledcWrite(PWM_CHANNEL, 0);
        }
        return;
    }

    switch (currentEffect) {
        case EFFECT_SOLID:
            if (currentPwm != brightness) {
                currentPwm = brightness;
                ledcWrite(PWM_CHANNEL, currentPwm);
            }
            break;

        case EFFECT_BLINK:
            if (now - prevMillis > 500) {
                prevMillis = now;
                currentPwm = (currentPwm == 0) ? brightness : 0;
                ledcWrite(PWM_CHANNEL, currentPwm);
            }
            break;

        case EFFECT_BLINK_FAST:
            if (now - prevMillis > 200) {
                prevMillis = now;
                currentPwm = (currentPwm == 0) ? brightness : 0;
                ledcWrite(PWM_CHANNEL, currentPwm);
            }
            break;

        case EFFECT_FADE_IN:
            if (currentPwm >= brightness) break;
            if (now - prevMillis > 10) {
                prevMillis = now;
                currentPwm = (currentPwm + 1 < brightness) ? currentPwm + 1 : brightness;
                ledcWrite(PWM_CHANNEL, currentPwm);
            }
            break;

        case EFFECT_FADE_OUT:
            if (currentPwm == 0) break;
            if (now - prevMillis > 10) {
                prevMillis = now;
                currentPwm = (currentPwm > 0) ? currentPwm - 1 : 0;
                ledcWrite(PWM_CHANNEL, currentPwm);
            }
            break;

        case EFFECT_BREATH:
            if (now - prevMillis > 20) {
                prevMillis = now;
                int val = currentPwm + fadeDir * 2;
                if (val >= (int)brightness) {
                    val = brightness;
                    fadeDir = -1;
                } else if (val <= 0) {
                    val = 0;
                    fadeDir = 1;
                }
                currentPwm = (uint8_t)val;
                ledcWrite(PWM_CHANNEL, currentPwm);
            }
            break;

        default:
            break;
    }
}
