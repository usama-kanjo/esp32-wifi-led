#include "button.h"
#include "pin_config.h"
#include "led_effects.h"
#include <Arduino.h>

static unsigned long lastDebounceTime = 0;
static unsigned long pressStartTime = 0;
static int lastReading = HIGH;
static bool longPressHandled = false;

static const unsigned long DEBOUNCE_DELAY = 50;
static const unsigned long LONG_PRESS_MS = 1000;

void buttonSetup() {
    pinMode(BUTTON_PIN, INPUT_PULLUP);
    lastReading = digitalRead(BUTTON_PIN);
}

void buttonLoop() {
    int reading = digitalRead(BUTTON_PIN);
    unsigned long now = millis();

    if (reading != lastReading) {
        lastDebounceTime = now;
    }

    if ((now - lastDebounceTime) > DEBOUNCE_DELAY) {
        if (reading == LOW && !longPressHandled) {
            if (pressStartTime == 0) {
                pressStartTime = now;
            }
            if ((now - pressStartTime) >= LONG_PRESS_MS) {
                Effect e = getCurrentEffect();
                e = (Effect)((e + 1) % EFFECT_COUNT);
                setEffect(e);
                longPressHandled = true;
                Serial.print("Effect changed to: ");
                Serial.println(getEffectName(e));
            }
        }

        if (reading == HIGH && pressStartTime != 0) {
            if (!longPressHandled) {
                toggleLed();
                Serial.print("LED toggled: ");
                Serial.println(getLedState() ? "ON" : "OFF");
            }
            pressStartTime = 0;
            longPressHandled = false;
        }
    }

    lastReading = reading;
}
