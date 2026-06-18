#ifndef HTML_PAGE_H
#define HTML_PAGE_H

#include <Arduino.h>
#include "led_effects.h"
#include "lang.h"

String getHTML(bool ledOn, Effect effect, uint8_t brightness, Lang lang);

#endif
