#include "html_page.h"

static const char* langCode(Lang lang) {
    if (lang == LANG_TR) return "tr";
    if (lang == LANG_AR) return "ar";
    return "en";
}

static const char* langDir(Lang lang) {
    return (lang == LANG_AR) ? "rtl" : "ltr";
}

static const char* effectName(Lang lang, Effect effect) {
    if (lang == LANG_TR) return getEffectNameTr(effect);
    return getEffectName(effect);
}

String getHTML(bool ledOn, Effect effect, uint8_t brightness, Lang lang) {
    String stateText = ledOn ? langStr(S_ON, lang) : langStr(S_OFF, lang);
    String stateColor = ledOn ? "#00e676" : "#ff5252";
    String statusStr = String(langStr(S_LED_STATUS, lang));
    statusStr.replace("%s", stateText);

    String e;
    e += F("<!DOCTYPE html><html lang=\"");
    e += langCode(lang);
    e += F("\" dir=\"");
    e += langDir(lang);
    e += F("\"><head><meta charset=\"UTF-8\"><meta name=\"viewport\" content=\"width=device-width,initial-scale=1.0\"><title>ESP32</title><style>");
    e += F("*,*::before,*::after{margin:0;padding:0;box-sizing:border-box}");
    e += F(":root{--bg:#0f0f1a;--card:#1a1a2e;--card-hover:#222244;--accent:#00e676;--danger:#ff5252;--text:#e0e0e0;--text-dim:#888;--radius:16px;--shadow:0 8px 32px rgba(0,0,0,0.4)}");
    e += F("body{font-family:-apple-system,BlinkMacSystemFont,'Segoe UI',Roboto,sans-serif;background:var(--bg);color:var(--text);min-height:100vh;display:flex;flex-direction:column;align-items:center;justify-content:center;padding:16px}");
    e += F(".card{background:var(--card);border-radius:var(--radius);box-shadow:var(--shadow);padding:32px 28px;max-width:400px;width:100%;text-align:center}");
    e += F("h1{font-size:24px;font-weight:700;margin-bottom:24px;letter-spacing:-0.5px}");
    e += F(".status{display:inline-flex;align-items:center;gap:10px;padding:12px 28px;border-radius:40px;font-size:18px;font-weight:600;margin-bottom:24px;background:color-mix(in srgb,");
    e += stateColor;
    e += F("15%,transparent);color:");
    e += stateColor;
    e += F(";border:1px solid color-mix(in srgb,");
    e += stateColor;
    e += F("30%,transparent)}");
    e += F(".indicator{width:12px;height:12px;border-radius:50%;background:");
    e += stateColor;
    e += F(";box-shadow:0 0 12px ");
    e += stateColor;
    e += F(";animation:pulse 2s infinite}");
    e += F("@keyframes pulse{0%,100%{opacity:1;transform:scale(1)}50%{opacity:0.6;transform:scale(0.9)}}");
    e += F(".section{margin-bottom:24px}.section label{display:block;font-size:13px;color:var(--text-dim);margin-bottom:10px;text-transform:uppercase;letter-spacing:0.5px}");
    e += F("input[type=\"range\"]{-webkit-appearance:none;width:100%;height:6px;background:#333;border-radius:3px;outline:none}");
    e += F("input[type=\"range\"]::-webkit-slider-thumb{-webkit-appearance:none;width:20px;height:20px;border-radius:50%;background:var(--accent);cursor:pointer;border:2px solid var(--card);box-shadow:0 0 8px rgba(0,230,118,0.4)}");
    e += F(".effect-grid{display:grid;grid-template-columns:repeat(3,1fr);gap:8px}");
    e += F(".effect-btn{padding:10px 4px;border:1px solid #333;border-radius:10px;background:transparent;color:var(--text-dim);font-size:12px;font-weight:500;cursor:pointer;transition:all 0.2s;text-decoration:none;display:block}");
    e += F(".effect-btn:hover{background:var(--card-hover);color:var(--text);border-color:#555}");
    e += F(".effect-btn.active{background:color-mix(in srgb,var(--accent)15%,transparent);color:var(--accent);border-color:var(--accent)}");
    e += F(".btn-row{display:flex;gap:10px;margin-bottom:16px}");
    e += F(".btn{flex:1;padding:14px 0;border:none;border-radius:12px;font-size:16px;font-weight:600;cursor:pointer;transition:all 0.2s;text-decoration:none;display:inline-block}");
    e += F(".btn:hover{transform:translateY(-1px)}.btn:active{transform:translateY(0)}");
    e += F(".btn-on{background:var(--accent);color:#0f0f1a}.btn-off{background:var(--danger);color:#fff}");
    e += F(".btn-toggle{flex:0 0 56px;background:#333;color:var(--text);font-size:20px;display:flex;align-items:center;justify-content:center}");
    e += F(".lang-row{display:flex;gap:8px;justify-content:center;margin-top:8px}");
    e += F(".lang-btn{padding:8px 16px;border:1px solid #333;border-radius:20px;background:transparent;color:var(--text-dim);font-size:13px;cursor:pointer;transition:all .2s;text-decoration:none}");
    e += F(".lang-btn:hover{background:var(--card-hover);color:var(--text);border-color:#555}");
    e += F(".lang-btn.active{background:color-mix(in srgb,var(--accent)15%,transparent);color:var(--accent);border-color:var(--accent)}");
    e += F("[dir=rtl] .card{direction:rtl}");
    e += F("[dir=rtl] .status{direction:ltr;unicode-bidi:embed}");
    e += F("[dir=rtl] .btn-row{direction:ltr;justify-content:center}");
    e += F("</style></head><body><div class=\"card\"><h1>🔥 ");
    e += langStr(S_TITLE, lang);
    e += F("</h1><div class=\"status\"><span class=\"indicator\"></span>");
    e += statusStr;
    e += F("</div><div class=\"section\"><label>");
    e += langStr(S_BRIGHTNESS, lang);
    e += F("</label><input type=\"range\" min=\"0\" max=\"255\" value=\"");
    e += String(brightness);
    e += F("\" oninput=\"fetch('/effect?id=");
    e += String((int)effect);
    e += F("&bri='+this.value)\"></div><div class=\"section\"><label>");
    e += langStr(S_EFFECT, lang);
    e += F("</label><div class=\"effect-grid\">");

    for (int i = 0; i < EFFECT_COUNT; i++) {
        String name = effectName(lang, (Effect)i);
        e += "<a href=\"/effect?id=" + String(i) + "\" class=\"effect-btn" + String(i == (int)effect ? " active" : "") + "\">" + name + "</a>";
    }

    e += F("</div></div><div class=\"btn-row\"><a href=\"/led/on\" class=\"btn btn-on\">");
    e += langStr(S_LED_ON_BTN, lang);
    e += F("</a><a href=\"/led/off\" class=\"btn btn-off\">");
    e += langStr(S_LED_OFF_BTN, lang);
    e += F("</a><a href=\"/led/toggle\" class=\"btn btn-toggle\">⚡</a></div>");
    e += F("<div class=\"lang-row\"><a href=\"/?lang=en\" class=\"lang-btn");
    e += String(lang == LANG_EN ? " active" : "");
    e += F("\">EN</a><a href=\"/?lang=tr\" class=\"lang-btn");
    e += String(lang == LANG_TR ? " active" : "");
    e += F("\">TR</a><a href=\"/?lang=ar\" class=\"lang-btn");
    e += String(lang == LANG_AR ? " active" : "");
    e += F("\">AR</a></div></div></body></html>");

    return e;
}
